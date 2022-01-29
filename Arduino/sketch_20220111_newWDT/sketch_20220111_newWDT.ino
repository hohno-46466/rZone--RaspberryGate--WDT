//
// sketch_20220111_newWDT.ino - another watchdog timer for Raspberry Pi
//

// Public domain

// ---------------------------------------------------------

// Note: This sketch has been prepared for the Digispark ATtiny85 board.

// See also the references section at the end of this sketch.

// ---------------------------------------------------------

// History:

// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// Pinouts:

/*
 P0 - I ← Watchdog Pulse from RPito ATtiny85   - IO5  21
 P1 - O → Indicator (blink the onboard)        - N/A  N/A
 P2 - I ← Request for watchdog type            - IO6  22
 P3 - O → Hardware Reset                       - (RUN pin (via level shifter))
 P4 - O → Notification from ATtiny85 to RPi    - IO12 32  (via level shifter)
 P5 - - - (By default, this pin is assigned to RESET on the ATtiny85 (It cannot be used for GPIO)
*/

// ---------------------------------------------------------

// Includes and Definitions

#include "./mydefs.h"			// Read mydefs.h before you read this sketch

#include "./taskClass0.h"
#include "./taskClass1.h"
#include "./taskClass2.h"
#include "./taskClass3.h"
#include "./taskClass4.h"

#include "classButtonSW.h"
#include "classBlinkLED.h"

#include "WDTstatus.h"

// ---------------------------------------------------------

// constructors

// Button Switches
classButtonSW task0input();
classButtonSW task3input();

// WDT Status

WDTstatus myWDT();

// task0 - Check the "heart beat" pulse from Raspberry Pi
taskClass0 task0(PIN_I_PULSE);

// task1 - Blink LED to show the current status
taskClass1 task1(PIN_O_LED);

// task2 - Detect type-specified request from Raspberry Pi
taskClass2 task2(PIN_I_REQ);

// task3 - Generate RESET pulse (for both of the gentle and the delayed watchdog)
taskClass3 task3(PIN_O_RESET);

#ifdef _USE_TASKX_INSTEAD_OF_TASK4_
// taskX - Blink LED using the notification pin (for debugging)
taskClass1 taskX(PIN_O_NOTE);
#else // _USE_TASKX_INSTEAD_OF_TASK4_
// task4 - Generate notification signal for Raspberry Pi
taskClass4 task4(PIN_O_NOTE);
#endif // _USE_TASKX_INSTEAD_OF_TASK4_

int task0stat = -1;
int task1stat = -1;
int task2stat = -1;
int task3stat = -1;

#ifdef _USE_TASKX_INSTEAD_OF_TASK4_
int taskXstat = -1;
#else // _USE_TASKX_INSTEAD_OF_TASK4_
int task4stat = -1;
#endif // _USE_TASKX_INSTEAD_OF_TASK4_

// ---------------------------------------------------------

// setup()

void setup() {

  task0.init(PIN_I_PULSE);  // pinMode(PIN_I_PULSE,INPUT_PULLUP);
  task1.init(PIN_O_LED);    // pinMode(PIN_O_LED,  OUTPUT);
  task2.init(PIN_I_REQ );   // pinMode(PIN_I_REQ  ,INPUT_PULLUP);
  task3.init(PIN_O_RESET);  // pinMode(PIN_O_RESET,OUTPUT);

#ifdef _USE_TASKX_INSTEAD_OF_TASK4_
  taskX.init(PIN_O_NOTE);   // pinMode(PIN_O_NOTE ,OUTPUT);
#else // _USE_TASKX_INSTEAD_OF_TASK4_
  task4.init(PIN_O_NOTE);
#endif // _USE_TASKX_INSTEAD_OF_TASK4_

  AVR_LED_OFF;    // LED is OFF
  AVR_NOTE_OFF;   // Reset pin on Raspberry Pi is not activated (Negative logic)
  AVR_RESET_OFF;  // No notification information

#ifdef _USE_UNO_
  Serial.begin(57600);
  Serial.println("# Hello!"); Serial.println();
#endif // _USE_UNO_

}

