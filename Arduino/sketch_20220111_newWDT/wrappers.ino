//
// wrappers.ino
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// *** IMPORTANT NOTICE ***
// Since this sketch has an "ino" extention, this file will be inserted
// in the main sketch (sketch_20220111_newWDT.ino) before each compilation

// ---------------------------------------------------------

// ---------------------------------------------------------
// wrapper functions
// ---------------------------------------------------------

#ifdef  USE_TASKX_INSTEADOF_TASK4

int taskX_wrapper() {

  // example task: LED blinking

  // taskX.set(500,500); taskX.blink();

  if (debug_cnt == 0) {
    taskX.set(50,950);

  } else if (debug_cnt == 6) {
    taskX.set(250,750);

  } else if (debug_cnt == 12) {
    taskX.set(500,500);

  } else if (debug_cnt == 18) {
    taskX.set(750,250);

  } else if (debug_cnt == 24) {
    taskX.set(950,50);
  }
  taskX.blink();

  return(0);
}

#endif  // USE_TASKX_INSTEADOF_TASK4

// -------------------------------------

// task0_wrapper() returns:
//   0 - watchdog timer is running.
//   1 - reset required (normal mode)
//   2 - reset required (extended mode)
//  -1 - other condition

int task0_wrapper() {

  static int _pulsesPerNsec = 0, _pulsesPerNsec_prev = -1;
  static boolean _pulsesPerNsecStat = false;
  static int _retval = -1;
  const int _WDT_START_LEVEL = 8;
  const int _WDT_RESET_LEVEL = 3;
  // const int _Nsec = PulseCounterSize;

  // _pulsesPerNsec = task0core() * _Nsec; // task0core() returns avaraged number of pulses per second in float style
  _pulsesPerNsec = task0.core();

  if ((_pulsesPerNsecStat == false) && (_pulsesPerNsec > _WDT_START_LEVEL)) {
      _pulsesPerNsecStat = true;
      _retval = 0;

#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 1)
      Serial.print("# *** newWDT started. ***  "); Serial.println(_pulsesPerNsec);
#endif  // (DEBUG_LEVEL >= 1)
#endif  // USE_GBKA

  } else if ((_pulsesPerNsecStat == true) && (_pulsesPerNsec < _WDT_RESET_LEVEL)) {
      _pulsesPerNsecStat = false;
      if (_pulsesPerNsec > (PulseCounterSize + 10)) {
        _retval = 2;
      } else {
        _retval = 1;
      }
  }

    if (_pulsesPerNsec >= 0) {
      if (_pulsesPerNsec != _pulsesPerNsec_prev) {

#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 2)
        // Serial.print("# _pulsesPerNsec = "); Serial.println(_pulsesPerNsec);
#endif  // (DEBUG_LEVEL >= 2)
#endif  // USE_GBKA

        _pulsesPerNsec_prev = _pulsesPerNsec;
      }
    }

    return(_retval);
}

// -------------------------------------

int task1_wrapper() {

  // example task: LED blinking

  // task1_wrapper() always returns zero

  if (debug_cnt < 5) {
    task1.set(500,500); task1.blink();

  } else if (debug_cnt < 10) {
    task1.set(250,250); task1.blink();

  } else if (debug_cnt < 15) {
    task1.set(100,100); task1.blink();

  } else if (debug_cnt < 20) {
    task1.set(50,50); task1.blink();

  } else {
    task1.set(20,20); task1.blink();
  }

  return(0);
}

// -------------------------------------

// task2_wrapper() returns:
//   0 - delayed mode
//   1 - gentle mode
//  -1 - other condition

int task2_wrapper() {

  int _retval = -1;

  // int _retval = task2core();

  return(_retval);
}


// -------------------------------------

// task3_wrapper() returns:
//   0 - RESET pulse is NOT generated
//   1 - RESET is ongoing
//  -1 - other condition

int task3_wrapper() {

  static int _reset = 0;

#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 2)
  //    Serial.print("#*** CurrentTime_8ms = "); Serial.print(CurrentTime_8ms);
  //    Serial.print("  task0stat = "); Serial.println(task0stat);
#endif  // (DEBUG_LEVEL >= 1)
#endif  // USE_GBKA



#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 1)
  if (task1stat >= 1) {
    Serial.print("# *** RESET reqired. *** HEARTBEAT_LOST = "); Serial.println(HEARTBEAT_LOST);
  }
#endif  // (DEBUG_LEVEL >= 1)
#endif  // USE_GBKA


  if (HEARTBEAT_LOST && (_reset == 0)) {

#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 2)
    Serial.print("# task3_wrapper()  "); Serial.println(task0stat);
#endif  // (DEBUG_LEVEL >= 1)
#endif  // USE_GBKA

    uint32_t _gTime1 = EXTENDED_MODE ? (60*1000L) : 1000L;
    uint32_t _gTime2 = 1000L;
    _reset = task3.core(1000, _gTime1, _gTime2, 1); // Gemerate a RESET pulse only once for 1second
    // arg1 - duration of the RESET pulse
    // arg2 - guard time before the first RESET pulse (in msec)
    // arg3 - guard time after for each RESET pulse (in msec)
    // arg4 - number of RESET pulses

    // retval = _reset ? 1 : 0;

#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 2)
    Serial.print("# task3.core() returned "); Serial.println(_reset);
#endif  // (DEBUG_LEVEL >= 1)
#endif  // USE_GBKA

  }

  return(_reset);
}

// -------------------------------------

#ifndef USE_TASKX_INSTEADOF_TASK4

// task4_wrapper() returns:
//   0 - notification is NOT activated
//   1 - notification is activated
//  -1 - other condition

int task4_wrapper() {

  int _retval = -1;

  // int _retval = task4core();

  return(_retval);

}

#endif  // USE_TASKX_INSTEADOF_TASK4

// ---------------------------------------------------------
