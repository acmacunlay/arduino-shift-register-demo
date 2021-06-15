#include <EEPROM.h> // library used to access the MCU's internal EEPROM

const byte latch = 5; // latch (Pin 12) of the 595 connected to D5
const byte clk = 6; // clock (Pin 11) of the 595 connected to D6
const byte data = 4; // data (Pin 14) of the 595 connected to D4
const int baudrate = 9600;

void setup() {

  // each pin is set up to send out bits
  pinMode(latch, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(clk, OUTPUT);
  
  Serial.begin(baudrate);
  returnToPreviousState();
  delay(2000); // will pause for 2000 ms to show the previously stored value

}

void loop() {

  delay(1000); // pause for 1000 ms before starting the for loop
  for (int i = 0; i < 256; i++) {
    updateRegister(i);
    delay(100); // pause for 100 ms before continuing the for loop
  }

}

// gets the value stored in the EEPROM at address 0
void returnToPreviousState() {
  byte savedState = EEPROM.read(0);
  updateRegister(savedState);
}

void updateRegister (int val) {

  Serial.println(val); // print the current value in the serial monitor (Ctrl + Shift + M)
  digitalWrite(latch, LOW); // unlocks the 595
  shiftOut(data, clk, MSBFIRST, val); // feeds the new value
  digitalWrite(latch, HIGH); // locks the 595
  EEPROM.update(0, val); // will store the new value in the EEPROM at address 0

}
