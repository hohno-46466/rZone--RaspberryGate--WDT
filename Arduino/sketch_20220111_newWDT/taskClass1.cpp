//
// taskClass1.cpp
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// taskClass1 -- Blink LED to show the current status

// ---------------------------------------------------------

#include "Arduino.h"
#include "taskClass1.h"
#include "classBlinkLED.h"
#include "mydefs.h"

extern uint32_t CurrentTime_8ms;
extern uint32_t eightMillis();

// ---------------------------------------------------------

// taskClass1::taskClass1(int pin)
//   pin - pin No. to blink a LED

taskClass1::taskClass1(int pin) {
	_pin = pin;
}

// ---------------------------------------------------------

// taskClass1::init()
// taskClass1::init(int pin)
//   pin - pin No. to blink a LED

boolean taskClass1::init() {
	if (_pin <= 1) { return(false); }
	pinMode(_pin,  OUTPUT);
	return(true);
}

boolean taskClass1::init(int pin) {
	_pin = pin;
	if (_pin <= 1) { return(false); }
	pinMode(_pin,  OUTPUT);
	return(true);
}

// ---------------------------------------------------------
