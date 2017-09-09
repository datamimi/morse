// HIGH and LOW are printed to screen when morse key is pushed

//const int led = 13;
const int buttonPin = 7;  // Morse key is connected to Pin 7

void setup()
{
  //pinMode(led, OUTPUT);       // LED
  pinMode(buttonPin, INPUT_PULLUP); // configure the pin connected to the Morse key as a pullup
}

void loop()
{
  if (digitalRead(buttonPin)) {
    // D7 pin is high due to pullup resistor
    digitalWrite(led, LOW);   // LED on
    delay(80);                  // Slow blink
    digitalWrite(led, HIGH);  // LED off
    delay(80);
  } else {
    // D7 pin is low due to pushbutton pressed
    digitalWrite(led, LOW);   // LED on
    delay(400);                   // Fast blink
    digitalWrite(led, HIGH);  // LED off
    delay(400);
  }
}
