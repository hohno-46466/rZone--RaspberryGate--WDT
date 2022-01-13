//
// taskClass2.cpp
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// taskClass2 --

// ---------------------------------------------------------

#include "Arduino.h"
#include "taskClass2.h"
#include "mydefs.h"

extern uint32_t GLOBAL_8millis_curr;
extern uint32_t tenMillis();

// ---------------------------------------------------------

// taskClass2::taskClass2(int pin)
//   pin - pin No. to receive WDT pulse

taskClass2::taskClass2(int pin) {
	_pin = pin;
	if (_pin > 0) {
		pinMode(_pin, INPUT_PULLUP);
	}
}

// ---------------------------------------------------------
