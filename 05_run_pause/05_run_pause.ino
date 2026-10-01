/*
  05 — Run/pause with a debounced button and adjustable speed

  The button toggles running once per accepted press. The potentiometer
  controls the time between LED steps. Both are checked in a loop that
  never calls delay(), so the controls stay responsive.

  Arduino Mega wiring: each LED on pins 22–29 with its own resistor;
  button from pin 2 to GND; potentiometer outer legs to 5V/GND and
  middle wiper to A0. Pins 0/1 are reserved for USB Serial.

  Reading guide: setup() prepares the hardware. In loop(), read inputs,
  debounce the button, advance the LED if due, then print a status line.
*/
const int ledPins[] = {22, 23, 24, 25, 26, 27, 28, 29};
const int ledCount = 8;
const int buttonPin = 2;
const int potPin = A0;

int currentLed = 0;           // Index into ledPins: 0 through 7.
bool running = true;          // Remember whether the LED is allowed to move.
bool lastReading = HIGH;      // What the raw button pin read last loop.
bool stableButton = HIGH;     // Last button state accepted after debounce.
unsigned long buttonChangedAt = 0; // When the raw reading last changed.
unsigned long previousStep = 0;    // When the LED last moved.
unsigned long previousPrint = 0;   // When status last printed.
unsigned long interval = 500;      // Milliseconds between LED steps.

void showLed() {
  // Clear all outputs before lighting the selected position.
  for (int i = 0; i < ledCount; i++){
    digitalWrite(ledPins[i], LOW);
  } 
  digitalWrite(ledPins[currentLed], HIGH);
}

void advanceLed() {
  // Move forward one index; after the last LED, return to the first.
  currentLed++;
  if (currentLed >= ledCount) currentLed = 0;
  showLed();
}

void setup() {
  // setup() runs once. INPUT_PULLUP makes the released button HIGH;
  // a press connects pin 2 to GND and reads LOW.
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  for (int i = 0; i < ledCount; i++) pinMode(ledPins[i], OUTPUT);
  showLed();
  // Optional teaching experiment: starting previousStep at millis()
  // would wait one full interval after startup before the first move.
  // previousStep = millis(); optional
}

void loop() {
  // Take one clock reading to compare with each saved timestamp.
  unsigned long now = millis();
  bool reading = digitalRead(buttonPin);

  // The knob changes the LED step interval, not the 250 ms print rate.
  // A larger pot reading maps to a smaller interval: faster movement.
  int potValue = analogRead(potPin);
  interval = map(potValue, 0, 1023, 1000, 100);

// Button debounce: a physical switch can rapidly flicker HIGH/LOW as
// its contacts settle. We track the raw reading separately from the
// stable state the program is willing to act on.
// 1. A raw change restarts the 30 ms settling timer.
  if (reading != lastReading) buttonChangedAt = now;
  // 2. Only accept a different state after 30 ms without another change.
  //    The time subtraction also works across normal millis() rollover.
  if (now - buttonChangedAt >= 30 && reading != stableButton) {
    stableButton = reading;
    // 3. Toggle only on a stable press (LOW), not again on release.
    if (stableButton == LOW) {
      running = !running;  // true becomes false; false becomes true.
      // When resuming, restart the step timer. This avoids an immediate
      // "catch-up" move caused by time spent paused.
      if (running) previousStep = now;
    }
  }
  // Save this raw sample for comparison with the next pass through loop().
  lastReading = reading;

  // Advance only when running and the pot-selected time has elapsed.
  // The button logic above keeps executing while movement is paused.
  if (running && now - previousStep >= interval) {
    previousStep = now;
    advanceLed();
  }

  // Print slower than loop() runs so Serial Monitor remains readable.
  // The conditional expression chooses a friendly word for a bool.
  if (now - previousPrint >= 250) {
    previousPrint = now;
    Serial.print("LED = "); Serial.print(currentLed);
    Serial.print("   interval = "); Serial.print(interval);
    Serial.print(" ms   running = ");
    Serial.println(running ? "YES" : "NO");
  }
}
