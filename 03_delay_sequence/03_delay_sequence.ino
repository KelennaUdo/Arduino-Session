/*
  03 — Make the selected LED advance

  This builds on 01 (read inputs) and 02 (select an LED). The sequence
  advances every 500 ms. It is deliberately built with delay() so you
  can notice what happens to a short button press during the wait.
*/
const int ledPins[] = {22, 23, 24, 25, 26, 27, 28, 29};
const int ledCount = 8;
const int buttonPin = 2;
const int potPin = A0;

// Keep the selected index after each pass through loop().
int currentLed = 0;

void showLed() {
  // Clear the previous light, then show exactly one selected LED.
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  digitalWrite(ledPins[currentLed], HIGH);
}

void advanceLed() {
  // Move to the next array position.
  currentLed++;
  // Valid indexes are 0 through 7. After 7, wrap back to 0.
  // This check happens before showLed(), so we never access ledPins[8].
  if (currentLed >= ledCount) {
    currentLed = 0;
  }
  showLed();
}

void setup() {
  // setup() runs once: start Serial, configure pins, show LED zero.
  Serial.begin(9600);
  // With INPUT_PULLUP, released reads HIGH and pressed reads LOW.
  pinMode(buttonPin, INPUT_PULLUP);
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  showLed();
}

void loop() {
  // Pause the entire sketch for half a second. A press and release that
  // happens during this time may be missed by the next digitalRead().
  delay(500);

  // We sample the inputs once after the pause. Serial shows the values,
  // but this sketch does not yet use them to control the LED sequence.
  bool buttonState = digitalRead(buttonPin);
  int potValue = analogRead(potPin);
  Serial.print("button = ");
  Serial.print(buttonState);
  Serial.print("   pot = ");
  Serial.println(potValue);

  // Advance one LED only after printing the current input readings.
  advanceLed();
  // Try a quick press: do you always see it in Serial Monitor?
  // Sketch 04 keeps checking without making loop() wait.
}
