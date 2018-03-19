#include <stdint.h>
#include <SPI.h>

void writeRCVals(uint8_t steering, uint8_t power);

#define CS_STEERING 9
#define CS_POWER 10

void setup() {
  // DO NOT USE SERIAL FOR DEBUGGING! SIGNIFICANTLY REDUCES PROCESSING SPEED
  //Setup SPI and the chip select pins
  pinMode(CS_STEERING, OUTPUT);
  digitalWrite(CS_STEERING, HIGH);
  pinMode(CS_POWER, OUTPUT);
  digitalWrite(CS_POWER, HIGH);
  SPI.setSCK(14);
  SPI.begin();

  //Setup the LED to be used for debugging
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

// Must always transfer 64 bytes, since HID is used
byte buffer[64];
uint8_t toggle = 0;

//elapsedMillis timeout
void loop() {
  int n;
  n = RawHID.recv(buffer, 0); //timeout=0, no wait

  //Received a new packet!
  if (n > 0) {
    writeRCVals(buffer[0], buffer[1]);
    //Toggle the LED state to show that a packet was received
    digitalWrite(LED_BUILTIN, toggle);
    toggle ^= 1;
  }
}

void writeRCVals(uint8_t steering, uint8_t power) {
  digitalWrite(CS_STEERING, LOW);
  SPI.transfer(0);
  SPI.transfer(steering);
  digitalWrite(CS_STEERING, HIGH);
  digitalWrite(CS_POWER, LOW);
  SPI.transfer(0);
  SPI.transfer(power);
  digitalWrite(CS_POWER, HIGH);
}