// ---------------------------------------------------------

/*
 Caveat:
  The value of the internal clock is incremented every 8 milli seconds.
  This means that the internal clock will overflow approximately every 397 days.
  Since there is no overflow protection, this sketch must be rebooted within 397 days after startup.

 Note: ((2**32)*8)/(1000*3600*24) = ~397.68

*/

// ---------------------------------------------------------

// Time Counter (unit: 8msec)

uint32_t CurrentTime_8ms = 0; // current time (in 8msec)

// ---------------------------------------------------------

// For debugging

int debug_cnt = 0;
uint32_t debug_LastCnt = 0;

// ---------------------------------------------------------

// loop()

// WARNING:
// We can NEVER use delay() function in the loop() and task...() functions.
// Instead of using delay(), we have to create and use the task function like task1()

uint32_t eightMillis();

void loop() {

  CurrentTime_8ms = eightMillis();

  if ((CurrentTime_8ms - debug_LastCnt) >= 125 /* 125 == 1000/8 */) {
    // debug_cnt increments every second
    // debug_LastCnt holds the time when debug_cnt was updated.
    debug_cnt++;
    if (debug_cnt >= 30) {
      debug_cnt = 0;

#ifdef _USE_UNO_
      Serial.print(">>> CurrentTime_8ms = "); Serial.println(CurrentTime_8ms);
#endif // _USE_UNO_
    }
    debug_LastCnt = CurrentTime_8ms;
  }

// -------------------------------------

  // task0 - Check the "heart beat" pulse from Raspberry Pi

  task0stat = task0_wrapper();

  // task0_wrapper() returns:
  //   0 - watchdog timer is running.
  //   1 - reset required (normal mode)
  //   2 - reset required (extended mode)
  //  -1 - other condition

#ifdef _USE_UNO_
  if (task0stat > 0) {
    // Serial.print(">>> task0_wrapper() returned "); Serial.println(task0stat);
  }
#endif // _USE_UNO_

// -------------------------------------

  // task1 - Blink LED to show the current status

  task1stat = task1_wrapper();

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 1)
	if (task1stat >= 1) {
      Serial.print("# *** RESET reqired. *** retval = "); Serial.println(task1stat);
	}
#endif // (_DEBUG_LEVEL >= 1)
#endif // _USE_UNO_

  // Since current task1_wrapper() just blinks a LED,
  // task0_wrapper() always returns zero.

// -------------------------------------

  // task2 - Detect type-specified request from Raspberry Pi

  task2stat = task2_wrapper();

  // task2_wrapper() returns:
  //   0 - delayed mode
  //   1 - gentle mode
  //  -1 - other condition

// -------------------------------------

  // task3 - Generate RESET pulse (for both of the gentle and the delayed watchdog)

    task3stat = task3_wrapper();

  // task3_wrapper() returns:
  //   0 - RESET pulse is NOT generated
  //   1 - RESET is ongoing
  //  -1 - other condition

// -------------------------------------

#ifdef _USE_TASKX_INSTEAD_OF_TASK4_

  // taskX - Blink LED using the notification pin (for debugging)

  // Since current version of taskX_wrapper() just blinks a LED,
  // taskX_wrapper() always returns zero.

  taskXstat = taskX_wrapper();

#else // _USE_TASKX_INSTEAD_OF_TASK4_

  // task4 - Generate notification signal for Raspberry Pi

  task4stat = task4_wrapper();

// task4_wrapper() returns:
//   0 - notification is NOT activated
//   1 - notification is activated
//  -1 - other condition

#endif // _USE_TASKX_INSTEAD_OF_TASK4_

