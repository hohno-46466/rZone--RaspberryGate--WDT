#ifndef __TASK_CLASS_1_H__
#define __TASK_CLASS_1_H__

//
// taskClass1.h
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// taskClass1 -- Blink LED to show the current status

// ---------------------------------------------------------

#include "Arduino.h"
#include "classBlinkLED.h"

class taskClass1 : public classBlinkLED {
 public:
	taskClass1(int pin); // : classBlinkLED(13){};
	boolean init();
	boolean init(int pin);
 private:
	int _pin = -1;
};

// ---------------------------------------------------------

#endif // __TASK_CLASS_1_H__
