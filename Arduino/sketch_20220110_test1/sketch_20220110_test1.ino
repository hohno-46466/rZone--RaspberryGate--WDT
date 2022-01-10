//
// sketch_20220110_test1
//

#define PIN_LED	(13)

void setup() {
  // setup function is here
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
}

void loop() {
  // loop function is here
  digitalWrite(PIN_LED, HIGH);
  delay(350);
  digitalWrite(PIN_LED, LOW);
  delay(650);
}
