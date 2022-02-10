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
  boolean blink();
  void stop();
  void start();
	int stat();
 protected:
  int32_t _updateTnext_ms();
  int _pin = -1; // PIN No.
  int32_t _T0_ms = 1;         // Duration of T0
  int32_t _T1_ms = 1;         // Duration of T1
  int32_t _T2_ms = 1;         // Duration of T2
  int32_t _T0start_ms = 0;    // Millis of the last start of T0
  int32_t _T1start_ms = 0;    // Millis of the last start of T1
  int32_t _T2start_ms = 0;    // Millis of the last start of T2
  uint16_t _N1 = 1;     // Number of inner loop
  uint16_t _N1now = 0;  // Current count of the inner loop
  uint16_t _N2 = 0;     // Number of outer loop
  uint16_t _N2now = 0;  // Current count of the outer loop
  boolean _LEDstat = true; // !!!
  int _blinkCounter = 0;
  int _blinkCounterPrev = -1;
  uint32_t _Tnext_ms = 0;
  boolean _positiveLogic = true; // true: positive logic (HIGH is to turn LED on), false: negative logic (LOW is to turn LED on)
  boolean _flag_blink = false;
  boolean _flag_reverseAction = false;
  boolean _flag_useT2 = false;
  boolean _flag_stop = false;
};

// ---------------------------------------------------------

#endif  // __CLASS_BLINK_LED_H__
