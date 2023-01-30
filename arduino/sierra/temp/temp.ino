#include <DHT.h>;

// Constants
int dht22 = A0;
#define DHTTYPE DHT11    // DHT 22  (AM2302)
DHT dht(dht22, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

// Variables
int chk;
float hum;  // Stores humidity value
float temp; // Stores temperature value

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
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
