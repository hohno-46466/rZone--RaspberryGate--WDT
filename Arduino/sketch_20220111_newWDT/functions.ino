//
// functions.ino
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// *** IMPORTANT NOTICE ***
// Since this sketch has an "ino" extention, this file will be inserted
// in the main sketch (sketch_20220111_newWDT.ino) before each compilation

// ---------------------------------------------------------

// ---------------------------------------------------------
// sub functions
// ---------------------------------------------------------

uint32_t tenMillis() {
  static int _cntOVF = 0;
  static uint32_t _now_8ms = 0;
  static uint32_t _prev_1ms = 0, _now_1ms = 0;

  _now_1ms = millis();

  if (_now_1ms < _prev_1ms) {
    // increment the overflow counter
    _cntOVF++;
  }
  _now_8ms = (_now_1ms / 10UL) + (_cntOVF % 10) * 429496729UL;
  _prev_1ms = _now_1ms;

  return(_now_8ms);
}

// ---------------------------------------------------------

uint32_t eightMillis() {
  static int _cntOVF = 0;
  static uint32_t _now_8ms = 0;
  static uint32_t _prev_1ms = 0, _now_1ms = 0;

  _now_1ms = millis();

  if (_now_1ms < _prev_1ms) {
    // increment the overflow counter
    _cntOVF++;
  }
  _now_8ms = (_now_1ms / 8UL) + (_cntOVF % 8) * 536870912UL;
  _prev_1ms = _now_1ms;

  return(_now_8ms);
}

// ---------------------------------------------------------
