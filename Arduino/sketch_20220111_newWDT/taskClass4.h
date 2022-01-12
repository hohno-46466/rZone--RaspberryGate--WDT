#ifndef __TASK_CLASS_4_H__
#define __TASK_CLASS_4_H__

//
// taskClass4.h
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

#include "Arduino.h"

class taskClass4 {
 public:
	taskClass4(int pin);
 private:
	int _pin = -1;
};

// ---------------------------------------------------------

#endif // __TASK_CLASS_4_H__
