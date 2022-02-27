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
  const int __updown_min = 5;  // 0x05; // (_LEVEL_MAX - _LEVEL_MIN) *  5 / 100;
  const int __updown_max = 64; // 0x40; // (_LEVEL_MAX - _LEVEL_MIN) * 40 / 100;

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
  __lastTime_ms = __currentTime_ms;

  boolean __pulseState = _GET_PULSE;

  // update _currentButtonVal
  if (__pulseState) {
    _currentButtonVal += _updown;
    if (_currentButtonVal > _LEVEL_MAX) { _currentButtonVal = _LEVEL_MAX; }

  } else {
    _currentButtonVal -= _updown;
    if (_currentButtonVal < _LEVEL_MIN) { _currentButtonVal = _LEVEL_MIN; }
  }

  if (((_buttonState == SW_OFF) || (_buttonState == SW_UNKNOWN)) && (_currentButtonVal > _LEVEL_L2H)) {
    // SW OFF -> SW ON
    _buttonState = SW_ON;
    _lastOFFtoON_ms = millis();
    OnOffHistory_ms[_OnOffHistory_next][0] = _lastOFFtoON_ms;
#ifdef TEST_MODE
    globalTestFlag2 = true;
#endif // TEST_MODE

  } else if ((_buttonState == SW_ON) && (_currentButtonVal < _LEVEL_H2L)) {
    // SW ON -> SW OFF
    _buttonState = SW_OFF;
    _lastONtoOFF_ms = millis();

    OnOffHistory_ms[_OnOffHistory_next][1] = _lastONtoOFF_ms;
    _OnOffHistory_next = (_OnOffHistory_next + 1) % OnOffHistorySize;
    OnOffHistory_ms[_OnOffHistory_next][0] = 0UL;
    OnOffHistory_ms[_OnOffHistory_next][1] = 0UL;

#ifdef TEST_MODE
    globalTestFlag2 = true;
#endif // TEST_MODE
  }

  return(_buttonState);
}

// ---------------------------------------------------------

// int classButtonSW::getStat()

int classButtonSW::getStat() {
  return(_buttonState);
}

// ---------------------------------------------------------

// uint32_t classButtonSW::getLastONtoOFFtime_ms();

uint32_t classButtonSW::getLastONtoOFFtime_ms(){
  return(_lastONtoOFF_ms);
}

// ---------------------------------------------------------

// uint32_t classButtonSW::getLastOFFtoON()

uint32_t classButtonSW::getLastOFFtoONtime_ms(){
  return(_lastOFFtoON_ms);
}

// ---------------------------------------------------------

// int classButtonSW::getOnOffHistoryNext()

int classButtonSW::getOnOffHistoryNext(){
  return(_OnOffHistory_next);
}

// ---------------------------------------------------------

#ifdef TEST_MODE

// int classButtonSW::getCurrentButtonVal()

int classButtonSW::getCurrentButtonVal() {
  return(_currentButtonVal);
}

// void classButtonSW::showOnOffHistory()

void classButtonSW::showOnOffHistory() {

  int __index, __next, __start;

  __next = getOnOffHistoryNext();
  __index =(__next + 1) % OnOffHistorySize;
  __start = __index;

#ifdef USE_GBKA
  Serial.print("__next = "); Serial.print(__next);
  Serial.print(", __index = "); Serial.print(__index);
  Serial.print(", OnOffHistorySize = "); Serial.print(OnOffHistorySize);
  Serial.println();
#endif // USE_GBKA

  do {
#ifdef USE_GBKA
    Serial.print(OnOffHistory_ms[__index][1]- OnOffHistory_ms[__index][0]);
    Serial.print(", ");
#endif // USE_GBKA
    __index = (__index+ 1) % OnOffHistorySize;
  } while(__index != __start);
#ifdef USE_GBKA
  Serial.println();
#endif // USE_GBKA

  /*
  __index = (__next + 1) % OnOffHistorySize;

  while(__index != __next) {
    Serial.print(OnOffHistory_ms[__index][1]);
    Serial.print(", ");
    __index = (__index + 1) % OnOffHistorySize;
  }
  Serial.println();
  */
  Serial.println();

}

#endif // TEST_MODE

// ---------------------------------------------------------
