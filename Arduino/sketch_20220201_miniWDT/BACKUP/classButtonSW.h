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
  int setSensitivity(int updown);
  boolean update();
  int getStat();
  uint32_t getLastONtoOFF();
  uint32_t getLastOFFtoON();
  //
 protected:
  const uint8_t _LEVEL_MIN = 0;
  const uint8_t _LEVEL_MAX = 0xff;
  const uint8_t _LEVEL_L2H = 0xe0;  // Threshold level from Low to High
  const uint8_t _LEVEL_H2L = 0x20;  // Threshold level from High to Low
  uint8_t _updown = 0x20;   // sensitivity
  int _pin    = -1;
  int _buttonState  = -1;   // assign one of SW_ON, SW_OFF, or SW_UNKNOWN
  int _currentVal = 0;      // currentVal goes up and down between _LEVEL_MIN and _LEVEL_MAX

  // uint32_t _Tnext_ms = 0;
  boolean _positive = true; // true: positive logic, false: negative logic
  boolean _pullup = true;   // true: use internal pullup
  uint32_t _last_ONtoOFF_ms = 0;
  uint32_t _last_OFFtoON_ms = 0;
};

// ---------------------------------------------------------

#endif  // __CLASS_BUTTON_SW_H__
