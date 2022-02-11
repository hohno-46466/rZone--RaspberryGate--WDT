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
  //
  boolean setResetPulse(int32_t T0_ms, int32_t T1_ms, int32_t T2_ms);
  boolean setNotification(int32_t T1_ms);
  boolean setBlinking(int32_t T0_ms, int32_t T1_ms, int32_t T2_ms, int N1, int N2, boolean reverseAction);
  //
  boolean startResetPulse();
  boolean startNotification();
  boolean startBlinking();
  //
  boolean stopResetPulse();
  boolean stopNotification();
    boolean stopBlinking();
    //
  int getResetStat();
 private:
  boolean _verbose = false;
  classBlinkLED   _LED;
  classBlinkLED   _RST;
  classBlinkLED   _NOTE;

};

// ---------------------------------------------------------

#endif  // __OUTPUT_PINS__H__
