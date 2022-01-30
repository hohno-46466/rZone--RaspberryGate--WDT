//
// taskClass4.cpp
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// task4 - Generate notification signal for Raspberry Pi

// ---------------------------------------------------------

#include "Arduino.h"
#include "taskClass4.h"
#include "mydefs.h"

extern uint32_t CurrentTime_8ms;
extern uint32_t eightMillis();

// ---------------------------------------------------------

// taskClass4::taskClass4(int pin)
//   pin - pin No. to notify to Raspberry Pi

taskClass4::taskClass4(int pin) {
  _pin = pin;
}

// ---------------------------------------------------------

// taskClass4::init()
// taskClass4::init(int pin)
//   pin - pin No. to notify to Raspberry Pi

boolean taskClass4::init() {
  if (_pin <= 0) { return(false); }
  pinMode(_pin, OUTPUT);
  return(true);
}

boolean taskClass4::init(int pin) {
  _pin = pin;
  if (_pin <= 0) { return(false); }
  pinMode(_pin, OUTPUT);
  return(true);
}

// ---------------------------------------------------------