// -------------------------------------

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL == 0)
	Serial.print("# "); Serial.print(task0stat);
	Serial.print("  "); Serial.print(task1stat);
	Serial.print("  "); Serial.print(task2stat);
	Serial.print("  "); Serial.print(task3stat);
#ifdef _USE_TASKX_INSTEAD_OF_TASK4_
	Serial.print("  "); Serial.print(taskXstat);
#else
	Serial.print("  "); Serial.print(task4stat);
#endif
	Serial.println();
	delay(50);
#endif // (_DEBUG_LEVEL >= 0)
#endif // _USE_UNO_

}

// ---------------------------------------------------------
// wrapper functions
// ---------------------------------------------------------

#ifdef _USE_TASKX_INSTEAD_OF_TASK4_

int taskX_wrapper() {

  // example task: LED blinking

  // taskX.set(500,500); taskX.blink();

  if (debug_cnt == 0) {
    taskX.set(50,950);

  } else if (debug_cnt == 6) {
    taskX.set(250,750);

  } else if (debug_cnt == 12) {
    taskX.set(500,500);

  } else if (debug_cnt == 18) {
    taskX.set(750,250);

  } else if (debug_cnt == 24) {
    taskX.set(950,50);
  }
  taskX.blink();

  return(0);
}

#endif // _USE_TASKX_INSTEAD_OF_TASK4_

// -------------------------------------

// task0_wrapper() returns:
//   0 - watchdog timer is running.
//   1 - reset required (normal mode)
//   2 - reset required (extended mode)
//  -1 - other condition

int task0_wrapper() {

  static int _pulsesPerNsec = 0, _pulsesPerNsec_prev = -1;
  static boolean _pulsesPerNsecStat = false;
  static int _retval = -1;
  const int _WDT_START_LEVEL = 8;
  const int _WDT_RESET_LEVEL = 3;
  // const int _Nsec = PulseCounterSize;

  // _pulsesPerNsec = task0core() * _Nsec; // task0core() returns avaraged number of pulses per second in float style
  _pulsesPerNsec = task0.core();

  if ((_pulsesPerNsecStat == false) && (_pulsesPerNsec > _WDT_START_LEVEL)) {
      _pulsesPerNsecStat = true;
      _retval = 0;

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 1)
      Serial.print("# *** newWDT started. ***  "); Serial.println(_pulsesPerNsec);
#endif // (_DEBUG_LEVEL >= 1)
#endif // _USE_UNO_

  } else if ((_pulsesPerNsecStat == true) && (_pulsesPerNsec < _WDT_RESET_LEVEL)) {
      _pulsesPerNsecStat = false;
      if (_pulsesPerNsec > (PulseCounterSize + 10)) {
        _retval = 2;
      } else {
        _retval = 1;
      }
  }

    if (_pulsesPerNsec >= 0) {
      if (_pulsesPerNsec != _pulsesPerNsec_prev) {

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 2)
        // Serial.print("# _pulsesPerNsec = "); Serial.println(_pulsesPerNsec);
#endif // (_DEBUG_LEVEL >= 2)
#endif // _USE_UNO_

        _pulsesPerNsec_prev = _pulsesPerNsec;
      }
    }

    return(_retval);
}

// -------------------------------------

int task1_wrapper() {

  // example task: LED blinking

  // task1_wrapper() always returns zero

  if (debug_cnt < 5) {
    task1.set(500,500); task1.blink();

  } else if (debug_cnt < 10) {
    task1.set(250,250); task1.blink();

  } else if (debug_cnt < 15) {
    task1.set(100,100); task1.blink();

  } else if (debug_cnt < 20) {
    task1.set(50,50); task1.blink();

  } else {
    task1.set(20,20); task1.blink();
  }

  return(0);
}

// -------------------------------------

// task2_wrapper() returns:
//   0 - delayed mode
//   1 - gentle mode
//  -1 - other condition

