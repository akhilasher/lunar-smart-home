/*
Keyestudio smart home Kit for Arduino
Project 7
Sevro
http://www.keyestudio.com
*/
#include <Servo.h> // Servo function library
Servo myservo_9;
Servo myservo_10;
int pos = 0;    // Start angle of servo
int inpin = 4;  // Define the button in D4
int inpin2 = 5; // Define the button in D4
int dir = -1;
int dir2 = -1;
int val;
void setup() {
  pinMode(inpin, INPUT);
  myservo_9.attach(9); // Define the position of the servo on D9

  // first servo (outdoor)

  pinMode(inpin2, INPUT);
  myservo_10.attach(10); // Define the position of the servo on D10
}
// second servo (indoor)
void loop() {
  dir *= -1;
  val =
      digitalRead(inpin); // Read the digital 4 level value and assign it to val
  if ((val == LOW) &&
      (dir >
       0)) { // for(pos = 0; pos < 180; pos += 1)// angle from 0 to 180 degrees
    myservo_9.write(50);
  }
  if ((val == LOW) &&
      (dir <
       0)) { // for(pos = 0; pos < 180; pos -= 1)// angle from 0 to 180 degrees
    myservo_9.write(-50);
  }

  // first servo

  if (dir < 0) {
    dir2 *= -1;
    val = digitalRead(
        inpin2); // Read the digital 4 level value and assign it to val
    if ((val == LOW) && (dir2 > 0)) { // for(pos = 0; pos < 180; pos += 1)//
                                      // angle from 0 to 180 degrees
      myservo_10.write(50);
    }
    if ((val == LOW) && (dir2 < 0)) { // for(pos = 0; pos < 180; pos -= 1)//
                                      // angle from 0 to 180 degrees
      myservo_10.write(-50);
    }
  }
}
//
