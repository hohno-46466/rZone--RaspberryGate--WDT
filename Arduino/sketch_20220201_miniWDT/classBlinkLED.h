#ifndef __CLASS_BLINK_LED_H__
#define __CLASS_BLINK_LED_H__

//
// classBlinkLED.h for miniWDT
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc
// Revised: Thu Feb  3 12:59:16 JST 2022 for miniWDT

// ---------------------------------------------------------

// classBlinkLED -- Blink LED to show the current status

// ---------------------------------------------------------

#include "Arduino.h"

class classBlinkLED {
 public:
  classBlinkLED();
  classBlinkLED(int pin, boolean positiveLogic);
  boolean init(int pin, boolean positiveLogic);
  void setParam(int T0_s, int T1_s, boolean reverseAction);
  void setParam(int T0_s, int T1_s, int T2_s, int N, boolean reverseAction);
  void setParam(int T0_s, int T1_s, int T2_s, int N1, int N2, boolean reverseAction);
  boolean blink();            // update blinking. This function needs to be called very frequently, either directly or indirectly in main().
  void stop();
  void start();
  int blinkStat();
  int blinkCounter();
 protected:
  int32_t _updateTnext_ms();
  int _pin = -1;              // PIN No.
  int32_t _T0_ms = 1;         // Duration of T0
  int32_t _T1_ms = 1;         // Duration of T1
  int32_t _T2_ms = 1;         // Duration of T2
  int32_t _T0start_ms = 0;    // Millis of the last start of T0
  int32_t _T1start_ms = 0;    // Millis of the last start of T1
  int32_t _T2start_ms = 0;    // Millis of the last start of T2
  boolean _T2mode = false;    // T2 mode
  uint32_t _Tnext_ms = 0;
  uint16_t _N1 = 1;           // Number of inner loop
  uint16_t _N1now = 0;        // Current count of the inner loop
  uint16_t _N2 = 0;           // Number of outer loop
  uint16_t _N2now = 0;        // Current count of the outer loop
  boolean _LEDstat = true;    // A trick to start this sketch with the LED off
  int _blinkCounter = 0;
  int _blinkCounterPrev = -1;
  boolean _positiveLogic = true;  // true: positive logic (HIGH is to turn LED on), false: negative logic (LOW is to turn LED on)
  boolean _flag_blink = false;    // true: now blinking, false: blinking stopped
  boolean _flag_reverseAction = false;  // Take reverse action (useful for temporarily interpreting the actual LED blinking pattern as the opposite of normal blinking mode)
  boolean _flag_done = false;     // if true, blinking will be end at the end of the current loop
};

// ---------------------------------------------------------

#endif  // __CLASS_BLINK_LED_H__
