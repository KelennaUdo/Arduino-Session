const int buttonPin = 2;
const int potPin = A0;


void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);  // INPUT_PULLUP: released = HIGH, pressed = LOW.
}


void loop() {
  bool buttonState = digitalRead(buttonPin);  // bool: stores true or false (HIGH or LOW).
  int potValue = analogRead(potPin);         // analogRead: reads roughly 0–1023.


  Serial.print("button = ");
  Serial.print(buttonState);
  Serial.print("   pot = ");
  Serial.println(potValue);


  delay(200);  // Only to keep this first Serial test readable.
}
