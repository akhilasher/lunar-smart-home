int INA = 9;
int INB = 10;
void setup() {
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
}
void loop() {
  analogWrite(INA, 255);
  digitalWrite(INB, LOW);
  delay(5000);
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);
  delay(200);
  digitalWrite(INA, LOW);
  analogWrite(INB, 255);
  delay(5000);
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);
  delay(200);
}
