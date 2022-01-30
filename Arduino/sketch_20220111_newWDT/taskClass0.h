#ifndef __TASK_CLASS_0_H__
#define __TASK_CLASS_0_H__

//
// taskClass0.h
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

// task0 - Check the "heart beat" pulse from Raspberry Pi

// ---------------------------------------------------------

#include "Arduino.h"

class taskClass0 {
 public:
  taskClass0(int pin);
  boolean init();
  boolean init(int pin);
  float core();
 private:
  int _pin = -1;
};

// ---------------------------------------------------------

#endif  // __TASK_CLASS_0_H__
