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
	// _pin = pin;
	if (_pin > 0) {
		pinMode(_pin, INPUT_PULLUP);
		digitalWrite(_pin, LOW);
	}
}

// ---------------------------------------------------------

// void classButtonSW::init(int pin)

void classButtonSW::init(int pin) {
	_pin = pin;
	if (_pin > 0) {
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
    return(false);
  }

  if (_state) {
    _currentVal += _updown;
    if (_currentVal > _LEVEL_MAX) { _currentVal = _LEVEL_MAX; }
  } else {
    _currentVal -= _updown;
    if (_currentVal < _LEVEL_MIN) { _currentVal = _LEVEL_MIN; }
  }

	if ((_state == false) && (_currentVal > _LEVEL_H)) {
		// FALSE -> TRUE
		_state = true;

	} else if ((_state == true) && (_currentVal < _LEVEL_L)) {
    // TRUE -> FALSE
    _state = false;
	}

	return(true);
}

// ---------------------------------------------------------

// void classButtonSW::get()

boolean classButtonSW::get() {
	return(_state);
}

// ---------------------------------------------------------


// ---------------------------------------------------------
