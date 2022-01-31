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
    digitalWrite(_pin, LOW);
  }
}

// ---------------------------------------------------------

// void classButtonSW::init(int pin)

void classButtonSW::init(int pin) {
  _pin = pin;
	if (IS_PIN_OK(_pin)) {
    pinMode(_pin, INPUT_PULLUP);
    digitalWrite(_pin, LOW);
  }
}

// ---------------------------------------------------------

// int classButtonSW::set(int updown)

int classButtonSW::set(int updown) {
  const int updown_min = (_LEVEL_MAX - _LEVEL_MIN) *  5 / 100;
  const int updown_max = (_LEVEL_MAX - _LEVEL_MIN) * 40 / 100;

  if ((updown >= updown_min) && (updown <= updown_max)) {
    _updown = updown;
  }
  return(updown);
}

// ---------------------------------------------------------

// void classButtonSW::update()

boolean classButtonSW::update() {
  // digital debouncing

  static uint32_t _lastTime_8ms = 0;
  uint32_t _currentTime_8ms = eightMillis();

  if ((_currentTime_8ms - _lastTime_8ms) <= 1) {
    return(_state);
  }

	boolean _pulseState = AVR_GET_PULSE;

  if (_pulseState) {
    _currentVal += _updown;
    if (_currentVal > _LEVEL_MAX) { _currentVal = _LEVEL_MAX; }
  } else if (_state == SW_ON) {
    _currentVal -= _updown;
    if (_currentVal < _LEVEL_MIN) { _currentVal = _LEVEL_MIN; }
  }

  if (((_state == SW_OFF) || (_state == SW_UNKNOWN)) && (_currentVal > _LEVEL_H)) {
    // SW OFF -> SW ON
    _state = SW_ON;

  } else if ((_state == SW_ON) && (_currentVal < _LEVEL_L)) {
    // SW ON -> SW OFF
    _state = SW<_OFF;
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
