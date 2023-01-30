#include <DHT.h>;
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
volatile int value;
LiquidCrystal_I2C
    mylcd(0x27, 16,
          2); // set the LCD address to 0x27 for a16 chars and 2 line display

// Constants
int dht22 = A0;
#define DHTTYPE DHT11    // DHT 22  (AM2302)
DHT dht(dht22, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

// Variables
int chk;
float hum; // Stores humidity value
float greenhouse_temp;
int greenhouse_tempF; // Stores temperature value

void setup() {
  Serial.begin(9600);
  value = 0;
  pinMode(A2, INPUT); // Soil sensor is at A2, the mode is input
  dht.begin();
  mylcd.init();
  mylcd.backlight();  // Light up the backlight
  mylcd.clear();      // Clear the screen
  Serial.begin(9600); // Set the serial port baud rate to 9600
}

void loop() {
  // Read data and store it to variables hum and temp
  delay(500); // Delay 0.5S
  value = analogRead(A2);
  hum = dht.readHumidity();
  greenhouse_temp = dht.readTemperature();
  greenhouse_tempF = greenhouse_temp * 1.8 + 32;
  // Print temp and humidity values to serial monitor
  Serial.print("greenhouse_hum=");
  Serial.print(hum);
  Serial.print(",greenhouse_temp=");
  Serial.print(greenhouse_temp);
  Serial.print(",greenhouse_soil_hum=");
  Serial.print(value);
  Serial.print("\n");
  delay(2000); // Delay 2 sec.

  mylcd.clear(); // clear screen
  mylcd.setCursor(0, 0);
  mylcd.print("temp:"); //
  mylcd.setCursor(6, 0);
  mylcd.print(greenhouse_tempF);
  mylcd.setCursor(8, 0);
  mylcd.print("F");
  mylcd.setCursor(0, 1);
  mylcd.print("soil hum:");
  mylcd.setCursor(10, 1);
  mylcd.print(value); // LCD screen print dry soil
  delay(300);         // Delay 0.3S
}
