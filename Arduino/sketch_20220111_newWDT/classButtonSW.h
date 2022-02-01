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
  classButtonSW(int pin, boolean pullup, boolean positive);
  boolean init(int pin, boolean pullup, boolean positive);
  int setParam(int updown);
  boolean update();
  int getStat();
 protected:
  const int _LEVEL_MIN = 0;
  const int _LEVEL_MAX = 100;
  const int _LEVEL_H   = 80;  // Threshold level from Low to High
  const int _LEVEL_L   = 20;  // Threshold level from High to Low
  int _pin    = -1;
  int _state  = -1;
  int _currentVal = 0;  // currentVal goes up and down between _LEVEL_MIN and _LEVEL_MAX
  int _updown = 15;
  uint32_t _Tnext_8ms = 0;
  boolean _positive = true; // true: positive logic, false: negative logic
};

// ---------------------------------------------------------

#endif  // __CLASS_BUTTON_SW_H__
