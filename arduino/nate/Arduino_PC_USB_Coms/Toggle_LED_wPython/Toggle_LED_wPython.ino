int LED = 12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    switch (Serial.read()) {
    case '0':
      digitalWrite(LED, LOW);
      Serial.print("LOW\n");
      break;
    case '1':
      digitalWrite(LED, HIGH);
      Serial.print("HIGH\n");
      break;
    default:
      break;
    }
  }
}
