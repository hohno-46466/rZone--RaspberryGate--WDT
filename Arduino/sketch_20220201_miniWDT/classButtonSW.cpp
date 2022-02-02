//
// classButtonSW.cpp
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// classButtonSW --

// ---------------------------------------------------------

#include "Arduino.h"
#include "classButtonSW.h"
#include "mydefs.h"

extern uint32_t eightMillis();

// ---------------------------------------------------------

// classButtonSW::classButtonSW()

classButtonSW::classButtonSW() {

  if (IS_PIN_OK(_pin)) {
    pinMode(_pin, INPUT_PULLUP);
  }
}

classButtonSW::classButtonSW(int pin, boolean pullup, boolean positive) {

  if (IS_PIN_OK(pin)) {
    _pin = pin;
    _positive = positive;
    pinMode(_pin, INPUT_PULLUP);
  }
}


// ---------------------------------------------------------

// boolean classButtonSW::init(int pin, boolean pullup, boolean positive)

boolean classButtonSW::init(int pin, boolean pullup, boolean positive) {

  if (!IS_PIN_OK(pin)) {
    return(false);
  }

  _pin = pin;
  _positive = positive;
  pinMode(_pin, pullup ? INPUT_PULLUP : INPUT);

  return(true);
}

// ---------------------------------------------------------

// int classButtonSW::setParam(int updown)

int classButtonSW::setParam(int updown) {
  const int updown_min = (_LEVEL_MAX - _LEVEL_MIN) *  5 / 100;
  const int updown_max = (_LEVEL_MAX - _LEVEL_MIN) * 40 / 100;

  if ((updown >= updown_min) && (updown <= updown_max)) {
    _updown = updown;
  }
  return(updown);
}

// ---------------------------------------------------------

#define GET_PIN (digitalRead(_pin) == (_positive ? HIGH : LOW))

// void classButtonSW::update()

boolean classButtonSW::update() {
  // digital debouncing

  static uint32_t _lastTime_8ms = 0;
  uint32_t _currentTime_8ms = eightMillis();

  if ((_currentTime_8ms - _lastTime_8ms) <= 1) {
    return(_state);
  }

  boolean _pulseState = GET_PIN;

  if (_pulseState) {
    _currentVal += _updown;
    if (_currentVal > _LEVEL_MAX) { _currentVal = _LEVEL_MAX; }

  } else {
    _currentVal -= _updown;
    if (_currentVal < _LEVEL_MIN) { _currentVal = _LEVEL_MIN; }
  }

  if (((_state == SW_OFF) || (_state == SW_UNKNOWN)) && (_currentVal > _LEVEL_H)) {
    // SW OFF -> SW ON
    _state = SW_ON;

  } else if ((_state == SW_ON) && (_currentVal < _LEVEL_L)) {
    // SW ON -> SW OFF
    _state = SW_OFF;
  }

  return(_state);
}

// ---------------------------------------------------------

// int classButtonSW::getStat()

int classButtonSW::getStat() {
  return(_state);
}

// ---------------------------------------------------------


// ---------------------------------------------------------
