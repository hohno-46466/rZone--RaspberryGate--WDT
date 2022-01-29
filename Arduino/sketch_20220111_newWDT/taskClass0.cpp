//
// taskClass0.cpp
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// task0 - Check the "heart beat" pulse from Raspberry Pi

// ---------------------------------------------------------

#include "Arduino.h"
#include "taskClass0.h"
#include "mydefs.h"

extern uint32_t CurrentTime_8ms;
extern uint32_t eightMillis();

// ---------------------------------------------------------

// taskClass0::taskClass0(int pin)
//   pin - pin No. to receive WDT pulse

taskClass0::taskClass0(int pin) {
	_pin = pin;
}

// ---------------------------------------------------------

// taskClass0::init()
// taskClass0::init(int pin)
//   pin - pin No. to receive WDT pulse

boolean taskClass0::init() {
	if (_pin <= 0) { return(false); }
	pinMode(_pin, INPUT_PULLUP);
	return(true);
}

boolean taskClass0::init(int pin) {
	_pin = pin;
	if (_pin <= 0) { return(false); }
	pinMode(_pin, INPUT_PULLUP);
	return(true);
}

// ---------------------------------------------------------

// taskClass0::core -- returns avaraged number of pulses per second

// float taskClass0::core()

float taskClass0::core() {
  const int _LEVEL_MIN = 0;
  const int _LEVEL_MAX = 100;
  const int _LEVEL_H   = 80;
  const int _LEVEL_L   = 20;

  int _sum = 0, _cnt = 0;
  static float _retval = 0.0;
  static uint32_t _lastPulse = 0;
  uint32_t _currentT_8ms = eightMillis();
  static struct pulseCounter{
    uint32_t eightMillis;
    int cnt;
  } _pulseCounter[PulseCounterSize];
  // const int PulseCounterSize = PulseCounterSize; // ((sizeof _secCnt) / (sizeof _pulseCounter[0]));
  static boolean _currentStat = false;
  static int _currentVal = 0;

  if ((_currentT_8ms - _lastPulse) <= 1) {
    return(_retval);
  }

  boolean _pulseState = AVR_GET_PULSE;

  _lastPulse = _currentT_8ms;

  // digital debouncing
  if (_pulseState) {
    _currentVal += 15;
    if (_currentVal > _LEVEL_MAX) { _currentVal = _LEVEL_MAX; }
  } else {
    _currentVal -= 15;
    if (_currentVal < _LEVEL_MIN) { _currentVal = _LEVEL_MIN; }
  }

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 5)
  Serial.print(_currentVal); Serial.print(" ");
#endif // (_DEBUG_LEVEL >= 4)
#endif // _USE_UNO_

  boolean _flagX = false; // _flagX is TRUE when a new pulse is detected

  if ((_currentStat == false) && (_currentVal > _LEVEL_H)) {
    // _currentState: FALSE -> TRUE
    _currentStat = true;
    _flagX = true;

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 5)
    Serial.println("L->H"); // Serial.print("H "); //
#endif // (_DEBUG_LEVEL >= 4)
#endif // _USE_UNO_

  } else if ((_currentStat == true) && (_currentVal < _LEVEL_L)) {
    // _currentState:  TRUE -> FALSE
    _currentStat = false;
    _flagX = false;

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 5)
    Serial.println("H->L"); // Serial.print("L "); //
#endif // (_DEBUG_LEVEL >= 4)
#endif // _USE_UNO_
  }

  if (_flagX) {
    int _index = (_currentT_8ms / 125UL) % PulseCounterSize;

    // XXX // _flagX = false; // Do you need this?

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 3)
    Serial.print("_index = "); Serial.print(_index); Serial.print(", ");
    Serial.print(_pulseCounter[_index].eightMillis / 125UL); Serial.print(", ");
    Serial.print(_pulseCounter[_index].cnt); Serial.println();
    // Serial.print(_currentT_8ms / 125UL); Serial.println();
#endif // (_DEBUG_LEVEL >= 3)
#endif // _USE_UNO_

    if ((_pulseCounter[_index].eightMillis / 125UL) == (_currentT_8ms / 125UL)) {
      // if _pulseCounter[_index] is valid, just increment the _pulseCounter[_index].cnt
      _pulseCounter[_index].cnt ++;

    } else {
      // if _pulseCounter[_index] is obsolete (timedout), replace with the new data
      _pulseCounter[_index].eightMillis = _currentT_8ms;
      _pulseCounter[_index].cnt = 1;
    }
  }

  // if the pulse comes every 1sec, all of _pulseCounter[*].cnt will be 1.
  // if the pulse comes more than two time in a second, some of _pulseCounter[*].cnt will be two or larger

  for (int i = 0; i < PulseCounterSize; i++) {
    uint32_t _tt = _pulseCounter[i].eightMillis;
    if ((int)((_currentT_8ms  - _tt) / 125UL) > PulseCounterSize) {
      // if _pulseCounter[*] is obsolete (timedout), it will be zero'd
      _pulseCounter[i].eightMillis = 0;
      _pulseCounter[i].cnt = 0;
    }
  }

  _sum = 0;
  _cnt = 0;
  for (int i = 0; i < PulseCounterSize; i++) {
    int _xx = _pulseCounter[i].cnt;
    if (_pulseCounter[i].eightMillis > 0) {
      _sum += _xx;
      _cnt ++;
    }

    // now _sum is the total number of pulses in the last PulseCounterSize sec.

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 4)
    if (_pulseCounter[i].eightMillis > 0) {
      Serial.print(_xx);
      Serial.print(". ");
    } else {
      Serial.print("-, ");
    }
#endif // (_DEBUG_LEVEL >= 4)
#endif // _USE_UNO_

  }

#ifdef _USE_UNO_
#if (_DEBUG_LEVEL >= 4)
  Serial.print("-> ");
  Serial.print(_sum);
  Serial.print("/");
  Serial.print(_cnt);
  Serial.print(" ( ");
  Serial.print((_cnt == 0) ? 0 : (float)_sum/_cnt);
  Serial.println(")");
#endif // (_DEBUG_LEVEL >= 4)
#endif // _USE_UNO_

  // _retval = (_cnt == 0) ? 0 : (float)_sum/_cnt;
  _retval =_sum;

  return(_retval);
}

// ---------------------------------------------------------
