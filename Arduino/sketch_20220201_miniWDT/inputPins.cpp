//
// inputPins.cpp
//

// ---------------------------------------------------------

// History:
// First version: Wed Feb  2 19:15:12 JST 2022 by @hohno_at_kuimc


// ---------------------------------------------------------

#include "Arduino.h"
#include "inputPins.h"
#include "mydefs.h"

// extern uint32_t Currenttime_sec;

// ---------------------------------------------------------

inputPins::inputPins() {

}

// ---------------------------------------------------------

boolean inputPins::init() {

  boolean _HBlogic = LOGIC_HBEAT;
  boolean _WDlogic = LOGIC_DELAY;

  _HB.init(PIN_I_PULSE, USE_PULLUP, _HBlogic);
  _WD.init(PIN_I_TYPE, USE_PULLUP, _WDlogic);
  _HBstat = -1;
  _WDstat = -1;
  _HBprev_ms = 0;
  return(true);
}

// ---------------------------------------------------------

boolean inputPins::update() {

  _HB.update();
  _WD.update();

  return(true);
}

// ---------------------------------------------------------

int32_t inputPins::getHBinterval_ms() {

  uint32_t __currentT_ms = millis();
  int32_t __interval_ms = 0;

  // __interval_ms = (int32_t)(__currentT_ms - _HBprev_ms);

  _HBstat = _HB.getStat();

  if ((_HBprev != _HBstat) && (_HBstat == SW_ON)) {
    __interval_ms = (int32_t)(__currentT_ms - _HBprev_ms);
    _HBprev_ms = __currentT_ms;
  }
  _HBprev = _HBstat;

  return(__interval_ms);
}

// ---------------------------------------------------------

int inputPins::getWDtype() {

  _WDstat = _WD.getStat();

  return(_WDstat);
}

// ---------------------------------------------------------
// ---------------------------------------------------------

#ifdef TEST_MODE

int inputPins::getHBstat() {
  return(_HBstat);
}

int inputPins::getWDstat() {
  return(_WDstat);
}

int inputPins::getHBcurrentButtonVal() {
  return(_HB.getCurrentButtonVal());
}

void inputPins::showHBhistory() {
  _HB.showOnOffHistory();
}

#endif // TEST_MODE

// ---------------------------------------------------------
// ---------------------------------------------------------
