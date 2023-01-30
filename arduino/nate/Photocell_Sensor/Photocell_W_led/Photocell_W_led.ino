int sensorPin = A0;
int value = 0;
int led = 2;
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}
void loop() {
  value = analogRead(sensorPin);
  if (value < 200) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  Serial.println(value, DEC);

  delay(50);
}
