//
// sketch_20220201_miniWDT.ino
//

// ---------------------------------------------------------

// History:
// First version: Wed Feb  2 19:15:12 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

#include "inputPins.h"
#include "outputPins.h"
#include "mydefs.h"

int alertLevel = ALERT_BEFORE_START;
int32_t HBinterval_ms = -1;
int32_t HBintervalLimit_ms = HB_INTERVAL_L_MS;

inputPins iPins;
outputPins oPins;

// ---------------------------------------------------------

void setup() {

  iPins.init();
  oPins.init();

  HBinterval_ms = -1;
  HBintervalLimit_ms = HB_INTERVAL_L_MS;

  oPins.setBlinking(1, 1, 1, -1, -1, false);
}

// ---------------------------------------------------------

// AlertLevel:
// -1 : watchdog is not started.
//  0 : watchdog is running
//  1 : watchdog has detected timeout just now
//  2 : rebooting

void loop() {
  loopX2();
}

// ---------------------------------------------------------

classBlinkLED test;

void loopX2() {

  // int step1_s, step2_s, step3_s;

  iPins.update();
  oPins.update();


}

// ---------------------------------------------------------

void loopX1() {

  int step1_s, step2_s, step3_s;

  iPins.update();
  oPins.update();

  if (alertLevel < 0) {

    // in case watchdog is not initialized
    iPins.init();
    oPins.init();
    alertLevel = ALERT_LEVEL_0; // watchdog has just started.

  } else if (alertLevel == ALERT_LEVEL_0) {

    // watchdog is running
    HBinterval_ms = iPins.getHBinterval_ms();

    if (HBinterval_ms >= (HBintervalLimit_ms)) {

      // watchdog alert!
      alertLevel = ALERT_LEVEL_1;

    } else {

      // watchdog keeps running
      if (HBinterval_ms < 0) {
        // if HBinterval_ms is less than zero, it means that there is no heartbeat pulse before (rebooting is in progress?).
        // In this case, we need to set longer interval limit
        HBintervalLimit_ms = HB_INTERVAL_L_MS;

      } else {
        // We set shorter interval because heartbeat has been running
        HBintervalLimit_ms = HB_INTERVAL_S_MS;
      }
    }

  } else if (alertLevel >= ALERT_LEVEL_1) {

    // watchdog timer has timed out.

    if (alertLevel == ALERT_LEVEL_1) {
      // for the first time...
      if (iPins.getWDtype() == 0) {
        step1_s = SEC_BEFORE1;
        step2_s = SEC_PULSE1;
        step3_s = SEC_AFTER1;
      } else {
        step1_s = SEC_BEFORE2;
        step2_s = SEC_PULSE2;
        step3_s = SEC_AFTER2;
      }
      oPins.setResetPulse(step1_s, step2_s, step3_s);
      oPins.setNotification(step1_s);
      oPins.setBlinking(step1_s, step2_s, step3_s, -1, -1, false);
      alertLevel = ALERT_LEVEL_2;

    } else {
      // alertLevel >= ALERT_LEVEL_2 means resetting is in progress

      // Return value of oPins.getResetState()
      // -1 : not initialized
      //  0 : resetting is not started (step0)
      //  1 : resetting in progress (step1)
      //  2 : resetting in progress (step2)
      //  3 : resetting in progress (step3)
      //  4 : resetting has been finished.
      if (oPins.getResetStat() >= RESET_STEP_4) {
        // rebooting process has been done
        alertLevel = ALERT_BEFORE_START; // watchdog runs again after initialization
        HBinterval_ms = HB_INTERVAL_L_MS; // since the target device (such as RPi) might be rebooting, use longer timeout
      }
    }
  }
}

// ---------------------------------------------------------
