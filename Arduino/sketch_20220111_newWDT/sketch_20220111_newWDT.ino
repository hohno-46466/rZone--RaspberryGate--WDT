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

#include "./mydefs.h"       // Read mydefs.h before you read this sketch

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

// task0 - Check the "heart beat" pulse from Raspberry Pi
taskClass0 task0(PIN_I_PULSE);

// task1 - Blink LED to show the current status
taskClass1 task1(PIN_O_LED);

// task2 - Detect type-specified request from Raspberry Pi
taskClass2 task2(PIN_I_REQ);

// task3 - Generate RESET pulse (for both of the gentle and the delayed watchdog)
taskClass3 task3(PIN_O_RESET);

#ifdef  USE_TASKX_INSTEADOF_TASK4
// taskX - Blink LED using the notification pin (for debugging)
taskClass1 taskX(PIN_O_NOTE);
#else   // if not USE_TASKX_INSTEADOF_TASK4
// task4 - Generate notification signal for Raspberry Pi
taskClass4 task4(PIN_O_NOTE);
#endif  // USE_TASKX_INSTEADOF_TASK4

int task0stat = -1;
int task1stat = -1;
int task2stat = -1;
int task3stat = -1;

#ifdef  USE_TASKX_INSTEADOF_TASK4
int taskXstat = -1;
#else   // if not USE_TASKX_INSTEADOF_TASK4
int task4stat = -1;
#endif  // USE_TASKX_INSTEADOF_TASK4

// WDT Status
WDTstatus myWDTx;


// ---------------------------------------------------------

#define TEST_MODE

// setup()

void setup() {

  task0.init(PIN_I_PULSE);  // pinMode(PIN_I_PULSE,INPUT_PULLUP);
  task1.init(PIN_O_LED);    // pinMode(PIN_O_LED,  OUTPUT);
  task2.init(PIN_I_REQ );   // pinMode(PIN_I_REQ  ,INPUT_PULLUP);
  task3.init(PIN_O_RESET);  // pinMode(PIN_O_RESET,OUTPUT);

#ifdef  USE_TASKX_INSTEADOF_TASK4
  taskX.init(PIN_O_NOTE);   // pinMode(PIN_O_NOTE ,OUTPUT);
#else   // if not USE_TASKX_INSTEADOF_TASK4
  task4.init(PIN_O_NOTE);
#endif  // USE_TASKX_INSTEADOF_TASK4

  AVR_LED_OFF;    // LED is OFF
  AVR_NOTE_OFF;   // Reset pin on Raspberry Pi is not activated (Negative logic)
  AVR_RESET_OFF;  // No notification information

#ifdef  USE_GBKA
  Serial.begin(57600);
#endif  // USE_GBKA

#ifdef  TEST_MODE
  setupXtest();
#else
  setupX();
#endif  // TEST_MODE
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void setupX() {

  myWDTx.init();

#ifdef  USE_GBKA
  Serial.println("# Hello!"); Serial.println();
#endif  // USE_GBKA

  // *** End of setup() ***
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

  USE_GBKA  CurrentTime_8ms = eightMillis();

  if ((CurrentTime_8ms - debug_LastCnt) >= 125 /* 125 == 1000/8 */) {
    // debug_cnt increments every second
    // debug_LastCnt holds the time when debug_cnt was updated.
    debug_cnt++;
    if (debug_cnt >= 30) {
      debug_cnt = 0;

#ifdef  USE_GBKA
      Serial.print(">>> CurrentTime_8ms = "); Serial.print(CurrentTime_8ms); Serial.print(", "); Serial.println(debug_cnt);
#endif  // USE_GBKA
    }
    debug_LastCnt = CurrentTime_8ms;
  }

#ifdef  TEST_MODE
  loopXtest();
#else
  loopX();
#endif  // TEST_MODE
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void loopX() {


  // task0 - Check the "heart beat" pulse from Raspberry Pi

  task0stat = task0_wrapper();

  // task0_wrapper() returns:
  //   0 - watchdog timer is running.
  //   1 - reset required (normal mode)
  //   2 - reset required (extended mode)
  //  -1 - other condition

#ifdef  USE_GBKA
  if (task0stat > 0) {
    // Serial.print(">>> task0_wrapper() returned "); Serial.println(task0stat);
  }
#endif  // USE_GBKA

// -------------------------------------

  // task1 - Blink LED to show the current status

  task1stat = task1_wrapper();

#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 1)
  if (task1stat >= 1) {
      Serial.print("# *** RESET reqired. *** retval = "); Serial.println(task1stat);
  }
#endif  // (DEBUG_LEVEL >= 1)
#endif  // USE_GBKA

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

#ifdef  USE_TASKX_INSTEADOF_TASK4

  // taskX - Blink LED using the notification pin (for debugging)

  // Since current version of taskX_wrapper() just blinks a LED,
  // taskX_wrapper() always returns zero.

  taskXstat = taskX_wrapper();

#else   // if not USE_TASKX_INSTEADOF_TASK4

  // task4 - Generate notification signal for Raspberry Pi

  task4stat = task4_wrapper();

// task4_wrapper() returns:
//   0 - notification is NOT activated
//   1 - notification is activated
//  -1 - other condition

#endif  // USE_TASKX_INSTEADOF_TASK4

// -------------------------------------

#ifdef  USE_GBKA
#if     (DEBUG_LEVEL == 0)
  Serial.print("# "); Serial.print(task0stat);
  Serial.print("  "); Serial.print(task1stat);
<  Serial.print("  "); Serial.print(task2stat);
  Serial.print("  "); Serial.print(task3stat);
#ifdef  USE_TASKX_INSTEADOF_TASK4
  Serial.print("  "); Serial.print(taskXstat);
#else   // if not USE_TASKX_INSTEADOF_TASK4
  Serial.print("  "); Serial.print(task4stat);
#endif  // USE_TASKX_INSTEADOF_TASK4
  Serial.println();
  delay(50);
#endif  // (DEBUG_LEVEL >= 0)
#endif  // USE_GBKA

  // -------------------------------------

  // *** End of loop() ***

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
