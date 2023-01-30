const String not_implemented_error = "0x42069";
const int dp_fan = 3; // fan diggy pin
const int dp_fan2 = 2;
const int ap_lm35 = 0; // lm35 (temp sense) analog pin

int old_temp_val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(dp_fan, OUTPUT);
  pinMode(dp_fan2, OUTPUT);
  digitalWrite(dp_fan, LOW);
  digitalWrite(dp_fan2, LOW);
}

void loop() {
  // digitalWrite(dp_fan, LOW);

  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil("\n");
    if (command == "fan on\n") {
      analogWrite(dp_fan, 255);
      Serial.println("fan=true");
    } else if (command == "fan off\n") {
      digitalWrite(dp_fan, LOW);
      Serial.println("fan=false");
    } else {
      Serial.println(not_implemented_error);
    }
  }

  int val, dat;
  val = analogRead(ap_lm35); // Connect LM35 on Analog 0
  dat = (500 * val) / 1024;
  if (old_temp_val != dat) {
    Serial.print("temp="); // Display the temperature on Serial monitor
    Serial.println(dat);
  }
  old_temp_val = dat;
}
