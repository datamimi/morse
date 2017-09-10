// DASH and DOT are printed to command line when morse key is pushed

const int led = 13; // led is connected to pin 13
const int keyPin = 7;  // morse key is connected to pin 7
const unsigned long debounceWaitTime = 10; // time delay in ms for debounce smoothing function
const unsigned long dashThresh = 200; // time threshold in ms to differentiate dots from dashes
const unsigned long letterThresh = 300; // time threshold in ms to differentiate letter gaps
const unsigned long wordThresh = 3000; // time threshold in ms to differentiate word gaps

int modelState = 0; // initialise model state to 0 or LOW
int inputSignal = 0; // initialise physical state to 0 or LOW
int inputCounter = 0; // initialise which input number we're currently on

unsigned long downTime = 0; // records the start time of state change
unsigned long upTime = 0; // records the end time of state change
unsigned long changeDuration = 0; // records the duration of state change
unsigned long pauseDuration = 0; // records the duration of the last pause

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
    pauseDuration = downTime-upTime;

    if (pauseDuration>=letterThresh and pauseDuration<wordThresh){ // if the preceding pause was long enough, evaluate the previous inputs as a single letter

      evaluateLetter();
      
    } else if (pauseDuration >= wordThresh) {

      evaluateLetter();
      newWord();
      
    }
}

void keyUp()
{
    modelState = 0; // update modelState
    upTime = millis();
    changeDuration = upTime-downTime; 
    digitalWrite(led, LOW); // switch LED off

    if (changeDuration>0 and changeDuration<dashThresh){
      Serial.println("DOT");
    } else if (changeDuration>=dashThresh) {
      Serial.println("DASH");
    }
    
}

void deBounce()
{
  delay(debounceWaitTime); // wait for a bit
  if (inputSignal==1 and modelState==0){ // if the input signal is still 1, only then update the model
       keyDown();
  }
}

void evaluateLetter()
{
  Serial.println("NEW LETTER");
}

void newWord()
{
  Serial.println("NEW WORD");
}


