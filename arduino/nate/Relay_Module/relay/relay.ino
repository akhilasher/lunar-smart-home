int Relay = 0;
void setup() {
  pinMode(8, OUTPUT);     // Set Pin13 as output
  digitalWrite(8, HIGH);  // Set Pin13 High
  pinMode(Relay, OUTPUT); // Set Pin3 as output
}
void loop() {
  digitalWrite(Relay, HIGH); // Turn off relay
  delay(2000);
  digitalWrite(Relay, LOW); // Turn on relay
  delay(2000);
}
