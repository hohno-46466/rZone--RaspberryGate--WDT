//
// taskClass4.cpp
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// taskClass4 --

// ---------------------------------------------------------

#include "Arduino.h"
#include "taskClass4.h"
#include "mydefs.h"

extern uint32_t GLOBAL_8millis_curr;
extern uint32_t tenMillis();

// ---------------------------------------------------------

// taskClass4::taskClass4(int pin)
//   pin - pin No. to notify to Raspberry Pi

taskClass4::taskClass4(int pin) {
	_pin = pin;
	if (_pin > 0) {
		pinMode(_pin, OUTPUT);
		digitalWrite(_pin, LOW);
	}
}

// ---------------------------------------------------------
