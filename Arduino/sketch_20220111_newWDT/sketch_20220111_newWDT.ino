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
P5 - - - (By default, this pin is assigned as reset for ATtiny85 (can't be used for GPIO)
*/

// ---------------------------------------------------------

// Includes and Definitions

#include "./mydefs.h"
#include "./taskClass0.h"
#include "./taskClass1.h"
#include "./taskClass2.h"
#include "./taskClass3.h"
#include "./taskClass4.h"

// ---------------------------------------------------------

taskClass0 task0(PIN_I_PULSE);
taskClass1 task1(PIN_O_LED);
taskClass2 task2(PIN_I_REQ);
taskClass3 task3(PIN_O_RESET);
//taskClass4 task4(PIN_O_NOTE);
taskClass1 taskX(PIN_O_NOTE);

// ---------------------------------------------------------

// setup()

void setup() {
  pinMode(PIN_I_PULSE,INPUT_PULLUP);
  pinMode(PIN_O_LED,  OUTPUT);
  pinMode(PIN_I_REQ  ,INPUT_PULLUP);
  pinMode(PIN_O_RESET,OUTPUT);
  pinMode(PIN_O_NOTE ,OUTPUT);

  ATT_LED_OFF;    // LED is OFF
  ATT_NOTE_OFF;   // Reset pin on Raspberry Pi is not activated (Negative logic)
  ATT_RESET_OFF;  // No notification information

#ifdef _USE_UNO_
  Serial.begin(57600);
  Serial.println("# Hello!"); Serial.println();
#endif // _USE_UNO_

}

// ---------------------------------------------------------

/*
 Caveat:
  The value of the internal clock is in increments of 10m seconds.
  This means that the internal clock overflows approximately every 497 days.
  Since there is no overflow protection, this sketch needs to be restarted within 497 days after startup.

 Note: ((2**32)/100)/3600/24 = ~497.1
*/

// ---------------------------------------------------------

// Time Counter (unit: 10msec)

uint32_t GLOBAL_ten_millis_curr = 0; // current time (in 10msec)
// uint32_t GLOBAL_ten_millis_task_timeout[4] = { 0, 0, 0, 0 };

// ---------------------------------------------------------

int debug_cnt = 0;
uint32_t debug_ten_millis_lastcnt = 0;


// ---------------------------------------------------------

// loop()

// WARNING:
// We can NEVER use delay() function in the loop() and task...() functions.
// Instead of using delay(), we have to create and use the task function like task1()

void loop() {

  static int pulseStat = 0;

  // GLOBAL_ten_millis_curr = millis() / 10;
  GLOBAL_ten_millis_curr = tenMillis();

  if ((GLOBAL_ten_millis_curr - debug_ten_millis_lastcnt) >= 100) {
    // debug_cnt increments every second
    // debug_ten_millis_lastcnt holds the time when debug_cnt was updated.
    debug_cnt++;
    if (debug_cnt >= 30) { debug_cnt = 0; }
    debug_ten_millis_lastcnt = GLOBAL_ten_millis_curr;
  }

// -------------------------------------

	// task0 - Check the pulse from Raspberry Pi

  pulseStat = task0_wrapper();

	// Return value:
	//   0 - watchdog timer is running.
	//   1 - reset required
	//  -1 - other condition

#ifdef _USE_UNO_
	if (pulseStat >= 0) {
		Serial.print(">>> pulsStat = "); Serial.println(pulseStat);
	}
#endif // _USE_UNO_

// -------------------------------------

	// task0 - Blink LED

	task1_wrapper();

// -------------------------------------

	// task2 - Request from Raspberry Pi for the watchdog type

  task2_wrapper();

// -------------------------------------

	// task3 - Generate reset pulse (for both of the gentle and the delayed watchdog)

  task3_wrapper();

// -------------------------------------

	// task4 - Generate notification signal for Raspberry Pi

  task4_wrapper();

// -------------------------------------

	// taskX - Blink LED using the notification pin

  taskX_wrapper();

}


// ---------------------------------------------------------
// wrapper functions
// ---------------------------------------------------------

void taskX_wrapper() {

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
}


// -------------------------------------

void task1_wrapper() {

  // example task: LED blinking

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
}

// -------------------------------------

void task3_wrapper() {

  boolean flag_reboot = false;

  if (flag_reboot) {
    task3tmp(1000, 1);
  }
}

// -------------------------------------

int task0_wrapper() {

  static int _pulsesPer30Sec = 0, _pulsesPer30Sec_prev = -1;
  static boolean _pulsesPer30SecStat = false;
  int _retval = -1;
  const int _WDT_START_LEVEL = 8;
  const int _WDT_RESET_LEVEL = 3;


  _pulsesPer30Sec = task0tmp();

  if ((_pulsesPer30SecStat == false) && (_pulsesPer30Sec > _WDT_START_LEVEL)) {
      _pulsesPer30SecStat = true;
      _retval = 0;

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 1)
      Serial.print("# *** newWDT started. ***  "); Serial.println(_pulsesPer30Sec);
#endif // (_DEBUG_LEVEL >= 1)
#endif // _USE_UNO_

  } else if ((_pulsesPer30SecStat == true) && (_pulsesPer30Sec < _WDT_RESET_LEVEL)) {
      _pulsesPer30SecStat = false;
      _retval = 1;

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 1)
      Serial.print("# *** RESET required. ***  "); Serial.println(_pulsesPer30Sec);
#endif // (_DEBUG_LEVEL >= 1)
#endif // _USE_UNO_
  }

    if (_pulsesPer30Sec >= 0) {
      if (_pulsesPer30Sec != _pulsesPer30Sec_prev) {

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 2)
        Serial.print("# _pulsesPer30Sec = "); Serial.println(_pulsesPer30Sec);
#endif // (_DEBUG_LEVEL >= 2)
#endif // _USE_UNO_

        _pulsesPer30Sec_prev = _pulsesPer30Sec;
      }
    }

    return(_retval);
}


// -------------------------------------

void task2_wrapper() {

}


// -------------------------------------

void task4_wrapper() {

}


// ---------------------------------------------------------
// sub functions
// ---------------------------------------------------------

uint32_t tenMillis() {
  static int cntOVF = 0;
  static uint32_t Tnow = 0;
  static uint32_t millisPrev = 0, millisNow = 0;

  millisNow = millis();

  if (millisNow < millisPrev) {
    cntOVF++;
  }
  Tnow = (millisNow / 10UL) + (cntOVF % 10) * 429496729UL;
  millisPrev = millisNow;

  return(Tnow);
}

// ---------------------------------------------------------

uint32_t eightMillis() {
  static int cntOVF = 0;
  static uint32_t Tnow = 0;
  static uint32_t millisPrev = 0, millisNow = 0;

  millisNow = millis();

  if (millisNow < millisPrev) {
    cntOVF++;
  }
  Tnow = (millisNow / 8UL) + (cntOVF % 8) * 536870912UL;
  millisPrev = millisNow;

  return(Tnow);
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
