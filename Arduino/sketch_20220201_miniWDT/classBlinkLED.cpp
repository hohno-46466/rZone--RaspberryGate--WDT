//
// classBlink.cpp for miniWDT
//

// ---------------------------------------------------------

#if 0
# WARNING: !!! This sketch is under development. Please do not build it!
#endif // 0 or 1

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

// void classBlinkLED::setParam(int32_t T0_ms, int32_t T1_ms, boolean reverseAction)
//   T0_ms - duration of LED OFF (in msec);
//   T1_ms - duration of LED ON (in msec)
//   reverseAction - set it true if you take reverse action (only useful for LED blink)

// void classBlinkLED::setParam(int32_t T0_ms, int32_t T1_ms, int32_t T2_ms, int N, boolean reverseAction)
//   T0_ms - duration of LED OFF before T1 (in msec)
//   T1_ms - duration of LED ON (in msec);
//   T2_ms - duration of LED OFF after T1 (in msec)
//   N     - number of additional repeat (0 is no repeat, 1 is repeat once (2 in total), -1 is repeat forever)
//   (if N = 3, then ((T0,T1),(T0,T1),(T0,T1),T2 [End])
//   reverseAction - set it true if you take reverse action (only useful for LED blink)

// void classBlinkLED::setParam(int32_t T0_ms, int32_t T1_ms, int32_t T2_ms, int N1, int N2, boolean reverseAction)
//   T0_ms - duration of LED OFF before T1 (in msec)
//   T1_ms - duration of LED ON (in msec);
//   T2_ms - duration of LED OFF after T1 (in msec)
//   N1    - number of additional repeat of (T0+T1)
//   N2    - number of additional repeat of ((T0+T1) x N1 + T2)
//   (if N1 = 3 and N2 = 2, then (((((T0,T1),(T0,T1),(T0,T1)),T2), ((T0,T1),(T0,T1),(T0,T1)),T2), [End])

void classBlinkLED::setParam(int32_t T0_ms, int32_t T1_ms, boolean reverseAction) {
  _flag_blink = true;
  _blinkCounter = 0;
  _blinkCounterPrev = -1;
  _LEDstat = true;    // A trick to start this sketch with the LED off
  _T0_ms = T0_ms;
  _T1_ms = T1_ms;
  _T2_ms = 0;
  _N1 = (uint16_t)-1; // repeat (almost) forever
  _N2 = 0;
  _flag_reverseAction = reverseAction;
  _N1now = 0;
  _N2now = 0;
  _Tnext_ms = millis();
#ifdef USE_GBKA
  Serial.print("# setParam()");
  Serial.print("  _T0_ms = "); Serial.print(_T0_ms);
  Serial.print(", _T1_ms = "); Serial.print(_T1_ms);
  Serial.print(", _T2_ms = "); Serial.print(_T2_ms);
  Serial.print(", _N1 = "); Serial.print(_N1);
  Serial.print(", _N2 = "); Serial.print(_N2);
  Serial.println();
#endif // USE_GBKA
}

void classBlinkLED::setParam(int32_t T0_ms, int32_t T1_ms, int32_t T2_ms, int N, boolean reverseAction) {
  // N x (T0 + T1) + T2 [End]
  _flag_blink = true;
  _blinkCounter = 0;
  _blinkCounterPrev = -1;
  _LEDstat = true;    // A trick to start this sketch with the LED off
  _T0_ms = T0_ms;
  _T1_ms = T1_ms;
  _T2_ms = T2_ms;
  _N1 = (uint16_t)N;
  _N2 = 0;
  _flag_reverseAction = reverseAction;
  _N1now = 0;
  _N2now = 0;
  _Tnext_ms = millis();
#ifdef USE_GBKA
  Serial.print("# setParam()");
  Serial.print("  _T0_ms = "); Serial.print(_T0_ms);
  Serial.print(", _T1_ms = "); Serial.print(_T1_ms);
  Serial.print(", _T2_ms = "); Serial.print(_T2_ms);
  Serial.print(", _N1 = "); Serial.print(_N1);
  Serial.print(", _N2 = "); Serial.print(_N2);
  Serial.println();
#endif // USE_GBKA
}

void classBlinkLED::setParam(int32_t T0_ms, int32_t T1_ms, int32_t T2_ms, int N1, int N2, boolean reverseAction) {
    // N2 x (N1 x (T0 + T1) + T2) [End]
  _flag_blink = true;
  _blinkCounter = 0;
  _blinkCounterPrev = -1;
  _LEDstat = true;    // A trick to start this sketch with the LED off
  _T0_ms = T0_ms;
  _T1_ms = T1_ms;
  _T2_ms = T2_ms;
  _N1 = (uint16_t)N1;
  _N2 = (uint16_t)N2;
  _flag_reverseAction = reverseAction;
  _N1now = 0;
  _N2now = 0;
  _Tnext_ms = millis();
#ifdef USE_GBKA
  Serial.print("# setParam()");
  Serial.print("  _T0_ms = "); Serial.print(_T0_ms);
  Serial.print(", _T1_ms = "); Serial.print(_T1_ms);
  Serial.print(", _T2_ms = "); Serial.print(_T2_ms);
  Serial.print(", _N1 = "); if (1) {Serial.print(N1); Serial.print("-> ");} Serial.print(_N1);
  Serial.print(", _N2 = "); if (1) {Serial.print(N2); Serial.print("-> ");} Serial.print(_N2);
  Serial.println();
#endif // USE_GBKA
}

