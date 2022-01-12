#ifndef __TASK_CLASS_2_H__
#define __TASK_CLASS_2_H__

//
// taskClass2.h
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

#include "Arduino.h"

class taskClass2 {
 public:
	taskClass2(int pin);
 private:
	int _pin = -1;
};

// ---------------------------------------------------------

#endif // __TASK_CLASS_2_H__
