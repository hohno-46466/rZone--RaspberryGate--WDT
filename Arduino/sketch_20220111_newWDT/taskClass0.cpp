//
// taskClass0.cpp
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// taskClass0 --

// ---------------------------------------------------------

#include "Arduino.h"
#include "taskClass0.h"
#include "mydefs.h"

extern uint32_t Global_ten_millis_curr;
extern uint32_t tenMillis();

// ---------------------------------------------------------

// taskClass0::taskClass0(int pin)
//   pin - pin No. to receive WDT pulse

taskClass0::taskClass0(int pin) {
	_pin = pin;
	if (_pin > 0) {
		pinMode(_pin, INPUT_PULLUP);
	}
}

// ---------------------------------------------------------
