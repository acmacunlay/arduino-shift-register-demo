// This sketch is just for giving you an idea on how to use the shift register in a real world application.

#include <EEPROM.h>.

const byte latch = 5; // latch (Pin 12) of the 595 connected to D5
const byte clk = 6; // clock (Pin 11) of the 595 connected to D6
const byte data = 4; // data (Pin 14) of the 595 connected to D4
const int baudrate = 9600;

int currentState;
int newState;

void setup() {

  pinMode(latch, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(clk, OUTPUT);
  
  currentState = getSavedState();
  updateRegister(currentState);

}

void loop() {

  // get all values from all inputs (some sensors maybe)
  int Q0 = checkQ0();
  int Q1 = checkQ1();
  int Q2 = checkQ2();
  int Q3 = checkQ3();
  int Q4 = checkQ4();
  int Q5 = checkQ5();
  int Q6 = checkQ6();
  int Q7 = checkQ7();

  // sum up all returned values from inputs
  newState = Q0 + Q1 + Q2 + Q3 + Q4 + Q5 + Q6 + Q7;

  // compare the new value to the current value
  if (newState == currentState) {
    // do nothing; just update the currentState variable
    currentState = newState;
  } else {
    // update the currentState variable and the shift register value
    currentState = newState;
    updateRegister(currentState);
    EEPROM.update(0, currentState); // store the new value in the EEPROM at address 0
  }
  
}

int getSavedState() {
  int savedState = EEPROM.read(0);
  return savedState;
}

int checkQ0() {
  bool Q0 = true;
  if (Q0) {
    return 1;
  } else {
    return 0;
  }
}

int checkQ1() {
  bool Q1 = true;
  if (Q1) {
    return 2;
  } else {
    return 0;
  }
}

int checkQ2() {
  bool Q2 = true;
  if (Q2) {
    return 4;
  } else {
    return 0;
  }
}

int checkQ3() {
  bool Q3 = true;
  if (Q3) {
    return 8;
  } else {
    return 0;
  }
}

int checkQ4() {
  bool Q4 = true;
  if (Q4) {
    return 16;
  } else {
    return 0;
  }
}

int checkQ5() {
  bool Q5 = true;
  if (Q5) {
    return 32;
  } else {
    return 0;
  }
}

int checkQ6() {
  bool Q6 = true;
  if (Q6) {
    return 64;
  } else {
    return 0;
  }
}

int checkQ7() {
  bool Q7 = true;
  if (Q7) {
    return 128;
  } else {
    return 0;
  }
}

void updateRegister (int val) {

  digitalWrite(latch, LOW); // unlocks the 595
  shiftOut(data, clk, MSBFIRST, val); // enters the new value
  digitalWrite(latch, HIGH); // locks the 595

}
