//
// stateMachine.ino
//

// ---------------------------------------------------------
// ---------------------------------------------------------

#ifdef TEST_MODE

void updateStateMachine4test() {

  // int _T0_s, _T1_s, _T2_s;
  static int32_t _HBinterval_prev_ms = 0;
  static int32_t _HBstat = 0, _HBstat_prev = 0;


  if (globalTestFlag2) {
    int tmpval = iPins.getHBcurrentButtonVal();
#ifdef USE_GBKA
    Serial.print("HBcurrentButtonVal = ");
    Serial.print(tmpval);
    Serial.println();
#endif // USE_GBKA
    globalTestFlag2 = false;
  }

  // alertLevel is -1 when the sketch starts
  if (alertLevel < 0) {

    // The following initialization are required when alertLevel is -1
    // iPins.init();
    // oPins.init();

    // alertLevel -1 -> 0 // watchdog has just started.
    prevLevel = alertLevel;
    alertLevel = ALERT_LEVEL_0;
    if (prevLevel != alertLevel) {
#ifdef USE_GBKA
      Serial.print("# alertLevel = "); Serial.print(prevLevel);
      Serial.print(" -> "); Serial.print(alertLevel);
      Serial.println();
#endif // USE_GBKA
    }

    // alert Level 0
  } else if (alertLevel == ALERT_LEVEL_0) {

    // watchdog is running
    HBinterval_ms = iPins.getHBinterval_ms();

    _HBstat = iPins.getHBstat();
    if (_HBstat != _HBstat_prev) {
      Serial.print("# _HBstat = "); Serial.print(_HBstat);
      Serial.println();
      if (_HBstat == 0) {
        iPins.showHBhistory();
      }
    }
    _HBstat_prev = _HBstat;

    if (HBinterval_ms != _HBinterval_prev_ms) {
#ifdef USE_GBKA
      Serial.print("# alertLevel = "); Serial.print(alertLevel);
      Serial.print(", HBinterval_ms = "); Serial.print(_HBinterval_prev_ms);
      Serial.print(" -> "); Serial.print(HBinterval_ms);
      Serial.println();
#endif // USE_GBKA
    }
    _HBinterval_prev_ms = HBinterval_ms;

    if (HBinterval_ms >= (HBintervalLimit_ms)) {
      // alertLevel 0 -> 1 // watchdog alert!
      prevLevel = alertLevel;
      // alertLevel = ALERT_LEVEL_1;
#ifdef USE_GBKA
      Serial.print("# alertLevel changed: "); Serial.print(prevLevel);
      Serial.print(" -> "); Serial.print(alertLevel);
      Serial.println();
#endif // USE_GBKA
    }
  }
}
#endif // TEST_MODE

// ---------------------------------------------------------

#ifdef TEST_MODE

