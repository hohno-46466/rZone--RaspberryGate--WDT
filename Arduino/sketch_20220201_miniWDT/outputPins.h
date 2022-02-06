#ifndef __OUTPUT_PINS__H__
#define __OUTPUT_PINS__H__

//
// outputPins.h
//

// ---------------------------------------------------------

// History:
// First version: Wed Feb  2 19:15:12 JST 2022 by @hohno_at_kuimc


// ---------------------------------------------------------

#include "Arduino.h"
#include "classBlinkLED.h"
#include "mydefs.h"

class outputPins {
 public:
  outputPins();
  boolean init();
  boolean update();
  boolean setResetPulse(int, int, int);
  boolean setNotification(int);
  boolean setBlinking(int, int, int, int, int, boolean);
  int getResetStat();
 private:
  boolean _verbose = false;
  classBlinkLED   _LED;
  classBlinkLED   _RST;
  classBlinkLED   _NOTE;

};

// ---------------------------------------------------------

#endif  // __OUTPUT_PINS__H__
