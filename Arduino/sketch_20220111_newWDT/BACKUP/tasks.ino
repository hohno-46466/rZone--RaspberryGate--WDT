//
// tasks.ino
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// extern uint32_t eightMillis();
// extern const int PulseCounterSize;

// ---------------------------------------------------------

#if 0

// // task0core -- returns avaraged number of pulses per second
//
// // float task0core()
//
// float task0core() {
//   const int _LEVEL_MIN = 0;
//   const int _LEVEL_MAX = 100;
//   const int _LEVEL_H   = 80;
//   const int _LEVEL_L   = 20;
//
//   int _sum = 0, _cnt = 0;
//   static float _retval = 0.0;
//   static uint32_t _lastPulse = 0;
//   uint32_t _currentT_8ms = eightMillis();
//   static struct pulseCounter{
//     uint32_t eightMillis;
//     int cnt;
//   } _pulseCounter[PulseCounterSize];
//   // const int PulseCounterSize = PulseCounterSize; // ((sizeof _secCnt) / (sizeof _pulseCounter[0]));
//   static boolean _currentStat = false;
//   static int _currentVal = 0;
//
//   if ((_currentT_8ms - _lastPulse) <= 1) {
//     return(_retval);
//   }
//
//   boolean _pulseState = AVR_GET_PULSE;
//
//   _lastPulse = _currentT_8ms;
//
//   // digital debouncing
//   if (_pulseState) {
//     _currentVal += 15;
//     if (_currentVal > _LEVEL_MAX) { _currentVal = _LEVEL_MAX; }
//   } else {
//     _currentVal -= 15;
//     if (_currentVal < _LEVEL_MIN) { _currentVal = _LEVEL_MIN; }
//   }
//
// #ifdef _USE_UNO_
// #if (_DEBUG_LEVEL >= 5)
//   Serial.print(_currentVal); Serial.print(" ");
// #endif // (_DEBUG_LEVEL >= 4)
// #endif // _USE_UNO_
//
//   boolean _flagX = false; // _flagX is TRUE when a new pulse is detected
//
//   if ((_currentStat == false) && (_currentVal > _LEVEL_H)) {
//     // _currentState: FALSE -> TRUE
//     _currentStat = true;
//     _flagX = true;
//
// #ifdef _USE_UNO_
// #if (_DEBUG_LEVEL >= 5)
//     Serial.println("L->H"); // Serial.print("H "); //
// #endif // (_DEBUG_LEVEL >= 4)
// #endif // _USE_UNO_
//
//   } else if ((_currentStat == true) && (_currentVal < _LEVEL_L)) {
//     // _currentState:  TRUE -> FALSE
//     _currentStat = false;
//     _flagX = false;
//
// #ifdef _USE_UNO_
// #if (_DEBUG_LEVEL >= 5)
//     Serial.println("H->L"); // Serial.print("L "); //
// #endif // (_DEBUG_LEVEL >= 4)
// #endif // _USE_UNO_
//   }
//
//   if (_flagX) {
//     int _index = (_currentT_8ms / 125UL) % PulseCounterSize;
//
//     // XXX // _flagX = false; // Do you need this?
//
// #ifdef _USE_UNO_
// #if (_DEBUG_LEVEL >= 3)
//     Serial.print("_index = "); Serial.print(_index); Serial.print(", ");
//     Serial.print(_pulseCounter[_index].eightMillis / 125UL); Serial.print(", ");
//     Serial.print(_pulseCounter[_index].cnt); Serial.println();
//     // Serial.print(_currentT_8ms / 125UL); Serial.println();
// #endif // (_DEBUG_LEVEL >= 3)
// #endif // _USE_UNO_
//
//     if ((_pulseCounter[_index].eightMillis / 125UL) == (_currentT_8ms / 125UL)) {
//       // if _pulseCounter[_index] is valid, just increment the _pulseCounter[_index].cnt
//       _pulseCounter[_index].cnt ++;
//
//     } else {
//       // if _pulseCounter[_index] is obsolete (timedout), replace with the new data
//       _pulseCounter[_index].eightMillis = _currentT_8ms;
//       _pulseCounter[_index].cnt = 1;
//     }
//   }
//
//   // if the pulse comes every 1sec, all of _pulseCounter[*].cnt will be 1.
//   // if the pulse comes more than two time in a second, some of _pulseCounter[*].cnt will be two or larger
//
//   for (int i = 0; i < PulseCounterSize; i++) {
//     uint32_t _tt = _pulseCounter[i].eightMillis;
//     if ((int)((_currentT_8ms  - _tt) / 125UL) > PulseCounterSize) {
//       // if _pulseCounter[*] is obsolete (timedout), it will be zero'd
//       _pulseCounter[i].eightMillis = 0;
//       _pulseCounter[i].cnt = 0;
//     }
//   }
//
//   _sum = 0;
//   _cnt = 0;
//   for (int i = 0; i < PulseCounterSize; i++) {
//     int _xx = _pulseCounter[i].cnt;
//     if (_pulseCounter[i].eightMillis > 0) {
//       _sum += _xx;
//       _cnt ++;
//     }
//
//     // now _sum is the total number of pulses in the last PulseCounterSize sec.
//
// #ifdef _USE_UNO_
// #if (_DEBUG_LEVEL >= 4)
//     if (_pulseCounter[i].eightMillis > 0) {
//       Serial.print(_xx);
//       Serial.print(". ");
//     } else {
//       Serial.print("-, ");
//     }
// #endif // (_DEBUG_LEVEL >= 4)
// #endif // _USE_UNO_
//
//   }
//
// #ifdef _USE_UNO_
// #if (_DEBUG_LEVEL >= 4)
//   Serial.print("-> ");
//   Serial.print(_sum);
//   Serial.print("/");
//   Serial.print(_cnt);
//   Serial.print(" ( ");
//   Serial.print((_cnt == 0) ? 0 : (float)_sum/_cnt);
//   Serial.println(")");
// #endif // (_DEBUG_LEVEL >= 4)
// #endif // _USE_UNO_
//
//   // _retval = (_cnt == 0) ? 0 : (float)_sum/_cnt;
//   _retval =_sum;
//
//   return(_retval);
// }

