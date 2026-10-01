/*
  04 — Three jobs share one fast loop

  Sketch 03 waited inside delay(500), so a quick button press could be
  missed. Here loop() keeps running. Each timed job asks, "Has enough
  time passed since I last did this job?" The button is checked on every
  pass; pot printing and LED movement each have their own timer.
*/
const int ledPins[] = {22, 23, 24, 25, 26, 27, 28, 29};
const int ledCount = 8;
const int buttonPin = 2;
const int potPin = A0;

int currentLed = 0;
// Keep the last sampled button state so we print only when it changes.
bool lastButtonState = HIGH;
// millis() and these saved timestamps use unsigned long on Arduino.
// previousStep is for the LEDs; previousPrint is for Serial output.
unsigned long previousStep = 0;
unsigned long previousPrint = 0;
// The LED moves every 500 milliseconds; the pot prints every 100 ms.
const unsigned long interval = 500;

void showLed() {
  // Make only the selected LED visible.
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  digitalWrite(ledPins[currentLed], HIGH);
}

void advanceLed() {
  // Go forward, then wrap from the last index back to zero.
  currentLed++;
  if (currentLed >= ledCount) {
    currentLed = 0;
  }
  showLed();
}

void setup() {
  // Initialize the hardware once at startup.
  Serial.begin(9600);
  // A released button is HIGH; pressing grounds the pin and reads LOW.
  pinMode(buttonPin, INPUT_PULLUP);
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  showLed();
  // Start the 500 ms LED countdown now. If this line were removed,
  // previousStep would be zero and timing would start from power-up.
  previousStep = millis(); // optional
}

void loop() {
  // Read the clock once for this pass. millis() returns time since startup;
  // asking for the time does not pause the program.
  unsigned long now = millis();
  bool buttonState = digitalRead(buttonPin);

  // Because loop() no longer waits 500 ms, a brief press is more likely
  // to be sampled. This detects changes, including release, but does not
  // yet filter electrical/mechanical button bounce (see sketch 05).
  if (buttonState != lastButtonState) {
    Serial.print("button = ");
    Serial.println(buttonState);  // A short press can now be seen.
    lastButtonState = buttonState;
  }

// Give Serial printing its own 100 ms schedule.
  if (now - previousPrint >= 100) {
    // Save when we actually printed, ready for the next interval.
    previousPrint = now;
    Serial.print("pot = ");
    Serial.println(analogRead(potPin));
  }

// The LED has a separate 500 ms schedule.
  if (now - previousStep >= interval) {
    // Subtracting unsigned timestamps handles normal millis() rollover.
    // Saving now means the next step is measured from this step.
    previousStep = now;
    advanceLed();
  }
  // Neither timed block waits. After these checks, loop() starts again.
}
