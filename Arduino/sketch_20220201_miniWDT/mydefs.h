#ifndef __MYDEFS_H__
#define __MYDEFS_H__

//
// mydefs.h for for miniWDT
//

// ---------------------------------------------------------

// History:
// First version: Tue Feb  1 09:53:38 JST 2022 by @hohno_at_kuimc
// Revised: Thu Feb  3 12:59:16 JST 2022 for miniWDT

// ---------------------------------------------------------

#define TEST_MODE

#ifdef TEST_MODE
const int testMode = true;
#else // TEST_MODE
const int testMode = false;
#endif // TEST_MODE

// ---------------------------------------------------------

#define USE_GBKA

#define DEBUG_LEVEL  (2)

// ---------------------------------------------------------

#ifdef  USE_GBKA
#define IS_PIN_OK(x)  ((x > 0) && (x <= 13))
#else   // if not USE_GBKA (ATtiny85)
#define IS_PIN_OK(x)  ((x >= 0) && (x <= 5))
#endif  // USE_GBKA

#define SW_ON       (1)
#define SW_OFF      (0)
#define SW_UNKNOWN  (-1)

#define POSITIVE_LOGIC  (true)
#define NEGATIVE_LOGIC  (false)

#define REVERSE_ACTION  (true)
#define NORMAL_ACTION   (false)

#define USE_PULLUP  (true)
#define NO_PULLUP   (false)

// ---------------------------------------------------------

#define ALERT_UNDEF     (-999)
#define ALERT_BEFORE_START  (-1) //  -1 : watchdog is not started.
#define ALERT_LEVEL_0   (0)  //  0 : watchdog is running
#define ALERT_LEVEL_1   (1)  //  1 : watchdog has just detected timeout now
#define ALERT_LEVEL_2   (2)  //  2 : rebooting
#define ALERT_LEVEL_3   (3)  //
#define ALERT_LEVEL_4   (4)  //


#define RESET_BEFORE_SETUP  (-1) // -1 : not initialized
#define RESET_STEP_0  (0)   //  0 : resetting is not started (step0)
#define RESET_STEP_1  (1)   //  1 : resetting in progress (step1)
#define RESET_STEP_2  (2)   //  2 : resetting in progress (step2)
#define RESET_STEP_3  (3)   //  3 : resetting in progress (step3)
#define RESET_STEP_4  (4)   //  4 : resetting has been finished.

// ---------------------------------------------------------

#ifdef  USE_GBKA
#define PIN_I_PULSE   (6)
#define PIN_O_LED     (4)
#define PIN_I_REQ     (7)
#define PIN_I_TYPE    (PIN_I_REQ)
#define PIN_O_RESET   (8)
#define PIN_O_NOTE    (12)
//
#else   // if not USE_GBKA (such as ATtiny85)
#define PIN_I_PULSE   (0)
#define PIN_O_LED     (1)
#define PIN_I_REQ     (2)
#define PIN_I_TYPE    (PIN_I_REQ)
#define PIN_O_RESET   (3)
#define PIN_O_NOTE    (4)
#endif  // USE_GBKA

// ---------------------------------------------------------

#ifdef  USE_GBKA
#define LOGIC_HBEAT      NEGATIVE_LOGIC // LOW is to recognize headeat pulse
#define LOGIC_LED        POSITIVE_LOGIC // HIGH is to turn LED on
#define LOGIC_DELAY      POSITIVE_LOGIC // HIGH is to designate the delayed WDT
// #define LOGIC_RESET      NEGATIVE_LOGIC // LOW is to make a reset pulse
#define LOGIC_RESET      POSITIVE_LOGIC // HIGH is to make a reset pulse
#define LOGIC_NOTE       NEGATIVE_LOGIC // LOW is to make a notification
#else   // if not USE_GBKA
#define LOGIC_HBEAT      NEGATIVE_LOGIC // LOW is to recognize headeat pulse
#define LOGIC_LED        POSITIVE_LOGIC // HIGH is to turn LED on
#define LOGIC_WDYPE      POSITIVE_LOGIC // HIGH is to designate the delayed WDT
#define LOGIC_RESET      NEGATIVE_LOGIC // LOW is to make a reset pulse
#define LOGIC_NOTE       NEGATIVE_LOGIC // LOW is to make a notification
#endif  // USE_GBKA


#define AVR_GET_PULSE (digitalRead(PIN_I_PULSE) == (LOGIC_HBEAT ? HIGH : LOW))

#define AVR_GET_REQ   (digitalRead(PIN_I_REQ)   == (LOGIC_DELAY ? HIGH : LOW))

#define AVR_LED_ON    (digitalWrite(PIN_O_LED, LOGIC_LED ? HIGH : LOW))
#define AVR_LED_OFF   (digitalWrite(PIN_O_LED, LOGIC_LED ? LOW : HIGH))

#define AVR_NOTE_ON   (digitalWrite(PIN_O_NOTE, LOGIC_NOTE ? HIGH : LOW))
#define AVR_NOTE_OFF  (digitalWrite(PIN_O_NOTE, LOGIC_NOTE ? LOW : HIGH))

#define AVR_RESET_ON  (digitalWrite(PIN_O_RESET, LOGIC_RESET ? HIGH : LOW))
#define AVR_RESET_OFF (digitalWrite(PIN_O_RESET, LOGIC_RESET ? LOW : HIGH))

// ---------------------------------------------------------

#define SEC_BEFORE1   (90)
#define SEC_PULSE1    (1)
#define SEC_AFTER1    (1)

#define SEC_BEFORE2   (30)
#define SEC_PULSE2    (900)
#define SEC_AFTER2    (1)

#define HB_INTERVAL_S_MS  (30 * 1000L)   // default timeout for heartbeat
#define HB_INTERVAL_L_MS  (90 * 1000L)   // longer timeout for heartbeat

// ---------------------------------------------------------

struct pinInfo {
  uint8_t stat;
  uint32_t timstamp;
};

// ---------------------------------------------------------

#endif  // __MYDEFS_H__
