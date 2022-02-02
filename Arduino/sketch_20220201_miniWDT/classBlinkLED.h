#ifndef __CLASS_BLINK_LED_H__
#define __CLASS_BLINK_LED_H__

//
// classBlinkLED.h
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// classBlinkLED -- Blink LED to show the current status

// ---------------------------------------------------------

#include "Arduino.h"

class classBlinkLED {
 public:
  classBlinkLED();
  classBlinkLED(int pin, boolean positive);
  boolean init(int pin, boolean positive);
  void setParam(int Ton, int Toff);
  void setParam(int T0, int T1, int T3, int N);
  boolean blink();
  void stop();
 protected:
  int _pin = -1;
  int _Ton = -1;
  int _Toff = -1;
  int _prev_Ton = 0;
  int _prev_Toff = 0;
  int _T0 = 0;
  int _T1 = 1;
  int _T2 = 1;
  boolean _LEDstat = false;
  uint32_t _Tnext_8ms = 0;
  boolean _positive = true; // true: positive logic (HIGH is to turn LED on), false: negative logic (LOW is to turn LED on)
};

// ---------------------------------------------------------

#endif  // __CLASS_BLINK_LED_H__
