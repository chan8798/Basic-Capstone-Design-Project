#include <Servo.h>        // Include Servo Library
#include <NewPing.h>      // Include Newping Library

// L298N Control Pins
const int LeftMotorForward = 4;
const int LeftMotorBackward = 5;
const int RightMotorForward = 6;
const int RightMotorBackward = 7;
const int R=11;
const int Y=12;
const int G=13;
const int buz=8;

#define TRIGGER_PIN  A1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A2  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 250 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 250cm.

Servo servo_motor;  // Servo's name
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

boolean goesForward = false;
int distance = 100;

void setup()
{
  // Set L298N Control Pins as Output
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(buz,OUTPUT);
  
  servo_motor.attach(9);   // Attachs the servo on pin 9 to servo object.
  servo_motor.write(90);   // Set at 115 degrees. 
  delay(2000);              // Wait for 2s.
  distance = readPing();    // Get Ping Distance.
  delay(100);               // Wait for 100ms.
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop()
{  
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  

  if (distance <= 40)
  {
    digitalWrite(buz,HIGH);
    delay(300); 
    digitalWrite(buz,LOW);
    digitalWrite(R,HIGH);
    digitalWrite(Y,HIGH);
    digitalWrite(G,HIGH);
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);
    


    if (distanceRight >= distanceLeft)
    {
      
      turnRight();
      delay(800);
      moveStop();
    }
    else
    {
      
      turnLeft();
      
      delay(800);
      moveStop();
    }
  
  }
  else
  {
    digitalWrite(buz,LOW);
    moveForward();
   
  }

  distance = readPing();
}

int lookRight()     // Look Right Function for Servo Motor
{  
  servo_motor.write(10);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft()      // Look Left Function for Servo Motor 
{
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int readPing()      // Read Ping Function for Ultrasonic Sensor.
{
  delay(100);                 // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int cm = sonar.ping_cm();   //Send ping, get ping distance in centimeters (cm).
  if (cm==0)
  {
    cm=250;
  }
  return cm;
}

void moveStop()       // Move Stop Function for Motor Driver.
{
  digitalWrite(R,HIGH);
  digitalWrite(Y,LOW);
  digitalWrite(G,LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward()    // Move Forward Function for Motor Driver.
{
    digitalWrite(R,LOW);
    digitalWrite(Y,LOW);
    digitalWrite(G,HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
}

void moveBackward()   // Move Backward Function for Motor Driver.
{
  digitalWrite(R,LOW);
  digitalWrite(Y,HIGH);
  digitalWrite(G,LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
}

void turnRight()      // Turn Right Function for Motor Driver.
{
  digitalWrite(R,LOW);
  digitalWrite(Y,HIGH);
  digitalWrite(G,HIGH);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
}

void turnLeft()       // Turn Left Function for Motor Driver.
{
  digitalWrite(R,LOW);
  digitalWrite(Y,HIGH);
  digitalWrite(G,HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
}
