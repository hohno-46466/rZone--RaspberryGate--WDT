#ifndef __CLASS_BLINK_LED_H__
#define __CLASS_BLINK_LED_H__

//
// classBlinkLED.h for miniWDT
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc
// Revised: Thu Feb  3 12:59:16 JST 2022 for miniWDT

// ---------------------------------------------------------

// classBlinkLED -- Blink LED to show the current status

// ---------------------------------------------------------

#include "Arduino.h"

class classBlinkLED {
 public:
  classBlinkLED();
  classBlinkLED(int, boolean);
  boolean init(int, boolean);
  void setParam(int, int, boolean);
  void setParam(int, int, int, int, boolean);
	void setParam(int, int, int, int, int, boolean);
  boolean blink();
  void stop();
	void start();
 protected:
	int32_t _updateTnext_ms();
	boolean _flag_blink = false;
	boolean _flag_reverse = false;
  int _pin = -1;
  // int _Ton = -1;
  // int _Toff = -1;
  // int _prev_Ton = 0;
  // int _prev_Toff = 0;
  int _T0_ms = 1, _T0prev_ms = 0;
  int _T1_ms = 1, _T1prev_ms = 0;
  int _T2_ms = 1, _T2pre_msv = 0;
	uint16_t _N1 = 1, _N1now = 0;
	uint16_t _N2 = 0, _N2now = 0;
  boolean _LEDstat = false;
  uint32_t _Tnext_ms = 0;
  boolean _positive = true; // true: positive logic (HIGH is to turn LED on), false: negative logic (LOW is to turn LED on)
	boolean _flag_useT2 = false;
	boolean _flag_stop = false;
};

// ---------------------------------------------------------

#endif  // __CLASS_BLINK_LED_H__
