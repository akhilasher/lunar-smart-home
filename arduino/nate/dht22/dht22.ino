/* How to use the DHT-22 sensor with Arduino uno
   Temperature and humidity sensor
   More info: http://www.ardumotive.com/how-to-use-dht-22-sensor-en.html
   Dev: Michalis Vasilakis // Date: 1/7/2015 // www.ardumotive.com */

// Libraries
#include <DHT.h>;

// Constants
const int FAN_PIN_A = 3;    // fan diggy pin
const int FAN_PIN_B = 4;    // fan diggy pin
const int DHT_PIN = 9;      // what pin we're connected to
const int DHT_TYPE = DHT22; // DHT 22  (AM2302)
DHT dht(DHT_PIN, DHT_TYPE); //// Initialize DHT sensor for normal 16mhz Arduino

// Variables
float hum;  // Stores humidity value
float temp; // Stores temperature value

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(FAN_PIN_A, OUTPUT);
  pinMode(FAN_PIN_B, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil("\n");
    if (command == "fan on\n") {
      analogWrite(FAN_PIN_A, 255);
      Serial.println("fan=true");
    } else if (command == "fan off\n") {
      digitalWrite(FAN_PIN_A, LOW);
      Serial.println("fan=false");
    }
  }

  // Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  // Print temp and humidity values to serial monitor
  Serial.print("hum=");
  Serial.print(hum);
  Serial.print(",temp=");
  Serial.print(temp);
  Serial.print("\n");
  delay(2000); // Delay 2 sec.
}
