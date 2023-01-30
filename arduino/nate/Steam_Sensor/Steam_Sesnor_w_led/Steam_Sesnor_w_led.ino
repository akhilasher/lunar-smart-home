int led = 2;
int sensor = 0;

void setup() {
  pinMode(led, OUTPUT);
  // digitalWrite(led, LOW);
  Serial.begin(9600); // open serial port, and set baud rate at 9600bps
}
void loop() {
  int val;
  val = analogRead(sensor); // plug vapor sensor into analog port 0
  if (val >= 10) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  Serial.print("Moisture is ");
  Serial.println(val); // read analog value through serial port printed
  delay(100);
}
