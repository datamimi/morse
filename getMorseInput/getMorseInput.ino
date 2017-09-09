// DASH and DOT are printed to command line when morse key is pushed

const int led = 13; // led is connected to pin 13
const int keyPin = 7;  // morse key is connected to pin 7
void setup()
{
  pinMode(led, OUTPUT);       // LED
  pinMode(keyPin, INPUT_PULLUP); // configure the pin connected to the morse key as a pullup
} // end of setup

void loop()
{
  // start of IF loop
  if (digitalRead(keyPin)) { // if input is HIGH

    Serial.println ("HIGH");
    digitalWrite(led, LOW);   // LED on
    
  } else if (!digitalRead(keyPin)) { // if input is LOW
      
      Serial.println ("LOW");
      digitalWrite(led, HIGH);   // LED off
    
  } // end of IF loop
  
} // end of loop
