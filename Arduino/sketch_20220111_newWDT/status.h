#ifndef __STATUS_H__
#define __STATUS_H__

//
// status.h
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

#include "Arduino.h"

class status {
 public:
	status();
	void init();
	void task0set(int x);
	int task0get();
	void task3set(int x);
	int task3get();
	void show();
	boolean should_be_reboot();
 private:
	int _verbose = -1;
};

// ---------------------------------------------------------

#endif  // __STATUS_H__
