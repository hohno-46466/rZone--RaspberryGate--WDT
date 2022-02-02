//
// sketch_20220201_miniWDT.ino
//

struct pinInfo {
  uint8_t stat;
  uint32_t timstamp;
};

pinInfo heatbeat = {0, 0}, wdtType = {0, 0};

int alertLevel = -1;
int WDTime = 0;

void setup() {


}


void main() {

  if (alertLevel == 0) {
    //
    WDTime = updateInputPins();
    if (WDTime >= 30) {
      alertLevel = 1;
    }
    //

  } else if (alertLevel >= 1) {
      //
    if (alertLevel == 1) {
      //
      if (wdtType.stat == 0) {
        setResetPulse(1, 1, 1);
      } else {
        setResetPulse(600, 1, 1);
      }
      // setNotification();
      // startBlinking();
      alertLevel = 2;

    } else {
      //
      updateOutputPins();
      //
    }

  }
}


