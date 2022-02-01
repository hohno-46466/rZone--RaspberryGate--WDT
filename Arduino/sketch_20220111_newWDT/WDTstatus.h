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
  int getStat();
 private:
  int _verbose = -1;
  int _statTask0 = -1, _prevTask0 = -1;
  int _statTask1 = -1, _prevTask1 = -1;
  int _statTask2 = -1, _prevTask2 = -1;
  int _statTask3 = -1, _prevTask3 = -1;
  int _rule1();
  int _rule2();
};

// ---------------------------------------------------------

#endif  // __WDT_STATUS_H__
