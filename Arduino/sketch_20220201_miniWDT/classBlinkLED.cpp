//
// classBlinkLED.cpp for miniWDT
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc
// Revised: Thu Feb  3 12:59:16 JST 2022 for miniWDT

// ---------------------------------------------------------

// classBlinkLED -- Blink LED to show the current status

// ---------------------------------------------------------

#include "Arduino.h"
#include "classBlinkLED.h"
#include "mydefs.h"

// ---------------------------------------------------------
// ---------------------------------------------------------

// classBlinkLED::classBlinkLED()
// classBlinkLED::classBlinkLED(int pin, boolean positive)

classBlinkLED::classBlinkLED() {

  if (IS_PIN_OK(_pin)) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, _positive ? LOW : HIGH); // turn LED off
  }
}

classBlinkLED::classBlinkLED(int pin, boolean positive) {

  if (IS_PIN_OK(pin)) {
    _pin = pin;
    _positive = positive;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, _positive ? LOW : HIGH); // turn LED off
  }
}

// ---------------------------------------------------------
// ---------------------------------------------------------

// boolean classBlinkLED::init(int pin, boolean positive)

boolean classBlinkLED::init(int pin, boolean positive) {

  if (!IS_PIN_OK(pin)) {
    return(false);
  }

  _pin = pin;
  _positive = positive;
    pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _positive ? LOW : HIGH); // turn LED off

  return(true);
}

// ---------------------------------------------------------

// void classBlinkLED::setParam(int Ton, int Toff)
//   Ton - duration of LED ON (in msec);
//   Toff - duration of LED OFF (in msec)
// void classBlinkLED::setParam(int T0, int T1, int T2, int N);
//   T0 - duration of LED OFF before T1 (in msec)
//   T1 - duration of LED ON (in msec);
//   T2 - duration of LED OFF after T1 (in msec)
//   N  - number of repeating
//   (if N = 3, then ((T0,T1),(T0,T1),(T0,T1),T2 [End])
// void classBlinkLED::setParam(int T0, int T1, int T2, int N1, int N2);
//   T0 - duration of LED OFF before T1 (in msec)
//   T1 - duration of LED ON (in msec);
//   T2 - duration of LED OFF after T1 (in msec)
//   N1 - number of repeating of (T0+T1)
//   N2 - number of repeating of ((T0+T1) x N1 + T2)
//   (if N1 = 3 and N2 = 2, then (((((T0,T1),(T0,T1),(T0,T1)),T2), ((T0,T1),(T0,T1),(T0,T1)),T2), [End])

void classBlinkLED::setParam(int Ton, int Toff) {
	_T0_ms = Ton;
  _T1_ms = Toff;
  _T2_ms = 0;
	_N1 = -1;
	_N2 = 0;
	_blink = true;
	_N1now = 0;
	_N2now = 0;
	_LEDstat = false;
	_Tnext_ms = millis();
}

void classBlinkLED::setParam(int T0, int T1, int T2, int N) {
	// N x (T0 + T1) + T2 [End]
	_T0_ms = T0;
  _T1_ms = T1;
  _T2_ms = T2;
	_N1 = N;
	_N2 = 0;
	_blink = true;
	_N1now = 0;
	_N2now = 0;
	_LEDstat = false;
	_Tnext_ms = millis();
}

void classBlinkLED::setParam(int T0, int T1, int T2, int N1, int N2) {
		// N2 x (N1 x (T0 + T1) + T2) [End]
	_T0_ms = T0;
  _T1_ms = T1;
  _T2_ms = T2;
	_N1 = N1;
	_N2 = N2;
	_blink = true;
	_N1now = 0;
	_N2now = 0;
	_LEDstat = false;
	_Tnext_ms = millis();
}

// ---------------------------------------------------------

// boolean classBlinkLED::blink()
// returns
//   tru  - LED is ON
//   false - LED is OFF

#define _LED_ON    (digitalWrite(_pin, Logic_LED ? HIGH : LOW))
#define _LED_OFF   (digitalWrite(_pin, Logic_LED ? LOW : HIGH))

boolean classBlinkLED::blink() {

	if (!_blink) {
		return(false);
	}

  if (!IS_PIN_OK(_pin)) {
    return(false);
  }

	if ((_T0_ms < 0) || (_T1_ms< 0) || (_T2_ms< 0)) {
		return(false);
	}

	if (_Tnext_ms > millis()) {
		//
	} else {
		// prepare for the next period
		_Tnext_ms += _updateTnext_ms();
		_LEDstat ? _LED_ON : _LED_OFF;
	}
	_blink = true;

	/*
  if ((_Ton == _prev_Ton) && (_Toff == _prev_Toff)) {
    // Both Ton and Toff are not updated
    if (_Tnext_ms <= millis()) {
      if (_LEDstat) {
        _LEDstat = false;
        _Tnext_ms += _Toff;
        _LED_OFF;
      } else {
        _LEDstat = true;
        _Tnext_ms += _Ton;
        _LED_ON;
      }
    }
  } else {
    // at least one of _Ton and _Toff was updated
    _prev_Ton = _Ton;
    _prev_Toff = _Toff;
    _Tnext_ms = millis() + _Ton;
    _LEDstat = true;
    _LED_ON;
  }
	*/

  return(_LEDstat);
}

// ---------------------------------------------------------

// void classBlinkLED::stop()

void classBlinkLED::stop() {
	_blink = false;
}

// ---------------------------------------------------------

// void classBlinkLED::start()

void classBlinkLED::start() {
	_blink = true;
}

// ---------------------------------------------------------
// ---------------------------------------------------------

/*private*/ uint32_t classBlinkLED::_updateTnext_ms() {

	uint32_t _retT_ms = 0;
	static boolean _flagT2 = false;

	// (((T0,T1),(T0,T1), ..),T2,)...

	if (_flagT2) {
		_flagT2 = false;
		_LEDstat = false;
		_retT_ms = _T2_ms;
		if (_N2 <= 0) {
			// loop forever
			_N1now = 0;
		}
		_N2now++;
		if (_N2now >= _N2) {
			_N2now = 0;
			_N1now = 0;
			}
		return(_retT_ms);
	}

	if (_LEDstat == false) {
		_LEDstat = true;
		_retT_ms = _T0_ms;
		return(_retT_ms);
	}

	if (_LEDstat == true) {
		_LEDstat = false;
		_retT_ms = _T1_ms;
		if (_N1 <= 0) {
			return(_retT_ms);
		}
		_N1now++;
		if (_N1now >= _N1) {
			_N1now = 0;
			_flagT2 = true;
		}
		return(_retT_ms);
	}

	return(0); /* NotReached */
}

// ---------------------------------------------------------
