//
// classBlinkLED.cpp
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// classBlinkLED -- Blink LED to show the current status

// ---------------------------------------------------------

#include "Arduino.h"
#include "classBlinkLED.h"
#include "mydefs.h"

extern uint32_t CurrentTime_8ms;
extern uint32_t eightMillis();

// ---------------------------------------------------------

// classBlinkLED::classBlinkLED()

classBlinkLED::classBlinkLED() {
  // _pin = pin;
  if (_pin > 0) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
  }
}

classBlinkLED::classBlinkLED(int pin) {
  _pin = pin;
  if (_pin > 0) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
  }
}

// ---------------------------------------------------------

// void classBlinkLED::set(int arg1, int arg2)
//   arg1 - duration of LED ON (in msec);
//   arg2 - duration of LED OFF (in msec)

void classBlinkLED::set(int arg1, int arg2) {
  _arg1 = arg1;
  _arg2 = arg2;
}

// ---------------------------------------------------------

// boolean classBlinkLED::blink()
// returns
//   true  - LED is ON
//   false - LED is OFF

#define _LED_ON    (digitalWrite(_pin, HIGH))
#define _LED_OFF   (digitalWrite(_pin, LOW))

boolean classBlinkLED::blink() {
  if ((_pin < 0) || (_arg1 < 0) || (_arg2 < 0)) {
    return(false);
  }
  if ((_arg1 == _prev_arg1) && (_arg2 == _prev_arg2)) {
    // Both arg1 and arg2 are not updated
    if (_next_8ms <= CurrentTime_8ms) {
      if (_flag) {
        _flag = false;
        _next_8ms += (_arg2/8);
        _LED_OFF;
      } else {
        _flag = true;
        _next_8ms += (_arg1/8);;
        _LED_ON;
      }
    }
  } else {
    // at least one of _arg1 and _arg2 was updated
    _prev_arg1 = _arg1;
    _prev_arg2 = _arg2;
    // _next_8ms = (millis() + _arg1) / 10;
    _next_8ms = eightMillis() + (_arg1 / 8);
    _flag = true;
    _LED_ON;
  }

  return(_flag);
}

// ---------------------------------------------------------

// void classBlinkLED::stop()

void classBlinkLED::stop() {
}

// ---------------------------------------------------------


// ---------------------------------------------------------
