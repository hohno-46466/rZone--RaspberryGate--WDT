//
// classBlink.cpp for miniWDT
//

# !!! This sketch is under developing. Do not build this. !!!


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
// classBlinkLED::classBlinkLED(int pin, boolean positiveLogic)

classBlinkLED::classBlinkLED() {

  if (IS_PIN_OK(_pin)) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, _positiveLogic ? LOW : HIGH); // turn LED off
  }
}

classBlinkLED::classBlinkLED(int pin, boolean positiveLogic) {

  if (IS_PIN_OK(pin)) {
    _pin = pin;
    _positiveLogic = positiveLogic;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, _positiveLogic ? LOW : HIGH); // turn LED off
  }
}

// ---------------------------------------------------------
// ---------------------------------------------------------

// boolean classBlinkLED::init(int pin, boolean positiveLogic)

boolean classBlinkLED::init(int pin, boolean positiveLogic) {

  if (!IS_PIN_OK(pin)) {
    return(false);
  }

  _pin = pin;
  _positiveLogic = positiveLogic;
    pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _positiveLogic ? LOW : HIGH); // turn LED off

  return(true);
}

// ---------------------------------------------------------

// void classBlinkLED::setParam(int Ton, int Toff, boolean reverseAction)
//   Ton - duration of LED ON (in msec);
//   Toff - duration of LED OFF (in msec)
//   reverseAction - set it true if you take reverse action (only useful for LED blink)

// void classBlinkLED::setParam(int T0, int T1, int T2, int N, boolean reverseAction)
//   T0 - duration of LED OFF before T1 (in msec)
//   T1 - duration of LED ON (in msec);
//   T2 - duration of LED OFF after T1 (in msec)
//   N  - number of additional repeat (0 is no repeat, 1 is repeat once (2 in total), -1 is repeat forever)
//   (if N = 3, then ((T0,T1),(T0,T1),(T0,T1),T2 [End])
//   reverseAction - set it true if you take reverse action (only useful for LED blink)

// void classBlinkLED::setParam(int T0, int T1, int T2, int N1, int N2), boolean reverseAction)
//   T0 - duration of LED OFF before T1 (in msec)
//   T1 - duration of LED ON (in msec);
//   T2 - duration of LED OFF after T1 (in msec)
//   N1 - number of additional repeat of (T0+T1)
//   N2 - number of additional repeat of ((T0+T1) x N1 + T2)
//   (if N1 = 3 and N2 = 2, then (((((T0,T1),(T0,T1),(T0,T1)),T2), ((T0,T1),(T0,T1),(T0,T1)),T2), [End])

void classBlinkLED::setParam(int T0_s, int T1_s, boolean reverseAction) {
  _flag_blink = true;
	_blinkCounter = 0;
	_blinkCounterPrev = -1;
	_LEDstat = false;
  _T0_ms = T0_s * 1000L; /* Ton  */
  _T1_ms = T1_s * 1000L; /* Toff */
  _T2_ms = 0;
  _N1 = (uint16_t)-1; // repeat (almost) forever
  _N2 = 0;
  _flag_reverseAction = reverseAction;
  _N1now = 0;
  _N2now = 0;
  _Tnext_ms = millis();
}

void classBlinkLED::setParam(int T0_s, int T1_s, int T2_s, int N, boolean reverseAction) {
  // N x (T0 + T1) + T2 [End]
  _flag_blink = true;
	_blinkCounter = 0;
	_blinkCounterPrev = -1;
	_LEDstat = false;
  _T0_ms = T0_s * 1000L;
  _T1_ms = T1_s * 1000L;
  _T2_ms = T2_s * 1000L;
  _N1 = (uint16_t)N;
  _N2 = 0;
  _flag_reverseAction = reverseAction;
  _N1now = 0;
  _N2now = 0;
  _Tnext_ms = millis();
}

void classBlinkLED::setParam(int T0_s, int T1_s, int T2_s, int N1, int N2, boolean reverseAction) {
    // N2 x (N1 x (T0 + T1) + T2) [End]
  _flag_blink = true;
	_blinkCounter = 0;
	_blinkCounterPrev = -1;
	_LEDstat = false;
  _T0_ms = T0_s * 1000L;
  _T1_ms = T1_s * 1000L;
  _T2_ms = T2_s * 1000L;
  _N1 = (uint16_t)N1;
  _N2 = (uint16_t)N2;
  _flag_reverseAction = reverseAction;
  _N1now = 0;
  _N2now = 0;
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

  if (!_flag_blink) {
    return(false);
  }

  if (!IS_PIN_OK(_pin)) {
    return(false);
  }

  if ((_T0_ms < 0) || (_T1_ms < 0) || (_T2_ms < 0)) {
    return(false);
  }

  if (_Tnext_ms > millis()) {

		// nothing to do here...
		// we are still waiting for _Tnext_ms to come

  } else {
    // we need to prepare for the next period

    int32_t _tmp_ms = _updateTnext_ms(); // get next period
    if (_tmp_ms < 0) {
      return(false);
    }

    _Tnext_ms += _tmp_ms;
    if (_LEDstat) {
			_LED_ON;
			// blinkCounter++ // we have done this is _updateTnext_ms()
				} else {
			_LED_OFF;
		}
  }
  _flag_blink = true;

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
  _flag_blink = false;
}

// ---------------------------------------------------------

// void classBlinkLED::start()

void classBlinkLED::start() {
  _flag_blink = true;
}

// ---------------------------------------------------------
// ---------------------------------------------------------

/*private*/ int32_t classBlinkLED::_updateTnext_ms() {

  int32_t _retT_ms = 0;

  // (((T0,T1),(T0,T1), ..),T2,)...

    if (_flag_stop) {
    _flag_stop = false;
    return(-1);
  }

  if (_flag_useT2) {
    _LEDstat = false;
		_blinkCounter = 0;
		_T2start_ms = millis();
    _retT_ms = _T2_ms;
    _N2now++;
    if (_N2now > _N2) {
    _flag_stop = true;
    }
    _flag_useT2 = false;
    return(_retT_ms);
  }

	// XXX ??? T0 (off) -> T1 (on) -> T2 (off) になっていない

  if (_LEDstat == false) {
    // if _LEDstat is false, then turn _LEDstat true and return the assigned value of T0_ms
    _LEDstat = true;
		_T0start_ms = millis();
		_blinkCounter = _blinkCounterPrev + 1;
		_blinkCounterPrev = _blinkCounter;
    _retT_ms = _T0_ms;
    return(_retT_ms);
  }

  if (_LEDstat == true) {
    // if _LEDstat is true, then turn _LEDstat false and return the assigned value of T1_ms
    _LEDstat = false;
		_blinkCounter = 0;
		_T1start_ms = millis();
    _retT_ms = _T1_ms;
    _N1now++;
    if (_N1now >= _N1) {
      _N1now = 0;
      _flag_useT2 = true;
    }
    return(_retT_ms);
  }

  return(0); /* NotReached */
}

// ---------------------------------------------------------
