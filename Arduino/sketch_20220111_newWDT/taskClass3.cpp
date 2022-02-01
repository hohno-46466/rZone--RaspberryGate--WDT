//
// taskClass3.cpp
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// task3 - Generate RESET pulse (for both of the gentle and the delayed watchdog)

// ---------------------------------------------------------

#include "Arduino.h"
#include "taskClass3.h"
#include "mydefs.h"

extern uint32_t CurrentTime_8ms;
extern uint32_t eightMillis();

// ---------------------------------------------------------

// taskClass3::taskClass3(int pin)
//   pin - pin No. to reset Raspberry Pi

taskClass3::taskClass3(int pin) {
  _pin = pin;
}

// ---------------------------------------------------------

// taskClass3::init()
// taskClass3::init(int pin)
//   pin - pin No. to reset Raspberry Pi

boolean taskClass3::init() {
  if (_pin <= 0) { return(false); }
  pinMode(_pin, OUTPUT);
  return(true);
}

boolean taskClass3::init(int pin) {
  _pin = pin;
  if (_pin <= 0) { return(false); }
  pinMode(_pin, OUTPUT);
  return(true);
}

// ---------------------------------------------------------

// taskClass3::core() - RESET Raspberry Pi

// taskClass3::core(int32_t arg1, int32_t arg2, int32_t arg3, int arg4)
//   args:
//     arg1 - duration of pulling down the RESET pin (in msec)
//     arg2 - guard time before the first RESET
//     arg2 - guard time after every RESET
//     arg4 - how many times will it generate Reset pulse (usually it's one)
//   return value:
//      1 - RESET is activated (request has been accepted)
//      0 - RESET is not activated
//     -1 - other condition

int taskClass3::core(int32_t arg1, int32_t arg2, int32_t arg3, int arg4) {
  static int _flag = 0; // current status
  static uint32_t next0_8ms = 0;
  static uint32_t next1_8ms = 0;
  static uint32_t next2_8ms = 0;
  static int _cnt = 0;

#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 2)
    Serial.print("# task3core() point1"); Serial.println();
#endif  // (DEBUG_LEVEL >= 1)
#endif  // USE_GBKA

    /*
  if (arg4 < 0) {
    // we can clear the _cnt by specifing -1 to arg4
    _cnt = 0;
    return(true);
  }
    */

  if ((arg1 <= 0) || (arg1 >= 1000*1000L)) {
    // calling this function is rejected if arg1 is 0, negative number, or too big
    return(-1);
  }

    if ((arg2 <= 0) || (arg2 >= 300*1000L)) {
    // guard time1 must be between 1 to 300 (sec)
    return(-1);
  }

    if ((arg3 <= 0) || (arg3 >= 100*1000L)) {
    // guard time2 must be between 1 to 100 (sec)
    return(-1);
  }

#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 2)
    Serial.print("# task3core() point2"); Serial.println();
#endif  // (DEBUG_LEVEL >= 1)
#endif  // USE_GBKA

  if (_flag == 0) {

#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 2)
    Serial.print("# task3core(), _flag is zero"); Serial.println();
#endif  // (DEBUG_LEVEL >= 2)
#endif  // USE_GBKA


    // _flag is zero (RESET is not activated)
    if (_cnt < arg4) {
      // RESET requied but not activated. It will be activated from now.
      _flag = 1; // RESET request has been accepted

      next0_8ms = eightMillis();

#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 2)
    Serial.print("# CurrentTime_8ms = "); Serial.println(CurrentTime_8ms);
    Serial.print("# _eightMillis() = "); Serial.println(next0_8ms);
#endif  // (DEBUG_LEVEL >= 2)
#endif  // USE_GBKA

      if (_cnt == 0) {
        next0_8ms += (arg2 / 8); // End of the first guard time
      }
      next1_8ms = next0_8ms + (arg1 / 8); // End of the current RESET
      next2_8ms = next1_8ms + (arg3 / 8); // End of the guard time


#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 2)
    Serial.print("# next0_8ms = "); Serial.println(next0_8ms);
    Serial.print("# next1_8ms = "); Serial.println(next1_8ms);
    Serial.print("# next2_8ms = "); Serial.println(next2_8ms);
#endif  // (DEBUG_LEVEL >= 2)
#endif  // USE_GBKA

      if (CurrentTime_8ms >= next0_8ms) {
        _cnt++;
        AVR_RESET_ON;

#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 2)
        Serial.print("# AVR_RESET_ON  "); Serial.println(_cnt);
#endif  // (DEBUG_LEVEL >= 2)
#endif  // USE_GBKA

      } else {
        // if _cnt is zero, we can insert guard time which is specified by arg2 by extending next0_8ms and doing nothing here
      }
    }

  } else {
#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 2)
    Serial.print("# task3core(), _flag is 1"); Serial.println();
#endif  // (DEBUG_LEVEL >= 1)
#endif  // USE_GBKA

    // _flag is 1 (RESET is activated)
    if (CurrentTime_8ms >= next1_8ms) {
      // if RESET is continued more than the specified duration, deactivate RESET and the guard time starts
      AVR_RESET_OFF;

    } else  if (CurrentTime_8ms >= next2_8ms) {
      // The guard time has been done.
      _flag = 0; // _flag is 0 (RESET is deactivated)
#ifdef  USE_GBKA
#if     (DEBUG_LEVEL >= 2)
      Serial.print("# AVR_RESET_OFF and guard time done."); Serial.println(_cnt);
#endif  // (DEBUG_LEVEL >= 1)
#endif  // USE_GBKA

    }
  }
  return(_flag);
}

// ---------------------------------------------------------
