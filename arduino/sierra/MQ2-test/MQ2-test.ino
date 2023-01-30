// Arduino UNO Board MQ2 Gas Sensor
#include <string.h>
const int pin = 3; // analog pin here not digital
const int pause_time =
    1000; // 100ms of down time before sending data again (0.1s)
const String roomnum = "00"; // this is the sensor number ig?
int val;                     // holds the gas value

void setup() {
  Serial.begin(9600); // Set serial baud rate to 9600 bps
}

void loop() {
  val = analogRead(pin);           // Read Gas value from analog 0
  String blah = String(val, DEC);  // converts the value to a string
  Serial.println("RM=" + roomnum); // Print the room nmbr to serial port
  Serial.println("gas=" + blah);   // Print the value to serial port
  delay(pause_time);               // wait for a bit
}
