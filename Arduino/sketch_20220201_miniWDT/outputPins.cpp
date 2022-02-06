//
// outputPins.cpp
//

// ---------------------------------------------------------

// History:
// First version: Wed Feb  2 19:15:12 JST 2022 by @hohno_at_kuimc


// ---------------------------------------------------------

#include "Arduino.h"
#include "outputPins.h"
#include "mydefs.h"

// extern uint32_t Currenttime_sec;

// ---------------------------------------------------------

outputPins::outputPins() {

}

// ---------------------------------------------------------

boolean outputPins::init() {

  _LED.init(PIN_O_LED, true);
  _LED.setParam(1, 1, true);
  _LED.start();

  _RST.init(PIN_O_RESET, true);
  _RST.setParam(1, 1, true);
  _RST.stop();

  _NOTE.init(PIN_O_NOTE, true);
  _NOTE.setParam(1, 1, true);
  _NOTE.stop();

  return(false);
}

// ---------------------------------------------------------

boolean outputPins::update() {

  _LED.blink();
  _RST.blink();
  _NOTE.blink();

  return(false);
}

// ---------------------------------------------------------

boolean outputPins::setResetPulse(int step1_s, int step2_s, int step3_s) {

  _RST.setParam(step1_s, step2_s, step3_s, 0, 0, false);

  return(false);
}

// ---------------------------------------------------------

boolean outputPins::setNotification(int step1_s) {

  _NOTE.setParam(step1_s, 1, 1, 0, 0, false);

  return(false);
}

// ---------------------------------------------------------

boolean outputPins::setBlinking(int step1_s, int step2_s, int step3_s, int N1, int N2, boolean reverse)  {


  _LED.setParam(step1_s, step2_s, step3_s, N1, N2, reverse);

  return(false);
}

// ---------------------------------------------------------

int outputPins::getResetStat() {

  return(-1);
}

// ---------------------------------------------------------
