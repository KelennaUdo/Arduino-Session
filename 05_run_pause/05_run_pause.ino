// Arduino Mega: LEDs 22–29 (each with a resistor), button 2 to GND,
// pot ends to 5V/GND and wiper to A0. Avoid pins 0/1 (USB Serial).
const int ledPins[] = {22, 23, 24, 25, 26, 27, 28, 29};
const int ledCount = 8;
const int buttonPin = 2;
const int potPin = A0;

int currentLed = 0;
bool running = true;  // bool: stores true or false.
bool lastReading = HIGH;
bool stableButton = HIGH;
unsigned long buttonChangedAt = 0;
unsigned long previousStep = 0;
unsigned long previousPrint = 0;
unsigned long interval = 500;

void showLed() {
  for (int i = 0; i < ledCount; i++){
    digitalWrite(ledPins[i], LOW);
  } 
  digitalWrite(ledPins[currentLed], HIGH);
}

void advanceLed() {
  currentLed++;
  if (currentLed >= ledCount) currentLed = 0;
  showLed();
}

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);  // Pressed means LOW.
  for (int i = 0; i < ledCount; i++) pinMode(ledPins[i], OUTPUT);
  showLed();
  // previousStep = millis(); optional
}

void loop() {
  unsigned long now = millis();
  bool reading = digitalRead(buttonPin);
  int potValue = analogRead(potPin);
  interval = map(potValue, 0, 1023, 1000, 100);
  // map(): converts the input range into an interval in milliseconds.

// button reading algorithm. 
  if (reading != lastReading) buttonChangedAt = now;
  if (now - buttonChangedAt >= 30 && reading != stableButton) {
    stableButton = reading;  // Accept only a stable change (debounce).
    if (stableButton == LOW) {
      running = !running;  // Toggle once per press.
      if (running) previousStep = now;  // If the button press set running == TRUE, restart the LED step timer (optional).
    }
  }
  lastReading = reading;

  if (running && now - previousStep >= interval) {
    previousStep = now;
    advanceLed();
  }

  if (now - previousPrint >= 250) {
    previousPrint = now;
    Serial.print("LED = "); Serial.print(currentLed);
    Serial.print("   interval = "); Serial.print(interval);
    Serial.print(" ms   running = ");
    Serial.println(running ? "YES" : "NO");
  }
}
