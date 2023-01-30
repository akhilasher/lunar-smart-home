int oldval = 0;

void setup() {
  Serial.begin(9600); // Set Baud Rate to 9600 bps
}

void loop() {
  int val;
  int dat;
  val = analogRead(0); // Connect LM35 on Analog 0
  dat = (500 * val) / 1024;
  ;
  if (oldval != dat) {
    Serial.print("temp="); // Display the temperature on Serial monitor
    Serial.println(dat);
    // Serial.println("C");
  }
  oldval = dat;
  delay(500);
}
