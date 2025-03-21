#include <Keypad.h>
#include <Bounce2.h>
#include "HID-Project.h"

// KEYPAD BUTTONS
const int R1 = 6;
const int R2 = 7;
const int R3 = 8;
const int R4 = 9;
const int C1 = 21;
const int C2 = 20;
const int C3 = 19;
const int C4 = 18;
const byte ROWS = 4;
const byte COLS = 4;
char keys[COLS][ROWS] = {
  { '1', '5', '9', 'c' },  // FIRST COLUMN
  { '2', '6', '0', 'd' },  // SECOND COLUMN
  { '3', '7', 'a', 'e' },  // THIRD COLUMN
  { '4', '8', 'b', 'f' }   // FOURTH COLUMN
};
byte rowPins[ROWS] = { R1, R2, R3, R4 };
byte colPins[COLS] = { C1, C2, C3, C4 };
Keypad kpd = Keypad(makeKeymap(keys), colPins, rowPins, COLS, ROWS);

int lastDebounceTime = 4;
const int debounceTime = 50;

int LED_MATRIX[16] = { B10000111, B01000111, B00100111, B00010111,
                       B10001011, B01001011, B00101011, B00011011,
                       B10001101, B01001101, B00101101, B00011101,
                       B10001110, B01001110, B00101110, B00011110 };
//Shift Register

// ST_CP pin 12
const int latchPin = 10;
// SH_CP pin 11
const int clockPin = 16;
// DS pin 14;
const int dataPin = 14;

//States
const int numStates = 4;
int currentState = 0;

void clearRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(latchPin, clockPin, LSBFIRST, B00001111);
  digitalWrite(latchPin, HIGH);
}

void flashLED(int time, uint8_t LED) {
  digitalWrite(latchPin, LOW);
  delay(time);
  shiftOut(dataPin, clockPin, LSBFIRST, LED);
  digitalWrite(latchPin, HIGH);
}

void setup() {

  // Serial.begin(9600);


  // for (int i = 0; i < numStates; i++) {
  //   pinMode(States[i], OUTPUT);
  //   digitalWrite(States[i], LOW);
  // }
  // Shift Register set up
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  clearRegister();
  Keyboard.begin();

  // Serial.print("Ready");
}



void ChangeState() {
  currentState++;
  if (currentState == numStates) {
    currentState = 0;
  }
  //Serial.print("State Changed. Current State: "); Serial.println(currentState);
  flashLED(100, LED_MATRIX[3]);
  // delay(100);
  return;
}
//NUMPAD
void Layout1(char button) {
  switch (button) {
    case '1':
      flashLED(100, LED_MATRIX[0]);
      Keyboard.print('7');
      Keyboard.releaseAll();
      break;
    case '2':
      Keyboard.print('8');
      flashLED(100, LED_MATRIX[1]);
      break;
    case '3':
      flashLED(100, LED_MATRIX[2]);
      Keyboard.print('9');
      break;
    case '5':
      flashLED(100, LED_MATRIX[4]);
      Keyboard.print('4');
      break;
    case '6':
      flashLED(100, LED_MATRIX[5]);
      Keyboard.print('5');
      break;
    case '7':
      flashLED(100, LED_MATRIX[6]);
      Keyboard.print('6');
      break;
    case '8':
      flashLED(100, LED_MATRIX[7]);
      Keyboard.print('+');
      break;
    case '9':
      flashLED(100, LED_MATRIX[8]);
      Keyboard.print('1');
      break;
    case '0':
      flashLED(100, LED_MATRIX[9]);
      Keyboard.print('2');
      break;
    case 'a':
      flashLED(100, LED_MATRIX[10]);
      Keyboard.print('3');
      break;
    case 'b':
      flashLED(100, LED_MATRIX[11]);
      Keyboard.print('-');
      break;
    case 'c':
      flashLED(100, LED_MATRIX[12]);
      Keyboard.print('0');
      break;
    case 'd':
      flashLED(100, LED_MATRIX[13]);
      Keyboard.print('0');
      break;
    case 'e':
      flashLED(100, LED_MATRIX[14]);
      Keyboard.print('*');
      break;
    case 'f':
      flashLED(100, LED_MATRIX[15]);
      Keyboard.press(KEY_ENTER);
      Keyboard.releaseAll();
      break;
  };
}

// PHOTOSHOP
void Layout2(char button) {
  switch (button) {
    case '1':  //
      break;
    case '2':  //
      break;
    case '3':  // EXPORT
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('w');
      delay(10);
      Keyboard.releaseAll();
      break;
    case '4':  //
      break;
    case '5':  //
      break;
    case '6':  //
      break;
    case '7':  //
      Keyboard.print("lacsonky@gmail.com");
      Keyboard.releaseAll();
      break;
    case '8':  //
      break;
    case '9':  //
      break;
  };
}

// FREECAD
void Layout3(char button) {
  switch (button) {
    case '1':
      break;
    case '2':
      break;
    case '3':
      break;
    case '4':
      Keyboard.press(KEY_F2);
      Keyboard.releaseAll();
      break;
    case '5':
      Keyboard.print('5');
      break;
    case '6':
      Keyboard.print('6');
      break;
    case '7':
      Keyboard.press('v');
      Keyboard.press('1');
      Keyboard.releaseAll();
      break;
    case '8':
      Keyboard.press('v');
      Keyboard.press('3');
      Keyboard.releaseAll();
      break;
    case '9':
      Keyboard.press('v');
      Keyboard.press('t');
      Keyboard.releaseAll();
      break;
  };
}

void Layout4(char button) {
  switch (button) {
    case '1':
      Keyboard.print('1');
      break;
    case '2':
      Keyboard.print('2');
      break;
    case '3':
      Keyboard.print('3');
      break;
    case '4':
      Keyboard.print('4');
      break;
    case '5':
      Keyboard.print('5');
      break;
    case '6':
      Keyboard.print('6');
      break;
    case '7':

      break;
    case '8':

      break;
    case '9':

      break;
  };
}


void loop() {
  //   int i;
  //   for (i = 0; i < 16; i++)
  // {
  //   flashLED(100, LED_MATRIX[i]);
  //  }
  //check the key matrix first
  char key = kpd.getKey();
  if (key) {
    switch (key) {
      case '4':
        ChangeState();
        break;
      // case '-':
      //   Keyboard.press(KEY_RIGHT_CTRL);
      //   Keyboard.press('s');
      //   delay(10);
      //   Keyboard.releaseAll();
      //   break;
      default:
        switch (currentState) {
          case 0:
            Layout1(key);
            break;
          case 1:
            Layout2(key);
            break;
          case 2:
            Layout3(key);
            break;
          case 3:
            Layout4(key);
            break;
        }
    }
  }
}
