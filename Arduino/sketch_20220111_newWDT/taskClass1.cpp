//
// taskClass1.cpp
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// taskClass1 -- blinkint LED

// ---------------------------------------------------------

#include "Arduino.h"
#include "taskClass1.h"
#include "mydefs.h"

extern uint32_t GLOBAL_8millis_curr;
extern uint32_t tenMillis();

// ---------------------------------------------------------

// taskClass1::taskClass1(int pin)
//   pin - pin No. to blink a LED

taskClass1::taskClass1(int pin) {
	_pin = pin;
	if (_pin > 0) {
		pinMode(_pin, OUTPUT);
		digitalWrite(_pin, LOW);
	}
}

// ---------------------------------------------------------

// void taskClass1::set(int arg1, int arg2)
//   arg1 - duration of LED ON (in msec);
//   arg2 - duration of LED OFF (in msec)

void taskClass1::set(int arg1, int arg2) {
	_arg1 = arg1;
	_arg2 = arg2;
}

// ---------------------------------------------------------

// boolean taskClass1::blink()
// returns
//   true  - LED is ON
//   false - LED is OFF

#define _LED_ON    (digitalWrite(_pin, HIGH))
#define _LED_OFF   (digitalWrite(_pin, LOW))

boolean taskClass1::blink() {
	if ((_pin < 0) || (_arg1 < 0) || (_arg2 < 0)) {
		return(false);
	}
	if ((_arg1 == _prev_arg1) && (_arg2 == _prev_arg2)) {
    // Both arg1 and arg2 are not updated
    if (_8millis_next <= GLOBAL_8millis_curr) {
      if (_flag) {
        _flag = false;
        _8millis_next += (_arg2/10);
        _LED_OFF;
      } else {
        _flag = true;
        _8millis_next += (_arg1/10);;
        _LED_ON;
      }
    }
  } else {
    // one of _arg1 and _arg2 was updated
    _prev_arg1 = _arg1;
    _prev_arg2 = _arg2;
		// _8millis_next = (millis() + _arg1) / 10;
    _8millis_next = tenMillis() + (_arg1 / 10);
    _flag = true;
    _LED_ON;
  }

  return(_flag);
}

// ---------------------------------------------------------

// void taskClass1::stop()

void taskClass1::stop() {
}

// ---------------------------------------------------------


// ---------------------------------------------------------