#endif // 0

// ---------------------------------------------------------

#if 0

// // task2core -- returns mode status (gentle mode or delayed mode)
//
// int task2core() {
//   return(-1);
// }

#endif // 0


// ---------------------------------------------------------

#if 0

// // task3core - RESET Raspberry Pi
//
// // task3core(int32_t arg1, int32_t arg2, int32_t arg3, int arg4)
// //   args:
// //     arg1 - duration of pulling down the RESET pin (in msec)
// //     arg2 - guard time before the first RESET
// //     arg2 - guard time after every RESET
// //     arg4 - how many times will it generate Reset pulse (usually it's one)
// //   return value:
// //      1 - RESET is activated (request has been accepted)
// //      0 - RESET is not activated
// //     -1 - other condition
//
// int task3core(int32_t arg1, int32_t arg2, int32_t arg3, int arg4) {
//   static int _flag = 0; // current status
//   static uint32_t next0_8ms = 0;
//   static uint32_t next1_8ms = 0;
//   static uint32_t next2_8ms = 0;
//   static int _cnt = 0;
//
// #ifdef _USE_UNO_
// #if (_DEBUG_LEVEL >= 2)
//     Serial.print("# task3core() point1"); Serial.println();
// #endif // (_DEBUG_LEVEL >= 1)
// #endif // _USE_UNO_
//
//     /*
//   if (arg4 < 0) {
//     // we can clear the _cnt by specifing -1 to arg4
//     _cnt = 0;
//     return(true);
//   }
//     */
//
//   if ((arg1 <= 0) || (arg1 >= 1000*1000L)) {
//     // calling this function is rejected if arg1 is 0, negative number, or too big
//     return(-1);
//   }
//
//     if ((arg2 <= 0) || (arg2 >= 300*1000L)) {
//     // guard time1 must be between 1 to 300 (sec)
//     return(-1);
//   }
//
//     if ((arg3 <= 0) || (arg3 >= 100*1000L)) {
//     // guard time2 must be between 1 to 100 (sec)
//     return(-1);
//   }
//
// #ifdef _USE_UNO_
// #if (_DEBUG_LEVEL >= 2)
//     Serial.print("# task3core() point2"); Serial.println();
// #endif // (_DEBUG_LEVEL >= 1)
// #endif // _USE_UNO_
//
//   if (_flag == 0) {
//
// #ifdef _USE_UNO_
// #if (_DEBUG_LEVEL >= 2)
//     Serial.print("# task3core(), _flag is zero"); Serial.println();
// #endif // (_DEBUG_LEVEL >= 1)
// #endif // _USE_UNO_
//
//
//     // _flag is zero (RESET is not activated)
//     if (_cnt < arg4) {
//       // RESET requied but not activated. It will be activated from now.
//       _flag = 1; // RESET request has been accepted
//
//       next0_8ms = eightMillis();
//
// #ifdef _USE_UNO_
// #if (_DEBUG_LEVEL >= 2)
//     Serial.print("# CurrentTime_8ms = "); Serial.println(CurrentTime_8ms);
//     Serial.print("# _eightMillis() = "); Serial.println(next0_8ms);
// #endif // (_DEBUG_LEVEL >= 1)
// #endif // _USE_UNO_
//
//       if (_cnt == 0) {
//         next0_8ms += (arg2 / 8); // End of the first guard time
//       }
//       next1_8ms = next0_8ms + (arg1 / 8); // End of the current RESET
//       next2_8ms = next1_8ms + (arg3 / 8); // End of the guard time
//
//
// #ifdef _USE_UNO_
// #if (_DEBUG_LEVEL >= 2)
//     Serial.print("# next0_8ms = "); Serial.println(next0_8ms);
//     Serial.print("# next1_8ms = "); Serial.println(next1_8ms);
//     Serial.print("# next2_8ms = "); Serial.println(next2_8ms);
// #endif // (_DEBUG_LEVEL >= 1)
// #endif // _USE_UNO_
//
//       if (CurrentTime_8ms >= next0_8ms) {
//         _cnt++;
//         AVR_RESET_ON;
//
// #ifdef _USE_UNO_
// #if (_DEBUG_LEVEL >= 2)
//         Serial.print("# AVR_RESET_ON  "); Serial.println(_cnt);
// #endif // (_DEBUG_LEVEL >= 1)
// #endif // _USE_UNO_
//
//       } else {
//         // if _cnt is zero, we can insert guard time which is specified by arg2 by extending next0_8ms and doing nothing here
//       }
//     }
//
//   } else {
// #ifdef _USE_UNO_
// #if (_DEBUG_LEVEL >= 2)
//     Serial.print("# task3core(), _flag is 1"); Serial.println();
// #endif // (_DEBUG_LEVEL >= 1)
// #endif // _USE_UNO_
//
//     // _flag is 1 (RESET is activated)
//     if (CurrentTime_8ms >= next1_8ms) {
//       // if RESET is continued more than the specified duration, deactivate RESET and the guard time starts
//       AVR_RESET_OFF;
//
//     } else  if (CurrentTime_8ms >= next2_8ms) {
//       // The guard time has been done.
//       _flag = 0; // _flag is 0 (RESET is deactivated)
// #ifdef _USE_UNO_
// #if (_DEBUG_LEVEL >= 2)
//       Serial.print("# AVR_RESET_OFF and guard time done."); Serial.println(_cnt);
// #endif // (_DEBUG_LEVEL >= 1)
// #endif // _USE_UNO_
//
//     }
//   }
//   return(_flag);
// }

#endif // 0

// ---------------------------------------------------------
// ---------------------------------------------------------
