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

#define PIN_I_PULSE   (PIN_0)
#define PIN_O_LED     (PIN_1)
#define PIN_I_REQ     (PIN_2)
#define PIN_O_RESET   (PIN_3)
#define PIN_O_NOTE    (PIN_4)

#define ATT_LED_ON    (digitalWrite(PIN_O_LED, HIGH))
#define ATT_LED_OFF   (digitalWrite(PIN_O_LED, LOW))

#define ATT_NOTE_ON   (digitalWrite(PIN_O_NOTE, LOW))
#define ATT_NOTE_OFF  (digitalWrite(PIN_O_NOTE, HIGH))

#define ATT_RESET_ON  (digitalWrite(PIN_O_RESET, LOW))
#define ATT_RESET_OFF (digitalWrite(PIN_O_RESET, HIGH))

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
uint32_t ten_millis_prev = 0; // previous time (in 10msec)
uint32_t ten_millis_curr = 0; // current time (in 10msec)
uint32_t ten_millis_task_timeout[4] = { 0, 0, 0, 0 };

// ---------------------------------------------------------

// loop()

int debug_cnt = 0;
int debug_ten_millis = 0;

void loop() {

	// We can NEVER use delay() function in the loop() and sub_...() functions.
	// Instead of using delay(), we have to create and use the task function like task1()

	ten_millis_curr = millis() / 10;

	if ((ten_millis_curr - debug_ten_millis) >= 100) {
		// debug_cnt increments every second
		// debug_ten_millis holds the time when debug_cnt was updated.
		debug_cnt ++;
		debug_ten_millis = ten_millis_curr;
	}

	sub_for_debug();

}

	// -------------------------------------

void sub_for_debug() {

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
	}
	// ------------------------

	boolean flag_reboot = false;

	if (flag_reboot) {
		task2(1000, 1);
	}

}


// ---------------------------------------------------------

// sub functions

// -------------------------------------

// task2 - RESET Raspberry Pi

// task2(int arg1, boolean arg2)
//    arg1 - duration of pulling down the Reset pin (in msec)
//    arg2 - how many times will it generate Reset pulse (usually 1)

boolean task2(int32_t arg1, int arg2) {
	static int32_t _prev_arg1 = -1;
	static boolean _flag = false;
	static uint32_t _ten_millis_next = 0;
	static boolean _cnt = 0;

		if (arg2 < 0) {
		_cnt = 0;
		return(true);
	}

	if ((arg1 <= 0) || (arg1 >= 1000*1000L)) {
		return(false);
	}


	if (!_flag) {
		if (_cnt < arg2) {
			_flag = true;
			_cnt++;
	  	_ten_millis_next = (millis() + arg1) / 10;
	  	ATT_RESET_ON;
		}

	} else {
		// flag is true;
		if (_ten_millis_next <= ten_millis_curr) {
			ATT_RESET_OFF;
			_flag = false;
		}
	}
	return(_flag);
}

// -------------------------------------

// task1 - - blinkint LED

// task1(int arg1, int arg2)
//   arg1 - duration of LED ON (in msec);
//   arg2 - duration of LED OFF (in msec)
// returns
//   true  - LED is ON
//   false - LED is OFF

boolean task1(int arg1, int arg2) {
	static uint32_t _ten_millis_prev = 0;
	static uint32_t _ten_millis_next = 0;
	static int _prev_arg1 = 0;
	static int _prev_arg2 = 0;
  static boolean _flag = false;

	if ((arg1 == _prev_arg1) && (arg2 == _prev_arg2)) {
		// Bith arg1 and arg2 are not updated
		if (_ten_millis_next <= ten_millis_curr) {
			if (_flag) {
				_flag = false;
				_ten_millis_next += (arg2/10);
				ATT_LED_OFF;
			} else {
				_flag = true;
				_ten_millis_next += (arg1/10);;
				ATT_LED_ON;
			}
		}
	} else {
		// one of arg1 and arg2 was updated
		_prev_arg1 = arg1;
		_prev_arg2 = arg2;
		_ten_millis_next = (millis() + arg1) / 10;
		_flag = true;
		ATT_LED_ON;
	}

	return(_flag);
}

// ---------------------------------------------------------


// ---------------------------------------------------------

// ---------------------------------------------------------

/*

References:

* ATtiny85 Module with Micro USB

  https://protosupplies.com/product/attiny85-module-with-micro-usb/

  http://digistump.com/wiki/digispark/tutorials/connecting

* schematic (Digispark ATtiny85)

  https://s3.amazonaws.com/digistump-resources/files/97a1bb28_DigisparkSchematic.pdf


*/


// ---------------------------------------------------------
