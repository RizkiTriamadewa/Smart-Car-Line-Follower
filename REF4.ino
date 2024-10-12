#include <SoftwareSerial.h>
SoftwareSerial BT_Serial(5, 6); // RX, TX

#define e1 8   // Right Motor Enable Pin EA
#define m1 9  // Right Motor MA1
#define m2 10  // Right Motor MA2
#define m3 11  // Left Motor MB1
#define m4 12   // Left Motor MB2
#define e2 13   // Left Motor Enable Pin EB

#define ir1 A4 // ir sensor Right
#define ir2 A3 // ir sensor Left
#define ir3 A2
#define ir4 A1
#define ir5 A0

int bt_data; // variable to receive data from the serial port
int Speed = 255;

int mode = 0;

void setup() { // put your setup code here, to run once

  pinMode(ir1, INPUT); // declare if sensor as input  
  pinMode(ir2, INPUT); // declare ir sensor as input

  pinMode(m1, OUTPUT); // Right Motor MA1
  pinMode(m2, OUTPUT); // Right Motor MA2
  pinMode(m3, OUTPUT); // Left Motor MB1
  pinMode(m4, OUTPUT); // Left Motor MB2
  pinMode(e1, OUTPUT); // Right Motor Enable Pin EA
  pinMode(e2, OUTPUT); // Left Motor Enable Pin EB

  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);

  Serial.begin(9600); // start serial communication at 9600bps
  BT_Serial.begin(9600);
  delay(500);
}

void loop() {

  if (BT_Serial.available() > 0) {  // if some date is sent, reads it and saves in state
    bt_data = BT_Serial.read();
    if (bt_data > 20) { Speed = bt_data; }
  }

  if (bt_data == 8) { mode = 1; Speed = 255; } // Auto Line Follower Command
  else if (bt_data == 9) { mode = 0; Stop(); }    // Manual Android Application Control Command

  analogWrite(e1, Speed); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
  analogWrite(e2, Speed); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 

  if (mode == 0) {
    //===============================================================================
    //                          Key Control Command
    //===============================================================================
    if (bt_data == 1) { forword(); }  // if the bt_data is '1' the DC motor will go forward
    else if (bt_data == 2) { backword(); }  // if the bt_data is '2' the motor will Reverse
    else if (bt_data == 3) { turnLeft(); }  // if the bt_data is '3' the motor will turn left
    else if (bt_data == 4) { turnRight(); } // if the bt_data is '4' the motor will turn right
    else if (bt_data == 5) { Stop(); }     // if the bt_data '5' the motor will Stop
  }
  else {
    //===============================================================================
    //                          Line Follower Control
    //===============================================================================
    int s1 = digitalRead(ir1);  // Left Most Sensor
    int s2 = digitalRead(ir2);  // Left Sensor
    int s3 = digitalRead(ir3);  // Middle Sensor
    int s4 = digitalRead(ir4);  // Right Sensor
    int s5 = digitalRead(ir5);  // Right Most Sensor

    if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 1 && s5 == 1) {
      // Only middle sensor detects black line
      // Going forward with full speed 
      analogWrite(e1, 255);
      analogWrite(e2, 255);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    }
    else if (s1 == 1 && s2 == 0 && s3 == 1 && s4 == 1 && s5 == 1) {
      // Only left sensor detects black line
      // Going right with full speed 
      analogWrite(e1, 255);
      analogWrite(e2, 255);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
    }
    else if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1) {
      // Only left most sensor detects black line
      // Going right with full speed 
      analogWrite(e1, 255);
      analogWrite(e2, 255);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, HIGH);
    }
    else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 0 && s5 == 1) {
      // Only right sensor detects black line
      // Going left with full speed 
      analogWrite(e1, 255);
      analogWrite(e2, 255);
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    }
    else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 0) {
      // Only right most sensor detects black line
      // Going left with full speed 
      analogWrite(e1, 255);
      analogWrite(e2, 255);
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    }
    else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 0 && s5 == 1) {
      // Middle and right sensor detects black line
      // Going left with full speed 
      analogWrite(e1, 255);
      analogWrite(e2, 255);
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    }
    else if (s1 == 1 && s2 == 0 && s3 == 0 && s4 == 1 && s5 == 1) {
      // Middle and left sensor detects black line
      // Going right with full speed 
      analogWrite(e1, 255);
      analogWrite(e2, 255);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
    }
    else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 1 && s5 == 1) {
      // Middle, left, and left most sensor detects black line
      // Going right with full speed 
      analogWrite(e1, 255);
      analogWrite(e2, 255);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
    }
    else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 0 && s5 == 0) {
      // Middle, right, and right most sensor detects black line
      // Going left with full speed 
      analogWrite(e1, 255);
      analogWrite(e2, 255);
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    }
    else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0 && s5 == 0) {
      // All sensors are on a black line
      // Stop
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
    }
  }

  delay(10);
}

void forword() {  // Forward
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
}

void backword() { // Backward
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
}

void turnRight() { // Turn Right
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
}

void turnLeft() { // Turn Left
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
}

void Stop() { // Stop
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
}
