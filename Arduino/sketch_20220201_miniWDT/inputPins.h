#ifndef __INPUT_PINS__H__
#define __INPUT_PINS__H__

//
// inputPins.h
//

// ---------------------------------------------------------

// History:
// First version: Wed Feb  2 19:15:12 JST 2022 by @hohno_at_kuimc


// ---------------------------------------------------------

#include "Arduino.h"

class inputPins {
 public:
  inputPins();
  boolean init();
  boolean update();
  int32_t getHBinterval_ms();
  int getWDType();
 private:
  boolean _verbose = false;
};

// ---------------------------------------------------------

#endif  // __INPUT_PINS__H__