void updateStateMachine4testX() {

  int _T0_s, _T1_s, _T2_s;

  // alertLevel is -1 when the sketch starts
  if (alertLevel < 0) {

    // in case watchdog is not initialized
    iPins.init();
    oPins.init();

    // alertLevel -1 -> 0 // watchdog has just started.
    prevLevel = alertLevel;
    alertLevel = ALERT_LEVEL_0;
    if (prevLevel != alertLevel) {
#ifdef USE_GBKA
#endif // USE_GBKA

      Serial.print("# alertLevel = "); Serial.print(prevLevel);
      Serial.print(" -> "); Serial.println(alertLevel);
    }

  // alert Level 0
  } else if (alertLevel == ALERT_LEVEL_0) {

    // watchdog is running
    HBinterval_ms = iPins.getHBinterval_ms();

    if (HBinterval_ms >= (HBintervalLimit_ms)) {

      // alertLevel 0 -> 1 // watchdog alert!
      prevLevel = alertLevel;
      alertLevel = ALERT_LEVEL_1;
    if (prevLevel != alertLevel) {
#ifdef USE_GBKA
#endif // USE_GBKA

      Serial.print("# alertLevel = "); Serial.print(prevLevel);
      Serial.print(" -> "); Serial.println(alertLevel);
    }

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

  // alertLevel >= 1
  } else if (alertLevel >= ALERT_LEVEL_1) {

    // watchdog timer has timed out.

    // alertLevel == 1
    if (alertLevel == ALERT_LEVEL_1) {
      // for the first time...
      if (iPins.getWDtype() == 0) {
        _T0_s = SEC_BEFORE1;
        _T1_s = SEC_PULSE1;
        _T2_s = SEC_AFTER1;
      } else {
        _T0_s = SEC_BEFORE2;
        _T1_s = SEC_PULSE2;
        _T2_s = SEC_AFTER2;
      }
      oPins.setResetPulse(_T0_s * 1000L, _T1_s * 1000L, _T2_s * 1000L);
      oPins.setNotification(_T0_s * 1000L);
      oPins.setBlinking(_T0_s * 1000L, _T1_s * 1000L, _T2_s * 1000L, -1, -1, false);
      oPins.startResetPulse();
      oPins.startNotification();
      oPins.startBlinking();

      // alertLevel 1 -> 2
      prevLevel = alertLevel;
      alertLevel = ALERT_LEVEL_2;
      if (prevLevel != alertLevel) {
#ifdef USE_GBKA
#endif // USE_GBKA

        Serial.print("# alertLevel = "); Serial.print(prevLevel);
        Serial.print(" -> "); Serial.println(alertLevel);
      }

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

        // alertLevel 2 -> -1
        prevLevel = alertLevel;
        alertLevel = ALERT_BEFORE_START; // watchdog runs again after initialization
        if (prevLevel != alertLevel) {
#ifdef USE_GBKA
#endif // USE_GBKA

          Serial.print("# alertLevel = "); Serial.print(prevLevel);
          Serial.print(" -> "); Serial.println(alertLevel);
        }

        HBinterval_ms = HB_INTERVAL_L_MS; // since the target device (such as RPi) might be rebooting, use longer timeout
      }
    }
  }
}

#endif // TEST_MODE

#ifdef TEST_MODE
#endif // TEST_MODE


// ---------------------------------------------------------
// ---------------------------------------------------------

void updateStateMachine4main() {

  int _T0_s, _T1_s, _T2_s;

  // alertLevel is -1 when the sketch starts
  if (alertLevel < 0) {

    // in case watchdog is not initialized
    iPins.init();
    oPins.init();

    // alertLevel -1 -> 0 // watchdog has just started.
    prevLevel = alertLevel;
    alertLevel = ALERT_LEVEL_0;

  // alert Level 0
  } else if (alertLevel == ALERT_LEVEL_0) {

    // watchdog is running
    HBinterval_ms = iPins.getHBinterval_ms();

    if (HBinterval_ms >= (HBintervalLimit_ms)) {

      // alertLevel 0 -> 1 // watchdog alert!
      prevLevel = alertLevel;
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

  // alertLevel >= 1
  } else if (alertLevel >= ALERT_LEVEL_1) {

    // watchdog timer has timed out.

    // alertLevel == 1
    if (alertLevel == ALERT_LEVEL_1) {
      // for the first time...
      if (iPins.getWDtype() == 0) {
        _T0_s = SEC_BEFORE1;
        _T1_s = SEC_PULSE1;
        _T2_s = SEC_AFTER1;
      } else {
        _T0_s = SEC_BEFORE2;
        _T1_s = SEC_PULSE2;
        _T2_s = SEC_AFTER2;
      }
      oPins.setResetPulse(_T0_s * 1000L, _T1_s * 1000L, _T2_s * 1000L);
      oPins.setNotification(_T0_s * 1000L);
      oPins.setBlinking(_T0_s * 1000L, _T1_s * 1000L, _T2_s * 1000L, -1, -1, false);
      oPins.startResetPulse();
      oPins.startNotification();
      oPins.startBlinking();

      // alertLevel 1 -> 2
      prevLevel = alertLevel;
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

        // alertLevel 2 -> -1
        prevLevel = alertLevel;
        alertLevel = ALERT_BEFORE_START; // watchdog runs again after initialization

        HBinterval_ms = HB_INTERVAL_L_MS; // since the target device (such as RPi) might be rebooting, use longer timeout
      }
    }
  }
}

// ---------------------------------------------------------
// ---------------------------------------------------------
