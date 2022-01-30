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
  classBlinkLED(int pin);
  void set(int arg1, int arg2);
  boolean blink();
  void stop();
 protected:
  int _pin = -1;
  int _arg1 = -1;
  int _arg2 = -1;
  int _prev_arg1 = 0;
  int _prev_arg2 = 0;
  boolean _flag = false;
  uint32_t _next_8ms = 0;
};

// ---------------------------------------------------------

#endif  // __CLASS_BLINK_LED_H__
