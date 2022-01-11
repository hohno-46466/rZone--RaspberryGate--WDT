#ifndef __MYDEFS_H__
#define __MYDEFS_H__

//
// mydefs.h
//

// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc


// ---------------------------------------------------------

const int PIN_0 = 0;
const int PIN_1 = 1;
const int PIN_2 = 2;
const int PIN_3 = 3;
const int PIN_4 = 4;
const int PIN_5 = 5;

// ---------------------------------------------------------

#define PIN_I_PULSE   (PIN_0)
#define PIN_O_LED     (PIN_1)
#define PIN_I_REQ     (PIN_2)
#define PIN_O_RESET   (PIN_3)
#define PIN_O_NOTE    (PIN_4)

#define ATT_LED_ON    (digitalWrite(PIN_O_LED, HIGH))
#define ATT_LED_OFF   (digitalWrite(PIN_O_LED, LOW))

#define ATT_NOTE_ON   (digitalWrite(PIN_O_NOTE, LOW))
#define ATT_NOTE_OFF  (digitalWrite(PIN_O_NOTE, HIGH))

#define ATT_RESET_ON  (digitalWrite(PIN_O_RESET, LOW))
#define ATT_RESET_OFF (digitalWrite(PIN_O_RESET, HIGH))


// ---------------------------------------------------------

#endif // __MYDEFS_H__