// ---------------------------------------------------------

// boolean classBlinkLED::update()
// returns
//   tru  - LED is ON
//   false - LED is OFF

#define _LED_ON    (digitalWrite(_pin, LOGIC_LED ? HIGH : LOW))
#define _LED_OFF   (digitalWrite(_pin, LOGIC_LED ? LOW : HIGH))

boolean classBlinkLED::update() {

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
      _flag_blink = false;
      return(false);
    }

    _Tnext_ms += _tmp_ms;
    if (_LEDstat) {
      if (_flag_reverseAction) { _LED_OFF; } else { _LED_ON; }
    } else {
      if (_flag_reverseAction) { _LED_ON; } else { _LED_OFF; }
    }
  }
  _flag_blink = true;

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

// int classBlinkLED::blinkStat()

int classBlinkLED::blinkStat() {
  int __retval = _flag_blink ? 1 : 0;
  // __retval will be expanded for more informatio with it

  return(__retval);
}


// ---------------------------------------------------------

// int classBlinkLED::blinkCounter()

int classBlinkLED::blinkCounter() {
  return(_blinkCounter);
}

// ---------------------------------------------------------
// ---------------------------------------------------------

/*private*/ int32_t classBlinkLED::_updateTnext_ms() {

  int32_t __retT_ms = 0;

  // (((T0,T1),(T0,T1), ..),T2,)...

    if (_flag_DLdone) {
      // if true, return -1 instead of returning the valid Tnext_ms value.
      // This tells the caller to terminate the double loop.
    _flag_DLdone = false;
    _flag_blink = false;

#ifdef USE_GBKA
#if (DEBUG_LEVEL > 2)
    Serial.println("# The double loop has been done, and blinking will be stopped");
#endif // (DEBUG_LEVEL > 2)
#endif // USE_GBKA

    return(-1);
  }

  if (_T2mode) {

#ifdef USE_GBKA
#if (DEBUG_LEVEL > 2)
    _loopCounter++;
    Serial.print("# _T2mode is true (The inner loop has been done). _loopCounter = ");
    Serial.print(_loopCounter);
    Serial.println();
#endif // (DEBUG_LEVEL > 2)
#endif // USE_GBKA

    _LEDstat = false;
    _blinkCounter = 0;
    _blinkCounterPrev = 0;
    _T2start_ms = millis();
    __retT_ms = _T2_ms;
    _N2now++;
    if (_N2now > _N2) {
      // if the double loop (both innner and outer) has been done, set _flag_DLdone true;
    _flag_DLdone = true;
    }
    _T2mode = false;
    return(__retT_ms);
  }

  // XXX

  if (_LEDstat == true) {
    // if _LEDstat is true, then turn _LEDstat false and return the assigned value of T0_ms
    _LEDstat = false;
    _blinkCounter = 0; // _blinkCounter is always zero when the LED is off.
    _T0start_ms = millis();
    __retT_ms = _T0_ms;

#ifdef USE_GBKA
#if (DEBUG_LEVEL > 3)
    Serial.print("# _LEDstat true -> false");
    Serial.print(", __retT_ms = "); Serial.print(__retT_ms);
    Serial.println();
#endif // (DEBUG_LEVEL > 3)
#endif // USE_GBKA


    return(__retT_ms);
  }

  if (_LEDstat == false) {
    // if _LEDstat is false, then turn _LEDstat true and return the assigned value of T1_ms
    _LEDstat = true;
    _blinkCounter = _blinkCounterPrev + 1; // _blinkCounter counts the number of LED on in this period (_blinkCounter rises from 1 to N1*N2-1
    _blinkCounterPrev = _blinkCounter;
    _T1start_ms = millis();
    __retT_ms = _T1_ms;
    _N1now++;
    if (_N1now > _N1) {
      _N1now = 0;
      _T2mode = true;
    }

#ifdef USE_GBKA
#if (DEBUG_LEVEL > 3)
    Serial.print("# _LEDstat false -> true");
    Serial.print(", _N1 = "); Serial.print(_N1);
    Serial.print(", _N1now = "); Serial.print(_N1now);
    Serial.print(", _N2 = "); Serial.print(_N2);
    Serial.print(", _N2now = "); Serial.print(_N2now);
    Serial.print(", _blinkCounter = "); Serial.print(_blinkCounter);
    Serial.print(", _blinkCounterPrev = "); Serial.print(_blinkCounterPrev);
    Serial.print(", _T2mode= "); Serial.print(_T2mode);
    Serial.print(", __retT_ms = "); Serial.print(__retT_ms);
    Serial.println();
#endif // (DEBUG_LEVEL > 3)
#endif // USE_GBKA

    return(__retT_ms);
  }

#ifdef USE_GBKA
  Serial.println("# it should not be here!");
#endif // USE_GBKA

  return(-1); /* NotReached */
}

// ---------------------------------------------------------
