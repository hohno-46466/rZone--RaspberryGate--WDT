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

// internal time counter
// uint32_t ten_millis_prev = 0; // previous time (in 10msec)
uint32_t ten_millis_curr = 0; // current time (in 10msec)
// uint32_t ten_millis_task_timeout[4] = { 0, 0, 0, 0 };

// ---------------------------------------------------------

// loop()

// WARNING:
// We can NEVER use delay() function in the loop() and task...() functions.
// Instead of using delay(), we have to create and use the task function like task1()

// -------------------------------------

int debug_cnt = 0;
uint32_t debug_ten_millis_lastcnt = 0;


void loop() {

  static int pulseStat = 0;

  ten_millis_curr = millis() / 10;

  if ((ten_millis_curr - debug_ten_millis_lastcnt) >= 100) {
    // debug_cnt increments every second
    // debug_ten_millis_lastcnt holds the time when debug_cnt was updated.
    debug_cnt++;
    debug_ten_millis_lastcnt = ten_millis_curr;
	}

	pulseStat = task0_wrapper();

#ifdef _USE_UNO_
		if (pulseStat >= 0) {
			Serial.print(">>> pulsStat = "); Serial.println(pulseStat);
		}
#endif // _USE_UNO_

  task1_wrapper();

  task2_wrapper();

  task3_wrapper();

	task4_wrapper();

	taskX_wrapper();

}


// ---------------------------------------------------------
// wrapper functions
// ---------------------------------------------------------

void taskX_wrapper() {

  // example task: LED blinking

  if (debug_cnt < 6) {
    taskX(75,25);
  } else if (debug_cnt < 12) {
    taskX(150,50);
  } else if (debug_cnt < 18) {
		taskX(200,50);
  } else if (debug_cnt < 24) {
    taskX(300,100);
  } else {
    debug_cnt = 0;
    taskX(20,20);
  }
}


// -------------------------------------

void task1_wrapper() {

  // example task: LED blinking

  if (debug_cnt < 5) {
    task1(500,500);
  } else if (debug_cnt < 10) {
    task1(250,250);
  } else if (debug_cnt < 15) {
    task1(100,100);
  } else if (debug_cnt < 20) {
    task1(50,50);
  } else {
    debug_cnt = 0;
		task1(20,20);
  }
}

// -------------------------------------

void task3_wrapper() {

  boolean flag_reboot = false;

  if (flag_reboot) {
    task3(1000, 1);
  }
}

// -------------------------------------

int task0_wrapper() {

	static int _pulsesPerTenSec = 0, _pulsesPerTenSec_prev = -1;
  static boolean _pulsesPerTenSecStat = false;
  int _retval = -1;

	_pulsesPerTenSec = task0();

	if ((_pulsesPerTenSecStat == false) && (_pulsesPerTenSec > 8)) {
			_pulsesPerTenSecStat = true;
			_retval = 0;

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 1)
			Serial.print("# *** newWDT started. ***  "); Serial.println(_pulsesPerTenSec);
#endif // (_DEBUG_LEVEL >= 1)
#endif // _USE_UNO_

	} else if ((_pulsesPerTenSecStat == true) && (_pulsesPerTenSec < 3)) {
			_pulsesPerTenSecStat = false;
			_retval = 1;

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 1)
			Serial.print("# *** RESET required. ***  "); Serial.println(_pulsesPerTenSec);
#endif // (_DEBUG_LEVEL >= 1)
#endif // _USE_UNO_
	}

		if (_pulsesPerTenSec >= 0) {
			if (_pulsesPerTenSec != _pulsesPerTenSec_prev) {

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 2)
				Serial.print("# _pulsesPerTenSec = "); Serial.println(_pulsesPerTenSec);
#endif // (_DEBUG_LEVEL >= 2)
#endif // _USE_UNO_

				_pulsesPerTenSec_prev = _pulsesPerTenSec;
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
