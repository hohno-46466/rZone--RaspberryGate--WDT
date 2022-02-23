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
    _pullup = pullup;
    pinMode(_pin, _pullup ? INPUT_PULLUP : INPUT);
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
  _pullup = pullup;
  pinMode(_pin, _pullup ? INPUT_PULLUP : INPUT);

  return(true);
}

// ---------------------------------------------------------

// int classButtonSW::setSensitivity(int updown)

int classButtonSW::setSensitivity(int updown) {
  const int __updown_min = 0x05; // (_LEVEL_MAX - _LEVEL_MIN) *  5 / 100;
  const int __updown_max = 0x40; // (_LEVEL_MAX - _LEVEL_MIN) * 40 / 100;

  if (updown < __updown_min) {
    _updown = __updown_min;
  } else if (updown > __updown_max) {
    _updown = __updown_max;
  } else {
    _updown = updown;
  }

  return(_updown);
}

// ---------------------------------------------------------

#define _GET_PULSE (digitalRead(_pin) == (_positive ? HIGH : LOW))
#define _BUTTON_SCAN_INTERVAL_MIN   (8)

// boolean classButtonSW::update()

boolean classButtonSW::update() {
  // digital debouncing

  static uint32_t __lastTime_ms = 0;
  uint32_t __currentTime_ms = millis();

  if ((__currentTime_ms - __lastTime_ms) <= _BUTTON_SCAN_INTERVAL_MIN) {
    // avoid excessive access to the button
    return(_buttonState);
  }

  boolean _pulseState = _GET_PULSE;

  // update _currentVal
  if (_pulseState) {
    _currentVal += _updown;
    if (_currentVal > _LEVEL_MAX) { _currentVal = _LEVEL_MAX; }

  } else {
    _currentVal -= _updown;
    if (_currentVal < _LEVEL_MIN) { _currentVal = _LEVEL_MIN; }
  }

  if (((_buttonState == SW_OFF) || (_buttonState == SW_UNKNOWN)) && (_currentVal > _LEVEL_L2H)) {
    // SW OFF -> SW ON
    _buttonState = SW_ON;
    _last_OFFtoON_ms = millis();

  } else if ((_buttonState == SW_ON) && (_currentVal < _LEVEL_L2H)) {
    // SW ON -> SW OFF
    _buttonState = SW_OFF;
    _last_ONtoOFF_ms = millis();
  }

  return(_buttonState);
}

// ---------------------------------------------------------

// int classButtonSW::getStat()

int classButtonSW::getStat() {
  return(_buttonState);
}

// ---------------------------------------------------------

// uint32_t classButtonSW::getLastONtoOFF();

uint32_t classButtonSW::getLastONtoOFF(){
  return(_last_ONtoOFF_ms);
}

// ---------------------------------------------------------

// uint32_t classButtonSW::getLastOFFtoON()

uint32_t classButtonSW::getLastOFFtoON(){
  return(_last_OFFtoON_ms);
}

// ---------------------------------------------------------
