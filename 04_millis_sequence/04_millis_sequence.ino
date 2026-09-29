const int ledPins[] = {22, 23, 24, 25, 26, 27, 28, 29};
const int ledCount = 8;
const int buttonPin = 2;
const int potPin = A0;

int currentLed = 0;
bool lastButtonState = HIGH;
unsigned long previousStep = 0;
unsigned long previousPrint = 0;
const unsigned long interval = 500;

void showLed() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  digitalWrite(ledPins[currentLed], HIGH);
}

void advanceLed() {
  currentLed++;
  if (currentLed >= ledCount) {
    currentLed = 0;
  }
  showLed();
}

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  showLed();
  previousStep = millis(); // optional
}

void loop() {
  unsigned long now = millis();  // millis(): time since startup, without waiting.
  bool buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    Serial.print("button = ");
    Serial.println(buttonState);  // A short press can now be seen.
    lastButtonState = buttonState;
  }

//this block instead of delay
  if (now - previousPrint >= 100) {
    // update the time
    previousPrint = now;
    // do the thing
    Serial.print("pot = ");
    Serial.println(analogRead(potPin));
  }

// this block instead of delay
  if (now - previousStep >= interval) {
    previousStep = now;
    advanceLed();
  }
}
