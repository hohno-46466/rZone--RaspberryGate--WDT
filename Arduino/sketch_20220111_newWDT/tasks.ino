//
// tasks.ino
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// -------------------------------------

// task0tmp -- returns number of pulses in last 30 seconds

// int task0tmp()

int task0tmp() {
  const int _LEVEL_MIN = 0;
  const int _LEVEL_MAX = 100;
  const int _LEVEL_H   = 80;
  const int _LEVEL_L   = 20;

  static int _sum = 0;
  static uint32_t _lastGetPulse = 0;
  uint32_t _currentMillis = millis();
  static struct secCnt {
    uint32_t millis;
    int cnt;
  } _secCnt[30]; // 30 is for 30 seconds
  const int _secCntSize = ((sizeof _secCnt) / (sizeof _secCnt[0]));
  static boolean _currentStat = false;
  static int _currentVal = 0;

  if ((_currentMillis - _lastGetPulse) < 2) {
    return(_sum);
  }

  boolean _pulseState = ATT_GET_PULSE;
  _lastGetPulse = _currentMillis;

  if (_pulseState) {
    _currentVal += 10;
    if (_currentVal > _LEVEL_MAX) { _currentVal = _LEVEL_MAX; }
  } else {
    _currentVal -= 10;
    if (_currentVal < _LEVEL_MIN) { _currentVal = _LEVEL_MIN; }
  }

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 4)
  Serial.print(_currentVal); Serial.print(" ");
#endif // (_DEBUG_LEVEL >= 4)
#endif // _USE_UNO_

  boolean _flagX = false;

  if ((_currentStat == false) && (_currentVal > _LEVEL_H)) {
    _currentStat = true;
    _flagX = true;

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 4)
    Serial.println("L->H"); // Serial.print("H "); //
#endif // (_DEBUG_LEVEL >= 4)
#endif // _USE_UNO_

  } else if ((_currentStat == true) && (_currentVal < _LEVEL_L)) {
    _currentStat = false;

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 4)
    Serial.println("H->L"); // Serial.print("L "); //
#endif // (_DEBUG_LEVEL >= 4)
#endif // _USE_UNO_

    _flagX = false;
  }

  // if (!_flagX) {
  //    return(_sum); // return(-2);
  // }

  if (_flagX) {
    int _index = (_currentMillis / 1000UL)  % _secCntSize;

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 3)
    Serial.print("_index = "); Serial.print(_index); Serial.print(", ");
    Serial.print(_secCnt[_index].millis / 1000UL); Serial.print(", ");
    Serial.print(_currentMillis / 1000UL); Serial.println();
#endif // (_DEBUG_LEVEL >= 3)
#endif // _USE_UNO_

    if ((_secCnt[_index].millis / 1000UL) == (_currentMillis / 1000UL)) {
      _secCnt[_index].cnt ++;
    } else {
      _secCnt[_index].millis = _currentMillis;
      _secCnt[_index].cnt = 1;
    }
  }

  for (int i = 0; i < _secCntSize; i++) {
    uint32_t _tt = _secCnt[i].millis;
    if ((int)((_currentMillis  - _tt) / 1000UL) > _secCntSize) {
      _secCnt[i].millis = 0;
      _secCnt[i].cnt = 0;
    }
  }

  _sum = 0;
  for (int i = 0; i < _secCntSize; i++) {
    int _xx = _secCnt[i].cnt;
    if (_secCnt[i].millis > 0) {
      _sum += _xx;
    }

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 3)
    Serial.print(_xx);
    Serial.print(", ");
#endif // (_DEBUG_LEVEL >= 3)
#endif // _USE_UNO_

  }

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 3)
  Serial.print("-> ");
  Serial.print(_sum);
  Serial.println();
#endif // (_DEBUG_LEVEL >= 3)
#endif // _USE_UNO_

  return(_sum);
}


// ---------------------------------------------------------

// task3tmp - RESET Raspberry Pi

// task3tmp(int32_t arg1, int arg2)
//    arg1 - duration of pulling down the Reset pin (in msec)
//    arg2 - how many times will it generate Reset pulse (usually it's one)

boolean task3tmp(int32_t arg1, int arg2) {
  // mystatic int32_t _prev_arg1 = -1;
  static boolean _flag = false;
  static uint32_t _ten_millis_next = 0;
  static int _cnt = 0;

  if (arg2 < 0) {
    _cnt = 0;
    return(true);
  }

  if ((arg1 <= 0) || (arg1 >= 1000*1000L)) {
    return(false);
  }

  if (!_flag) {
    if (_cnt < arg2) {
      _flag = true;
      _cnt++;
      // ten_millis_next = (millis() + arg1) / 10;
      _ten_millis_next = tenMillis() + (arg1 / 10);
      ATT_RESET_ON;
    }

  } else {
    // flag is true;
    if (_ten_millis_next <= GLOBAL_ten_millis_curr) {
      ATT_RESET_OFF;
      _flag = false;
    }
  }
  return(_flag);
}

// ---------------------------------------------------------
