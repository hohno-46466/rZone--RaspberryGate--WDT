#ifndef __WDT_STATUS_H__
#define __WDT_STATUS_H__

//
// WDTstatus.h
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

#include "Arduino.h"

class WDTstatus {
 public:
	WDTstatus();
	void init();
	void task0set(int x);
	int task0get();
	void task1set(int x);
	int task1get();
	void task2set(int x);
	int task2get();
	void task3set(int x);
	int task3get();
	void task4set(int x);
	int task4get();
	void taskXset(int x);
	int taskXget();
	void show();
	void update();
	int getStatus();
 private:
	int _verbose = -1;
};

// ---------------------------------------------------------

#endif  // __WDT_STATUS_H__
