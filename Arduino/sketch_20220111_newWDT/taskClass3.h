#ifndef __TASK_CLASS_3_H__
#define __TASK_CLASS_3_H__

//
// taskClass3.h
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// task3 - Generate RESET pulse (for both of the gentle and the delayed watchdog)

// ---------------------------------------------------------

#include "Arduino.h"

class taskClass3 {
 public:
	taskClass3(int pin);
	boolean init();
	boolean init(int pin);
	int core(int32_t arg1, int32_t arg2, int32_t arg3, int arg4);
 private:
	int _pin = -1;
};

// ---------------------------------------------------------

#endif // __TASK_CLASS_3_H__
