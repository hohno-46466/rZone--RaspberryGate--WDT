#ifndef __MYDEFS_H__
#define __MYDEFS_H__

//
// mydefs.h
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// task0 - Check the "heart beat" pulse from Raspberry Pi
// task1 - Blink LED to show the current status
// task2 - Detect type-specified request from Raspberry Pi
// task3 - Generate RESET pulse (for both of the gentle and the delayed watchdog)
// task4 - Generate notification signal for Raspberry Pi
// taskX - Blink LED using the notification pin (for debugging)

// ---------------------------------------------------------

#define USE_GBKA
#define DEBUG_LEVEL  (3)

#define USE_TASKX_INSTEAD_OF_TASK4

// ---------------------------------------------------------

const int PulseCounterSize = 30; // Maximum watchdog

// ---------------------------------------------------------

#define HEARTBEAT_LOST  (task0stat >= 1)
#define EXTENDED_MODE   (task0stat >= 2)
#define DELAYED_REBOOT  (task2stat == 1)

// ---------------------------------------------------------

#define IS_PIN_OK(x)	(x > 0)	// This should be updated to check more

#define SW_ON			(1)
#define SW_OFF			(0)
#define SW_UNKNOWN	(-1)

// ---------------------------------------------------------

#ifdef  USE_GBKA
#define PIN_I_PULSE   (6)
#define PIN_O_LED     (4)
#define PIN_I_REQ     (7)
#define PIN_O_RESET   (8)
#define PIN_O_NOTE    (12)
//
#else   // if not USE_GBKA
#define PIN_I_PULSE   (0)
#define PIN_O_LED     (1)
#define PIN_I_REQ     (2)
#define PIN_O_RESET   (3)
#define PIN_O_NOTE    (4)
#endif  // USE_GBKA

// ---------------------------------------------------------

#ifdef  USE_GBKA
#define AVR_GET_PULSE (digitalRead(PIN_I_PULSE) == HIGH)
#else   // if not USE_GBKA
#define AVR_GET_PULSE (digitalRead(PIN_I_PULSE) == LOW)
#endif  // USE_GBKA
#define AVR_GET_REQ   digitalRead(PIN_I_REQ)

#define AVR_LED_ON    (digitalWrite(PIN_O_LED, HIGH))
#define AVR_LED_OFF   (digitalWrite(PIN_O_LED, LOW))

#define AVR_NOTE_ON   (digitalWrite(PIN_O_NOTE, LOW))
#define AVR_NOTE_OFF  (digitalWrite(PIN_O_NOTE, HIGH))

#define AVR_RESET_ON  (digitalWrite(PIN_O_RESET, LOW))
#define AVR_RESET_OFF (digitalWrite(PIN_O_RESET, HIGH))

// ---------------------------------------------------------

#endif  // __MYDEFS_H__
