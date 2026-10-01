/*
  02 — Select one LED from an array

  Goal: make one LED light up, then understand how a single index chooses
  between eight outputs. Each LED needs its own current-limiting resistor.
  Wire the LEDs to Mega pins 22–29; keep pins 0 and 1 free for USB Serial.

  Trace the idea: currentLed = 0 selects ledPins[0], which is pin 22.
  Arrays count from zero, so the last valid index here is 7, not 8.
*/

// The array keeps the eight related pin numbers in one place.
const int ledPins[] = {22, 23, 24, 25, 26, 27, 28, 29};

// Size of the whole array divided by size of one element = number of LEDs.
// This works here because ledPins is an actual array in this scope. An array
// passed into a function behaves like a pointer, so this calculation would
// not count its elements inside an ordinary function parameter.
const int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);
// For this workshop, writing const int ledCount = 8; is also fine.

// Remember which LED is selected between calls to showLed().
int currentLed = 0;

void showLed() {
  // First switch every LED off; otherwise an earlier LED might stay on.
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  // Turn on only the pin at the selected array position.
  digitalWrite(ledPins[currentLed], HIGH);
}

void setup() {
  // A digital pin must be configured as OUTPUT before driving an LED.
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  // setup() runs once, so this sketch shows one steady LED.
  showLed();
}

void loop() {
  // Nothing changes yet. To test the array, change currentLed's initial
  // value above (try 3), upload again, and predict which pin lights up.
  // In sketch 03, loop() will advance this index automatically.
}
