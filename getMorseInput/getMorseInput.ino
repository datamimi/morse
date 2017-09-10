// DASH and DOT are printed to command line when morse key is pushed

const int led = 13; // led is connected to pin 13
const int keyPin = 7;  // morse key is connected to pin 7
const unsigned long debounceWaitTime = 5; // time delay in ms for debounce smoothing function
const unsigned long newLetterWaitTime = 500; 

int modelState = 0; // initialise model state to 0 or LOW
int inputSignal = 0; // initialise physical state to 0 or LOW
int inputList[5]; // initialise a list to hold dots and dashes for one letter; the max size of one letter is 5 units
int inputCounter = 0; // initialise which input number we're currently on

unsigned long downTime = 0; // records the start time of state change
unsigned long upTime = 0; // records the end time of state change
unsigned long changeDuration = 0; // records the duration of state change

void setup()
{
  pinMode(led, OUTPUT); // configure the pin connected to the led as an output
  pinMode(keyPin, INPUT_PULLUP); // configure the pin connected to the morse key as a pullup
} // end of setup

void loop()
{
  inputSignal =! digitalRead(keyPin);
  
  // start of IF loop
  if (inputSignal==0 and modelState==0) { // if both physical state and model state are 0, do nothing

  } else if (inputSignal==1 and modelState==0) { // if input from key has gone to 1 and model is still 0, update model

    deBounce();

  } else if (inputSignal==1 and modelState==1) { // if both physical state and model are 1, do nothing

  } else if (inputSignal==0 and modelState==1) { // if input from key has gone to 0 and model is still 1, update model

    keyUp();

  }
  
} // end of loop

void keyDown()
{
    modelState = 1; // update modelState
    downTime = millis();
    digitalWrite(led, HIGH); // switch LED on

    if (downTime-upTime>newLetterWaitTime){ // evaluate the stored inputs as a whole letter
      Serial.println(inputList);
    }
    
}

void keyUp()
{
    modelState = 0; // update modelState
    upTime = millis();
    changeDuration = upTime-downTime; 
    digitalWrite(led, LOW); // switch LED off

    if (changeDuration>0 and changeDuration<100){
      Serial.println("DOT");
      inputList[inputCounter]=1;
      inputCounter++;
    } else if (changeDuration>=100) {
      Serial.println("DASH");
      inputList[inputCounter]=2;
      inputCounter++;
    }
    
}

void deBounce()
{
  delay(debounceWaitTime); // wait for a bit
  if (inputSignal==1 and modelState==0){ // if the input signal is still 1, only then update the model
       keyDown();
  }
}

