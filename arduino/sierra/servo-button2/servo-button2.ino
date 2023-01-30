int inpin = 2;
int inpin2 = 3;

#include <Servo.h> // Servo function library

Servo myservo_9;
Servo myservo_10;
int pos = 0; // Start angle of servo
int dir = -1;
int dir2 = -1;
int val;

void setup() {
  pinMode(inpin, INPUT);
  myservo_9.attach(9); // Define the position of the servo on D9
  pinMode(inpin2, INPUT);
  myservo_10.attach(10);
  Serial.begin(9600);
}

void loop() {
  bool currentState = digitalRead(inpin) == LOW;

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil("\n");
    if (command == "open_inside_airlock\n") {
      if (dir2 == -1) {
        myservo_10.write(-180);
        dir2 = 1;
        Serial.println("airlock_in=true");
        delay(500);
      }
    } else if (command == "close_inside_airlock\n") {
      if (dir2 == 1) {
        myservo_10.write(180);
        dir2 = -1;
        Serial.println("airlock_in=false");
        delay(500);
      }
    } else {
      Serial.println("0x42069");
    }
  }

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil("\n");
    if (command == "open_outside_airlock\n") {
      if (dir == -1) {
        myservo_9.write(-180);
        dir = 1;
        Serial.println("airlock_outside=true");
        delay(500);
      }
    } else if (command == "close_outside_airlock\n") {
      if (dir == 1) {
        myservo_9.write(180);
        dir = -1;
        Serial.println("airlock_outside=false");
        delay(500);
      }
    } else {
      Serial.println("0x42069");
    }
  }

  if ((currentState) && (dir == 1)) {
    myservo_9.write(180);
    dir = -1;
    Serial.println("airlock_out=false");
    delay(500);
  } else if ((currentState) && (dir == -1)) {
    if (dir == -1) {
      myservo_9.write(-180);
      dir = 1;
      Serial.println("airlock_out=true");
      delay(500);
    }
  }

  if (dir == -1) {
    bool currentState2 = digitalRead(inpin2) == LOW;
    if ((currentState2) && (dir2 == 1)) {
      myservo_10.write(180);
      dir2 = -1;
      Serial.println("airlock_in=false");
      delay(500);
    } else if ((currentState2) && (dir2 == -1)) {
      myservo_10.write(-180);
      dir2 = 1;
      Serial.println("airlock_in=true");
      delay(500);
    }
  }
}

// myservo_10 is inside airlock
// myservo_9 is outside airlock
// if dir2 = -1, indoor airlock is closed
// if dir2 = 1, indoor airlock is open
// if dir = -1, outdoor airlock is open
// if dir = 1, outdoor airlock is closed