int task2_wrapper() {

  int _retval = -1;

  // int _retval = task2core();

  return(_retval);
}


// -------------------------------------

// task3_wrapper() returns:
//   0 - RESET pulse is NOT generated
//   1 - RESET is ongoing
//  -1 - other condition

int task3_wrapper() {

  static int _reset = 0;

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 2)
  //    Serial.print("#*** CurrentTime_8ms = "); Serial.print(CurrentTime_8ms);
  //    Serial.print("  task0stat = "); Serial.println(task0stat);
#endif // (_DEBUG_LEVEL >= 1)
#endif // _USE_UNO_



#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 1)
	if (task1stat >= 1) {
		Serial.print("# *** RESET reqired. *** HEARTBEAT_LOST = "); Serial.println(HEARTBEAT_LOST);
	}
#endif // (_DEBUG_LEVEL >= 1)
#endif // _USE_UNO_


  if (HEARTBEAT_LOST && (_reset == 0)) {

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 2)
    Serial.print("# task3_wrapper()  "); Serial.println(task0stat);
#endif // (_DEBUG_LEVEL >= 1)
#endif // _USE_UNO_

    uint32_t _gTime1 = EXTENDED_MODE ? (60*1000L) : 1000L;
    uint32_t _gTime2 = 1000L;
    _reset = task3.core(1000, _gTime1, _gTime2, 1); // Gemerate a RESET pulse only once for 1second
    // arg1 - duration of the RESET pulse
    // arg2 - guard time before the first RESET pulse (in msec)
    // arg3 - guard time after for each RESET pulse (in msec)
    // arg4 - number of RESET pulses

    // retval = _reset ? 1 : 0;

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 2)
    Serial.print("# task3.core() returned "); Serial.println(_reset);
#endif // (_DEBUG_LEVEL >= 1)
#endif // _USE_UNO_

  }

  return(_reset);
}

// -------------------------------------

#ifndef _USE_TASKX_INSTEAD_OF_TASK4_

// task4_wrapper() returns:
//   0 - notification is NOT activated
//   1 - notification is activated
//  -1 - other condition

int task4_wrapper() {

  int _retval = -1;

  // int _retval = task4core();

  return(_retval);

}

#endif // _USE_TASKX_INSTEAD_OF_TASK4_

// ---------------------------------------------------------
// sub functions
// ---------------------------------------------------------

uint32_t tenMillis() {
  static int _cntOVF = 0;
  static uint32_t _now_8ms = 0;
  static uint32_t _prev_1ms = 0, _now_1ms = 0;

  _now_1ms = millis();

  if (_now_1ms < _prev_1ms) {
    // increment the overflow counter
    _cntOVF++;
  }
  _now_8ms = (_now_1ms / 10UL) + (_cntOVF % 10) * 429496729UL;
  _prev_1ms = _now_1ms;

  return(_now_8ms);
}

// ---------------------------------------------------------

uint32_t eightMillis() {
  static int _cntOVF = 0;
  static uint32_t _now_8ms = 0;
  static uint32_t _prev_1ms = 0, _now_1ms = 0;

  _now_1ms = millis();

  if (_now_1ms < _prev_1ms) {
    // increment the overflow counter
    _cntOVF++;
  }
  _now_8ms = (_now_1ms / 8UL) + (_cntOVF % 8) * 536870912UL;
  _prev_1ms = _now_1ms;

  return(_now_8ms);
}

// ---------------------------------------------------------
// References:
// ---------------------------------------------------------

/*
 * ATtiny85 Module with Micro USB
 *
 *  https://protosupplies.com/product/attiny85-module-with-micro-usb/
 *
 *  http://digistump.com/wiki/digispark/tutorials/connecting
 *
 * schematic (Digispark ATtiny85)
 *
 *  https://s3.amazonaws.com/digistump-resources/files/97a1bb28_DigisparkSchematic.pdf
 *
 */

// ---------------------------------------------------------
