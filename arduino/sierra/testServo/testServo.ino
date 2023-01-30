bool prevState = false;
bool functionState = false;
int buttonPin = 2;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  bool currentState = digitalRead(buttonPin) == LOW;
  bool stateChanged = currentState != prevState;

  if (stateChanged) {
    if (currentState) {
      Serial.println("do stuff");
      // do stuff (your code here)
    } else {
      Serial.println("no do stuff");
      // "undo" stuff (basically if you wanna do something when it should be
      // "not running")
    }
  }

  if (currentState == true) {
    prevState = true;
  } else {
    prevState = false;
  }
}
