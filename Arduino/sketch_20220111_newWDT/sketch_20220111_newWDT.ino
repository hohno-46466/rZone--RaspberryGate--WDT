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

int cnt_debug = 0;
int ten_millis_debug = 0;

// WARNING:
// We can NEVER use delay() function in the loop() and task...() functions.
// Instead of using delay(), we have to create and use the task function like task1()

// -------------------------------------

void loop() {

  ten_millis_curr = millis() / 10;

  if ((ten_millis_curr - ten_millis_debug) >= 100) {
    // cnt_debug increments every second
    // ten_millis_debug holds the time when cnt_debug was updated.
    cnt_debug ++;
    ten_millis_debug = ten_millis_curr;
  }

  task_for_debug1();
  task_for_debug2();

}

// -------------------------------------

void task_for_debug1() {

  // example task: LED blinking

  if (cnt_debug < 5) {
    task1(500,500);
  } else if (cnt_debug < 10) {
    task1(250,250);
  } else if (cnt_debug < 15) {
    task1(100,100);
  } else if (cnt_debug < 20) {
    task1(50,50);
  } else {
    cnt_debug = 0;
		task1(200,50);
  }
}
// -------------------------------------

void task_for_debug2() {

  boolean flag_reboot = false;

  if (flag_reboot) {
    task2(1000, 1);
  }
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
