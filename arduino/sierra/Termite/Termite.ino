#include <DHT.h>
#include <DHT_U.h>

#include <Adafruit_Sensor.h>

#include <DHT.h>
#include <DHT_U.h>

int analogPin = A0; // Input from photoresistor connected to A0
int buzzerPin = 4;  // Positive buzzer pin connected to pin 4

long max_frequency = 2500; // Max frequency for the buzzer

long frequency; // The frequency to buzz the buzzer
int readVal;    // The input voltage read from photoresistor

void setup() {
  pinMode(buzzerPin, OUTPUT); // set a pin for buzzer output
}

void loop() {
  readVal = analogRead(analogPin); // Reads 0-1023
  frequency = (readVal * max_frequency) / 1023;
  buzz(buzzerPin, frequency, 10);
}

void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000 / frequency / 2;
  long numCycles = frequency * length / 1000;

  for (long i = 0; i < numCycles; i++) {
    digitalWrite(targetPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(targetPin, LOW);
    delayMicroseconds(delayValue);
  }
}
