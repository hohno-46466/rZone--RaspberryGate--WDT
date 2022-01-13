//
// taskClass3.cpp
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// taskClass3 --

// ---------------------------------------------------------

#include "Arduino.h"
#include "taskClass3.h"
#include "mydefs.h"

extern uint32_t GLOBAL_ten_millis_curr;
extern uint32_t tenMillis();

// ---------------------------------------------------------

// taskClass3::taskClass3(int pin)
//   pin - pin No. to reset Raspberry Pi

taskClass3::taskClass3(int pin) {
	_pin = pin;
	if (_pin > 0) {
		pinMode(_pin, OUTPUT);
		digitalWrite(_pin, LOW);
	}
}

// ---------------------------------------------------------
