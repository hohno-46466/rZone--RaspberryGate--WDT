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

// ---------------------------------------------------------

// constructor

outputPins::outputPins() {
  // nothing to do here
  // since _LED, _RST, _NOTE are prepared as the private member, we don't need to use constructor for these three objects here.
}

// ---------------------------------------------------------

boolean outputPins::init() {

  _LED.init(PIN_O_LED, POSITIVE_LOGIC);
  _LED.setParam(1, 1, NORMAL_ACTION);
  _LED.start();

  _RST.init(PIN_O_RESET, POSITIVE_LOGIC);
  _RST.setParam(1, 1, NORMAL_ACTION);
  _RST.stop();

  _NOTE.init(PIN_O_NOTE, POSITIVE_LOGIC);
  _NOTE.setParam(1, 1, NORMAL_ACTION);
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

boolean outputPins::setResetPulse(int32_t T0_ms, int32_t T1_ms, int32_t T2_ms) {

  _RST.stop();
  _RST.setParam(T0_ms, T1_ms, T2_ms, 0, 0, NORMAL_ACTION);

  // set a (single) RESET pulse as follows:
  //   step1: T0(ms) for the first guard time
  //   step2: T1(ms) for the NOTIFICATION
  //   step3: T2(ms) sec for the second guard time

  return(false);
}

// ---------------------------------------------------------

boolean outputPins::setNotification(int32_t T1_ms) {

  _NOTE.stop();
  _NOTE.setParam(1000, T1_ms, 1000, 0, 0, NORMAL_ACTION);

  // set a (single) NOTIFICATION pulse as follows:
  //   step1: T0(ms) sec for the first guard time
  //   step2: 1sec for the NOTIFICATION
  //   step3: 1sec for the second guard time

  return(false);
}

// ---------------------------------------------------------

boolean outputPins::setBlinking(int32_t T0_ms, int32_t T1_ms, int32_t T2_ms, int N1, int N2, boolean reverseAction)  {

  _LED.stop();
  _LED.setParam(T0_ms, T1_ms, T2_ms, N1, N2, reverseAction);

  // if reverse is NORMAL_ACTION, then
  //   Repeat the following outer loop N2+1 times
  //     Repeat the following inner loop N1+1 times
  //       Turn LED OFF for T0(ms)
  //       Turn LED ON for T1(ms)
  //     End of the inner loop
  //     Turn LED OFF for T2(ms)
  //   End of the outer loop
  // endif

  // if reverse is REVERSE_ACTION, then
  //   Repeat the following outer loop N2+1 times
  //     Repeat the following inner loop N1+1 times
  //       Turn LED ON for T0(ms)
  //       Turn LED OFF for T1(ms)
  //     End of the inner loop
  //     Turn LED ON for T2(ms)
  //   End of the outer loop
  // endif

  return(false);
}

// ---------------------------------------------------------

boolean outputPins::startResetPulse() {

  _RST.start();

  return(true);
}

// ---------------------------------------------------------


boolean outputPins::startNotification() {

  _NOTE.start();

  return(true);
}

// ---------------------------------------------------------

boolean outputPins::startBlinking() {

  _LED.start();

  return(true);
}

// ---------------------------------------------------------

boolean outputPins::stopResetPulse() {

  _RST.stop();

  return(true);
}

// ---------------------------------------------------------

boolean outputPins::stopNotification() {

  _NOTE.stop();

  return(true);
}

// ---------------------------------------------------------

boolean outputPins::stopBlinking() {

  _LED.stop();

  return(true);
}

// ---------------------------------------------------------

int outputPins::getResetStat() {

  return(true);
}

// ---------------------------------------------------------
