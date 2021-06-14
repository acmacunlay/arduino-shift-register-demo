#include <EEPROM.h>

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
  delay(2000);

}

void loop() {

  delay(1000);
  for (int i = 0; i < 256; i++) {
    updateRegister(i);
    delay(100);
  }

}

void returnToPreviousState() {
  byte savedState = EEPROM.read(0);
  updateRegister(savedState);
}

void updateRegister (int val) {

  Serial.println(val);
  digitalWrite(latch, LOW); // unlocks the 595
  shiftOut(data, clk, MSBFIRST, val); // feeds the new value
  digitalWrite(latch, HIGH); // locks the 595
  EEPROM.update(0, val);

}
