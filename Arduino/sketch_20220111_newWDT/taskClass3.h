#ifndef __TASK_CLASS_3_H__
#define __TASK_CLASS_3_H__

//
// taskClass3.h
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

#include "Arduino.h"

class taskClass3 {
 public:
	taskClass3(int pin);
 private:
	int _pin = -1;
};

// ---------------------------------------------------------

#endif // __TASK_CLASS_3_H__
