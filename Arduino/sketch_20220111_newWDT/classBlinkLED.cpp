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

void classBlinkLED::setParam(int Ton, int Toff) {
  _Ton = Ton;
  _Toff = Toff;
}

// ---------------------------------------------------------

// boolean classBlinkLED::blink()
// returns
//   true  - LED is ON
//   false - LED is OFF

#define _LED_ON    (digitalWrite(_pin, HIGH))
#define _LED_OFF   (digitalWrite(_pin, LOW))

boolean classBlinkLED::blink() {
  if ((_pin < 0) || (_Ton < 0) || (_Toff < 0)) {
    return(false);
  }
  if ((_Ton == _prev_Ton) && (_Toff == _prev_Toff)) {
    // Both Ton and Toff are not updated
    if (_Tnext_8ms <= CurrentTime_8ms) {
      if (_LEDstat) {
        _LEDstat = false;
        _Tnext_8ms += (_Toff/8);
        _LED_OFF;
      } else {
        _LEDstat = true;
        _Tnext_8ms += (_Ton/8);;
        _LED_ON;
      }
    }
  } else {
    // at least one of _Ton and _Toff was updated
    _prev_Ton = _Ton;
    _prev_Toff = _Toff;
    // _Tnext_8ms = (millis() + _Ton) / 10;
    _Tnext_8ms = eightMillis() + (_Ton / 8);
    _LEDstat = true;
    _LED_ON;
  }

  return(_LEDstat);
}

// ---------------------------------------------------------

// void classBlinkLED::stop()

void classBlinkLED::stop() {
}

// ---------------------------------------------------------


// ---------------------------------------------------------
