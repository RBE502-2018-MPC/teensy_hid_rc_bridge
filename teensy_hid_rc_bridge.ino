void setup() {
  // DO NOT USE SERIAL FOR DEBUGGING! SIGNIFICANTLY REDUCES PROCESSING SPEED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

// Must always transfer 64 bytes, since HID is used
byte buffer[64];
//elapsedMillis timeout
void loop() {
  int n;
  n = RawHID.recv(buffer, 0); //timeout=0, no wait

  //Received a new packet!
  if (n > 0) {
    // Quick debug output to show that it's working
    if (buffer[0] > 64) {
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }

    //Send the message back to ack
    buffer[2] = 0xDE;
    buffer[3] = 0xAD;
    buffer[4] = 0xBE;
    buffer[5] = 0xEF;
    n = RawHID.send(buffer, 100);
  }

}
