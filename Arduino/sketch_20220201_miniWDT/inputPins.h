#ifndef __INPUT_PINS_H__
#define __INPUT_PINS_H__

//
// inputPins.h
//

// ---------------------------------------------------------

// History:
// First version: Wed Feb  2 19:15:12 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

#include "Arduino.h"
#include "classButtonSW.h"
#include "mydefs.h"

class inputPins {
 public:
  inputPins();
  boolean init();
  boolean update();
  //
  int32_t getHBinterval_ms();
  int getWDtype();
#ifdef TEST_MODE
  int getHBstat();
  int getWDstat();
  int getHBcurrentButtonVal();
  void showHBhistory();
#endif // TEST_MODE
  //
 private:
  boolean _verbose = false;
  classButtonSW _HB;  // pin for heartbeat pulse
  classButtonSW _WD;  // pin for Watchdog Type
  int _HBstat = -1;
  int _WDstat = -1;
  int _HBprev = -1;
  int _WDprev = -1;
  uint32_t _HBprev_ms = 0;
};

// ---------------------------------------------------------

#endif  // __INPUT_PINS_H__
