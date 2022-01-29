//
// taskClass2.cpp
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// task2 - Detect type-specified request from Raspberry Pi

// ---------------------------------------------------------

#include "Arduino.h"
#include "taskClass2.h"
#include "mydefs.h"

extern uint32_t CurrentTime_8ms;
extern uint32_t eightMillis();

// ---------------------------------------------------------

// taskClass2::taskClass2(int pin)
//   pin - pin No. to receive WDT pulse

taskClass2::taskClass2(int pin) {
	_pin = pin;
}

// ---------------------------------------------------------

// taskClass2::init()
// taskClass2::init(int pin)
//   pin - pin No. to receive WDT pulse

boolean taskClass2::init() {
	if (_pin <= 1) { return(false); }
	pinMode(_pin, INPUT_PULLUP);
	return(true);
}

boolean taskClass2::init(int pin) {
	_pin = pin;
	if (_pin <= 1) { return(false); }
	pinMode(_pin, INPUT_PULLUP);
	return(true);
}

// ---------------------------------------------------------
