//
// sketch_20220201_miniWDT.ino
//

// ---------------------------------------------------------

// History:
// First version: Wed Feb  2 19:15:12 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

#include "inputPins.h"
#include "outputPins.h"
#include "mydefs.h"

int alertLevel = ALERT_BEFORE_START;
int prevLevel = ALERT_UNDEF;
int32_t HBinterval_ms = -1;
int32_t HBintervalLimit_ms = HB_INTERVAL_L_MS;

inputPins iPins;
outputPins oPins;

// ---------------------------------------------------------
// setup()
// ---------------------------------------------------------

void setup() {
  if (testMode) {
    setup4test();
  } else {
    setup4main();
  }
}

// ---------------------------------------------------------

void setup4test() {

  int32_t T0_ms = 1000, T1_ms = 1000, T2_ms = 1000;
  int N1 = -1, N2 = -1;
  boolean reverseAction = false;

#ifdef USE_GBKA
  Serial.begin(57600);
  Serial.print("\n*** setup4test() ***\n\n");
#endif // USE_GBKA
  iPins.init();
  oPins.init();

  // T0_ms = 400, T1_ms = 100, T2_ms = 3000, N1 = 4, N2 = -1;
  T0_ms = 500, T1_ms = 500, T2_ms = 2000, N1 = 2, N2 = -1;
  reverseAction = false;
  oPins.setBlinking(T0_ms, T1_ms, T2_ms, N1, N2, reverseAction);
  oPins.startBlinking();

  T0_ms = 1*1000L; T1_ms = 2*1000L; T2_ms = 1*1000L;
  oPins.setResetPulse(T0_ms, T1_ms, T2_ms);
  oPins.stopResetPulse();

  T1_ms = 20*1000L;
  oPins.setNotification(T1_ms);
  oPins.stopNotification();

}

  // ---------------------------------------------------------


void setup4main() {

  int T0_s = 1, T1_s = 1, T2_s = 1, N1 = -1, N2 = -1;
  boolean reverseAction = false;

  iPins.init();
  oPins.init();

  HBinterval_ms = -1;
  HBintervalLimit_ms = HB_INTERVAL_L_MS;

  T0_s = 1; T1_s = 1; T2_s = 2; N1 = 2; N2 = 0;
  reverseAction = false;
  oPins.setBlinking(T0_s * 1000L, T1_s * 1000L, T2_s * 1000L, N1, N2, reverseAction);
  oPins.startBlinking();

  T0_s = 1; T1_s = 2; T2_s = 1;
  // reverseAction = false;
  oPins.setResetPulse(T0_s * 1000L, T1_s * 1000L, T2_s * 1000L);
  oPins.stopResetPulse();

  T1_s = 20;
  // reverseAction = false;
  oPins.setNotification(T1_s * 1000L);
  oPins.stopNotification();
}

// ---------------------------------------------------------
// loop()
// ---------------------------------------------------------

// AlertLevel:
// -1 : watchdog is not started.
//  0 : watchdog is running
//  1 : watchdog has detected timeout just now
//  2 : rebooting

void loop() {
  if (testMode) {
    loop4test();
  } else {
    loop4main();
  }
}

// ---------------------------------------------------------

classBlinkLED test;

void loop4test() {

  iPins.update();
  oPins.update();

	updateStateMachine4test();
}

// ---------------------------------------------------------

void loop4main() {

  iPins.update();
  oPins.update();

	updateStateMachine4main();

}

// ---------------------------------------------------------
