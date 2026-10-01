/*
  01 — Read two inputs and watch them in Serial Monitor

  Goal: connect a button and a potentiometer, then see what the Arduino
  actually reads. The numbers printed here become our debugging evidence
  in later sketches. Open Serial Monitor at 9600 baud after uploading.

  Wiring on an Arduino Mega:
    Button: one side to pin 2, the other to GND.
    Potentiometer: outer legs to 5V and GND; middle leg (wiper) to A0.
  If turning the knob works backward, swap the two outer connections.
*/
const int buttonPin = 2;  // A digital input: just HIGH or LOW.
const int potPin = A0;     // An analog input: a range of readings.


void setup() {
  // setup() runs once when the board starts or resets.
  Serial.begin(9600);
  // The internal pull-up gives the unpressed pin a known HIGH state.
  // Pressing connects it to GND, so a press reads LOW (printed as 0).
  pinMode(buttonPin, INPUT_PULLUP);
}


void loop() {
  // loop() repeats. Take a new snapshot of both inputs each pass.
  // bool stores one of two states: HIGH/true or LOW/false.
  bool buttonState = digitalRead(buttonPin);
  // A 10-bit analog reading on the Mega is approximately 0 to 1023.
  int potValue = analogRead(potPin);


  // print() stays on the same line; println() finishes the line.
  // Labels make it easier to tell which number belongs to which input.
  Serial.print("button = ");
  Serial.print(buttonState);
  Serial.print("   pot = ");
  Serial.println(potValue);


  // Slow the messages so they are readable. Later we will see why delay()
  // is a poor choice when the Arduino must react quickly to a button.
  delay(200);
}
