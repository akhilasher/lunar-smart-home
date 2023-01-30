#include "DHT.h"
#include "string.h"

#define gas_sensor A0
#define dht22_pin A1

#define toggle_auto_lights 2
#define passive_buzzer 3
#define toggle_lights 4
#define red_light 5
#define yel_light 6
#define white_light                                                            \
  9 // this is the basic light controlled by either the time or based off the 2
    // switches
#define alarm_test_btn 10

#define baudrate 9600

String lights_on_msg = "kitchen_light_on";
String lights_off_msg = "kitchen_light_off";

bool rLight = false;
bool yLight = false;
bool pBuzzer = false;
bool turnon_light = false;
int prev_gas_level = -12;
int gas_level = 0; // ppm?

int heat_threshold = 40; // celsius
int gas_threshold = 250; // ppm?

bool lightsShouldBeOn = false; // dictates if the lights have been set to on by
                               // the dashboard/computer
unsigned long alarmLBlMillis = millis();
unsigned long alarmLBuMillis = millis();
unsigned long lastPost = millis();
unsigned long alarmTestMillis = millis() - 10001;
bool shouldDoAlarms = false;
bool prevLights = false;

DHT dht22(dht22_pin, DHT22);
void setup() {
  Serial.begin(baudrate);
  pinMode(passive_buzzer, OUTPUT);
  pinMode(toggle_lights, INPUT);
  pinMode(toggle_auto_lights, INPUT);
  dht22.begin();
}

void undoAlarms() {
  digitalWrite(red_light, LOW);
  digitalWrite(passive_buzzer, LOW);
  rLight = false;
  pBuzzer = false;
}

void doAlarms() {
  if ((millis() - alarmLBlMillis) > 500) {
    rLight = !rLight;
    digitalWrite(red_light, rLight);
    alarmLBlMillis = millis();
    // Serial.print(alarmLBlMillis);
    // Serial.print("; ");
    // Serial.print(millis());
    // Serial.print("; ");
    // Serial.println(millis()-alarmLBlMillis);
  }
  if ((millis() - alarmLBuMillis) > 1500) {
    pBuzzer = !pBuzzer;
    digitalWrite(passive_buzzer, pBuzzer);
    alarmLBuMillis = millis();
  }
}

void loop() {

  prev_gas_level = gas_level;
  gas_level = analogRead(gas_sensor);
  bool gSDA = false;
  bool hSDA = false;
  if (gas_level >= gas_threshold) {
    gSDA = true;
  } else {
    gSDA = false;
  }
  if (dht22.readTemperature() > heat_threshold) {
    hSDA = true;
  } else {
    hSDA = false;
  }
  shouldDoAlarms = (hSDA == true) || (gSDA == true);
  if (!digitalRead(alarm_test_btn)) {
    alarmTestMillis = millis();
  }

  if (millis() - alarmTestMillis < 10001) {
    shouldDoAlarms = true;
  }

  if (Serial.available() > 0) {
    String message = Serial.readStringUntil("\n");
    Serial.print("'");
    Serial.print(message);
    Serial.print("'");
    Serial.println();
    if (message == lights_on_msg || message == lights_on_msg + "\n") {
      lightsShouldBeOn = true;
    } else if (message == lights_off_msg || message == lights_off_msg + "\n") {
      lightsShouldBeOn = false;
    }
  }

  if (digitalRead(toggle_auto_lights)) {
    if (digitalRead(toggle_lights)) {
      turnon_light = true;
    } else {
      turnon_light = false;
    }
  } else {
    turnon_light = lightsShouldBeOn;
  }
  if (shouldDoAlarms) {
    doAlarms();
  } else {
    undoAlarms();
  }

  if (turnon_light) {
    digitalWrite(white_light, HIGH);
  } else {
    digitalWrite(white_light, LOW);
  }

  if (millis() - lastPost > 20000000000) {
    lastPost = millis();
    Serial.print("kitchen_gas_level=");
    Serial.print(gas_level);
    Serial.print(",kitchen_temp=");
    Serial.print(floor(dht22.readTemperature()));
    Serial.print(",kitchen_hum=");
    Serial.print(floor(dht22.readHumidity()));
    Serial.print(",kitchen_light=");
    if (turnon_light) {
      Serial.println("true");
    } else {
      Serial.println("false");
    }
  }
}
