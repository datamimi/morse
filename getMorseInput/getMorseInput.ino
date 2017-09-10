// DASH and DOT are printed to command line when morse key is pushed

const int led = 13; // led is connected to pin 13
const int keyPin = 7;  // morse key is connected to pin 7

int modelState = 0; // initialise model state to 0 or LOW
int inputSignal = 0; // initialise physical state to 0 or LOW

unsigned long changeStartTime = 0; // records the start time of state change
unsigned long changeEndTime = 0; // records the end time of state change
unsigned long changeDuration = 0; // records the duration of state change

void setup()
{
  pinMode(led, OUTPUT);       // LED
  pinMode(keyPin, INPUT_PULLUP); // configure the pin connected to the morse key as a pullup
} // end of setup

void loop()
{
  inputSignal =! digitalRead(keyPin);
//  Serial.println("MODEL STATE:");
//  Serial.println(modelState);
//  delay(500);
//  Serial.println("INPUT SIGNAL:");
//  Serial.println(inputSignal);
//  delay(500);
  
  // start of IF loop
  if (inputSignal==0 and modelState==0) { // if both physical state and model state are 0, do nothing

  } else if (inputSignal==1 and modelState==0) { // if input from key has gone to 1 and model is still 0, update model

    keyDown();

  } else if (inputSignal==1 and modelState==1) { // if both physical state and model are 1, do nothing

  } else if (inputSignal==0 and modelState==1) { // if input from key has gone to 0 and model is still 1, update model

    keyUp();

  }
  
} // end of loop

void keyDown()
{
    modelState = 1; // update modelState
    changeStartTime = millis();
    digitalWrite(led, HIGH); // switch LED on
}

void keyUp()
{
    modelState = 0; // update modelState
    changeEndTime = millis();
    changeDuration = changeEndTime-changeStartTime; 
    digitalWrite(led, LOW); // switch LED off
    Serial.println(changeDuration);
}
