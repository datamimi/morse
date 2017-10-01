// Turns Morse key into USB keyboard

#include <Bounce.h> // include de-bounce library

const int led = 13; // led is connected to pin 13
const int keyPin = 7;  // morse key is connected to pin 7
Bounce morseKey = Bounce(keyPin, 10);  // 10 ms debounce

const unsigned long dashThresh = 150; // time threshold in ms to differentiate dots from dashes
const unsigned long letterThresh = 500; // time threshold in ms to differentiate letter gaps
const unsigned long wordThresh = 3000; // time threshold in ms to differentiate word gaps

String inputString = ""; // initialise input string

unsigned long downTime = 0; // records the start time of state change
unsigned long upTime = 0; // records the end time of state change
unsigned long timeNow = 0; // records the current time
unsigned long changeDuration = 0; // records the duration of state change
unsigned long pauseDuration = 0; // records the duration of the last pause

int pauseFlag = 0; // initilise the flag to indicate whether a pause has already been evaluated

void setup()
{
  pinMode(led, OUTPUT); // configure the pin connected to the led as an output
  pinMode(keyPin, INPUT_PULLUP); // configure the pin connected to the morse key as a pullup
} // end of setup

void loop()
{
  checkPause();
  // start of IF loop
  if (morseKey.update()){

    if (morseKey.risingEdge()) { // if input from key has gone to 1 and model is still 0, update model

      keyUp();

    } else if (morseKey.fallingEdge()) { // if input from key has gone to 0 and model is still 1, update model

      keyDown();

    }
  } // end of if update loop

} // end of loop

void keyDown()
{
    downTime = millis();
    digitalWrite(led, HIGH); // switch LED on
}

void keyUp()
{
    upTime = millis();
    changeDuration = upTime-downTime;
    digitalWrite(led, LOW); // switch LED off

    if (changeDuration>0 and changeDuration<dashThresh){
      inputString = inputString + ".";
      Serial.println("DOT");

    } else if (changeDuration>=dashThresh) {
      inputString = inputString + "-";
      Serial.println("DASH");

    }

    pauseFlag = 1;

}

void checkPause()
{
    timeNow = millis();
    pauseDuration = timeNow-upTime;

    if (pauseDuration>=letterThresh and pauseDuration<wordThresh and pauseFlag){ // if the preceding pause was long enough AND a pause hasn't just been evaluated, evaluate the previous inputs as a single letter

      evaluateLetter();
      pauseFlag = 0;

    } else if (pauseDuration >= wordThresh and pauseFlag) {

      evaluateLetter();
      newWord();
      pauseFlag = 0;

    }
}

void press(var key){
  Keyboard.press(key);
  Keyboard.release(key);
}

void newWord()
{
  press(KEY_SPACE);
}

void evaluateLetter()
{

  if (inputString==".-") {
      press(KEY_A);
  } else if (inputString=="-..."){
      press(KEY_B);
  } else if (inputString == "-.-."){
      press(KEY_C);
  } else if (inputString=="-.."){
      press(KEY_D);
  } else if (inputString=="."){
      press(KEY_E);
  } else if (inputString=="..-."){
      press(KEY_F);
  } else if (inputString=="--."){
      press(KEY_G);
  } else if (inputString=="...."){
      press(KEY_H);
  } else if (inputString==".."){
      press(KEY_I);
  } else if (inputString==".---"){
      press(KEY_J);
  } else if (inputString=="-.-"){
      press(KEY_K);
  } else if (inputString==".-.."){
      press(KEY_L);
  } else if (inputString=="--"){
      press(KEY_M);
  } else if (inputString=="-."){
      press(KEY_N);
  } else if (inputString=="---"){
      press(KEY_O);
  } else if (inputString==".--."){
      press(KEY_P);
  } else if (inputString=="--.-"){
      press(KEY_Q);
  } else if (inputString==".-."){
      press(KEY_R);
  } else if (inputString=="..."){
      press(KEY_S);
  } else if (inputString=="-"){
      press(KEY_T);
  } else if (inputString=="..-"){
      press(KEY_U);
  } else if (inputString=="...-"){
      press(KEY_V);
  } else if (inputString==".--"){
      press(KEY_W);
  } else if (inputString=="-..-"){
      press(KEY_X);
  } else if (inputString=="-.--"){
      press(KEY_Y);
  } else if (inputString=="--.."){
      press(KEY_Z);
  } else if (inputString==".----"){
      press(KEY_1);
  } else if (inputString=="..---"){
      press(KEY_2);
  } else if (inputString=="...--"){
      press(KEY_3);
  } else if (inputString=="....-"){
      press(KEY_4);
  } else if (inputString=="....."){
      press(KEY_5);
  } else if (inputString=="-...."){
      press(KEY_6);
  } else if (inputString=="--..."){
      press(KEY_7);
  } else if (inputString=="---.."){
      press(KEY_8);
  } else if (inputString=="----."){
      press(KEY_9);
  } else if (inputString=="-----"){
      press(KEY_0);
  } else {
      press(KEY_MINUS);
  }

  inputString = ""; // re-initialise inputString ready for new letter

}
