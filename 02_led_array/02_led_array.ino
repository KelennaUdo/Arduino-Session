// Arduino Mega: LEDs on digital pins 22–29. Avoid pins 0 and 1 (Serial).

const int ledPins[] = {22, 23, 24, 25, 26, 27, 28, 29}; // Array: keeps related pin numbers together.

const int ledCount = sizeof(ledPins) / sizeof(ledPins[0]); // Calculate the number of elements (DO NOT DO THIS IN A CUSTOM FUNCTION)
// or
// const int ledCount = 8;

int currentLed = 0;  // Variable: remembers the selected LED.

void showLed() {
  // Function: a named block of code that performs one job.
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  digitalWrite(ledPins[currentLed], HIGH);
}

void setup() {
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  showLed();
}

void loop() {
  // Try a different value for currentLed in the setup(), then upload again.
}
