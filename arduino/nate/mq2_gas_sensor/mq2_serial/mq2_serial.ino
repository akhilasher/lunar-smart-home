/// Arduino Sample Code
#include <string.h>
const int pin = 3; // analog pin here not digital
const int pause_time =
    100; // 100ms of down time before sending data again (0.1s)
int val;

void setup() {
  Serial.begin(9600); // Set serial baud rate to 9600 bps
}

void loop() {
  val = analogRead(pin); // Read Gas value from analog 0
  String blah = String(val, DEC);
  Serial.println("gas=" + blah); // Print the value to serial port
  delay(100);
}
