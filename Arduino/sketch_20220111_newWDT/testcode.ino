//
// testcode.ino
//

#ifdef test_mode

// ---------------------------------------------------------

#define TEST_BUTTON_ON_GBKA
// #define TEST_BLINK_ON_GBKA

// ---------------------------------------------------------<

#ifdef TEST_BLINK_ON_GBKA
#ifndef  USE_GBKA
XXX DEFINE USE_GBKA IF YOU DEFINE TEST_BLINK_ON_GBKA XXX
#endif  // USE_GBKA

classBlinkLED test1;

void setupXtest() {

  Serial.println("# *** TEST_BLINK_ON_GBKA ***"); Serial.println();

  test1.init(PIN_O_LED, POSITIVE_LOGIC);
}

// -----------------------------------------------

void loopXtest() {

if (debug_cnt < 5) {
    test1.setParam(500,500); test1.blink();

  } else if (debug_cnt < 10) {
    test1.setParam(250,250); test1.blink();

  } else if (debug_cnt < 15) {
    test1.setParam(100,100); test1.blink();

  } else if (debug_cnt < 20) {
    test1.setParam(50,50); test1.blink();

  } else {
    test1.setParam(20,20); test1.blink();
  }

}

#endif  // TEST_BLINK_ON_GBKA


// ---------------------------------------------------------<

#ifdef TEST_BUTTON_ON_GBKA
#ifndef  USE_GBKA
XXX DEFINE USE_GBKA IF YOU DEFINE TEST_BUTTON_ON_GBKA XXX
#endif  // USE_GBKA

classButtonSW test0;

void setupXtest() {

  Serial.println("# *** TEST_BUTTON_ON_GBKA ***"); Serial.println();

  test0.init(PIN_I_PULSE, USE_PULLUP, POSITIVE_LOGIC);
}

// -----------------------------------------------

void loopXtest() {

    static uint32_t _lastPulse_8ms = 0;
  static int _vNow = 0, _vPrev = 0;

  CurrentTime_8ms = eightMillis();

  if ((CurrentTime_8ms - _lastPulse_8ms) > 1) {
      _lastPulse_8ms = CurrentTime_8ms;
      _vNow = test0.update();
      if (_vNow != _vPrev) {
        Serial.print("_vNow = "); Serial.println(_vNow);
      }
      _vPrev = _vNow;
  }
}

#endif // TEST_BUTTON_ON_GBKA

// ---------------------------------------------------------

#endif  // test_mode
