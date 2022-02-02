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

class outputPins {
 public:
  outputPins();
  boolean init();
  boolean update();
  boolean startResetPulse(int, int, int);
  boolean startNotification(int);
  boolean startBlinking(int, int, int);
  int getResetStat();
 private:
  boolean _verbose = false;
};

// ---------------------------------------------------------

#endif  // __OUTPUT_PINS__H__
