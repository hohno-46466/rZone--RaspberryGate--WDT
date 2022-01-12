#ifndef _TASK_CLASS1_H_
#define _TASK_CLASS1_H_

//
// taskClass1.h
//
// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

#include "Arduino.h"

class taskClass1 {
 public:
	taskClass1(int pin);
	void set(int arg1, int arg2);
	boolean blink();
	void stop();
 private:
	int _pin = -1;
	int _arg1 = -1;
	int _arg2 = -1;
	int _prev_arg1 = 0;
	int _prev_arg2 = 0;
	boolean _flag = false;
	uint32_t _ten_millis_next = 0;
};

// ---------------------------------------------------------

#endif // _TASK_CLASS1_H_
