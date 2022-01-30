#ifndef __CLASS_BUTTON_SW_H__
#define __CLASS_BUTTON_SW_H__

//
// classButtonSW.h
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// classButtonSW --

// ---------------------------------------------------------

#include "Arduino.h"

class classButtonSW {
 public:
  classButtonSW();
  void init(int pin);
  int set(int updown);
  boolean update();
  boolean get();
 protected:
  int _pin = -1;
  int _currentVal = 0;
  boolean _state = false;
  uint32_t _next_8ms = 0;
  const int _LEVEL_MIN = 0;
  const int _LEVEL_MAX = 100;
  const int _LEVEL_H   = 80;
  const int _LEVEL_L   = 20;
  int _updown = 15;
};

// ---------------------------------------------------------

#endif  // __CLASS_BUTTON_SW_H__
