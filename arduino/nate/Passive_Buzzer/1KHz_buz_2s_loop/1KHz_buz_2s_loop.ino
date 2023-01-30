const int buz = 0;

void setup() { pinMode(buz, OUTPUT); }

void loop() {
  tone(buz, 1000);
  delay(1000);
  noTone(buz);
  delay(1000);
}
