const int ledPins[] = {22, 23, 24, 25, 26, 27, 28, 29};
const int ledCount = 8;
const int buttonPin = 2;
const int potPin = A0;

int currentLed = 0;

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
  // set the button pin
  pinMode(buttonPin, INPUT_PULLUP);
  // set the led pins
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  // show the inital currentLed
  showLed();
}

void loop() {
  delay(500);  // Nothing below runs during this wait.

  bool buttonState = digitalRead(buttonPin);
  int potValue = analogRead(potPin);
  Serial.print("button = ");
  Serial.print(buttonState);
  Serial.print("   pot = ");
  Serial.println(potValue);

  advanceLed();
}
