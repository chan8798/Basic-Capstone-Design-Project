#include <Servo.h>
#define trigPin  A0  
#define echoPin  A1  
#define MotorA_IN1  3    
#define MotorA_IN2  4  

#define MotorB_IN3  5  
#define MotorB_IN4  6   

#define MotorA_PWM  9   
#define MotorB_PWM  10   

//play thing of Octaf
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

// buzzerPin set Pin and (ledPin1,ledPin2) set
const int buzzerPin = 8; // Digital Pin 8
const int ledPin1 = 12;  // Digital Pin 12
const int ledPin2 = 13;  // Digital Pin 13 Built In Led can Change it if you want

int counter=0;

Servo servo;

void setup()
  {
    Serial.begin(9600);
    servo.attach(11);
    servo.write(90);
  	pinMode(MotorA_IN1, OUTPUT);     
  	pinMode(MotorA_IN2, OUTPUT);    
  
  	pinMode(MotorB_IN3, OUTPUT);      
  	pinMode(MotorB_IN4, OUTPUT);    
  	
  	pinMode(MotorA_PWM, OUTPUT);       // Declare "MotorA_PWM" as "Output Pin".
  	pinMode(MotorB_PWM, OUTPUT);       // Declare "MotorB_PWM" as "Output Pin". 
  
    pinMode(trigPin, OUTPUT);          // Declare "trigPin" as "Output Pin". 
    pinMode(echoPin, INPUT);           // Declare "echoPin" as "Input Pin". 

    pinMode(buzzerPin, OUTPUT); // Digital Pin 8
    pinMode(ledPin1, OUTPUT);  // Digital Pin 12
    pinMode(ledPin2, OUTPUT); // Digital Pin 13 Built In Led can Change it if you want

  }



float search(void)
  {
    float duration = 0.00;                // Float type variable declaration 
    float CM = 0.00;
      
      
      digitalWrite(trigPin, LOW);        // Trig_pin output as OV (Logic Low-Level) 
      delayMicroseconds(2);              // Delay for 2 us
    
      //Send 10us High Pulse to Ultra-Sonic Sonar Sensor "trigPin" 
      digitalWrite(trigPin, HIGH);       // Trig_pin output as 5V (Logic High-Level)
      delayMicroseconds(10);             // Delay for 10 us 
    
      digitalWrite(trigPin, LOW);        // Trig_pin output as OV (Logic Low-Level)
  
    
    duration = pulseIn(echoPin, HIGH); // Start counting time, upto again "echoPin" back to Logical "High-Level" and puting the "time" into a variable called "duration" 
   
    CM = (duration / 58.82); //Convert distance into CM. 
    
   return CM;
  }
void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(buzzerPin, note, duration);

  //Play different LED depending on value of 'counter'
  if(counter % 2 == 0)
  {
    digitalWrite(ledPin1, HIGH);
    delay(duration);
    digitalWrite(ledPin1, LOW);
  }else
  {
    digitalWrite(ledPin2, HIGH);
    delay(duration);
    digitalWrite(ledPin2, LOW);
  }

  //Stop tone on buzzerPin
  noTone(buzzerPin);

  delay(50);

  //Increment counter
  counter++;
}
void firstSection()
{
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);

  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);
}
void secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);

  delay(325);

  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  

  delay(350);
}


void RobotForward()
  {
   //Play first section
  firstSection();

  //Play second section
  secondSection();

  //Variant 1
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 350);  
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);  
  beep(cH, 125);
  beep(eH, 650);

  delay(500);

  //Repeat second section
  secondSection();

  //Variant 2
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 650);  

  delay(650);
	digitalWrite(MotorA_IN1, HIGH);
	digitalWrite(MotorA_IN2, LOW);
	digitalWrite(MotorB_IN3, HIGH);
	digitalWrite(MotorB_IN4, LOW);
  }

void RobotBackward()
  {
	digitalWrite(MotorA_IN1, LOW);
	digitalWrite(MotorA_IN2, HIGH);
	digitalWrite(MotorB_IN3, LOW);
	digitalWrite(MotorB_IN4, HIGH);
  }

void RobotLeft()
  {
	digitalWrite(MotorA_IN1, LOW);
	digitalWrite(MotorA_IN2, HIGH);
	digitalWrite(MotorB_IN3, HIGH);
	digitalWrite(MotorB_IN4, LOW);	
  }

void RobotRight()
  {
	digitalWrite(MotorA_IN1, HIGH);
	digitalWrite(MotorA_IN2, LOW);
	digitalWrite(MotorB_IN3, LOW);
	digitalWrite(MotorB_IN4, HIGH);	
  }

void RobotStop()
  {
	digitalWrite(MotorA_IN1, LOW);
	digitalWrite(MotorA_IN2, LOW);
	digitalWrite(MotorB_IN3, LOW);
	digitalWrite(MotorB_IN4, LOW);
  }
  
  
  


void loop()
  {
     float distance = 0.00;
     float RobotSpeed = 0.00;
     float RightDistance = 0.00;
     float LeftDistance = 0.00;
 
    
    // Measuring the distance in CM
    distance = search();
    
    
    if((distance <= 30)) // If obstracle found in 40 CM.
      {
        analogWrite(MotorA_PWM, 100); // Update speed in MOTORA Output Terminal
        analogWrite(MotorB_PWM, 100); // Update speed in MOTORB Output Terminal
    
        RobotStop(); //Robot Stop
        delay(400);
        
        servo.write(5);
        delay(1000);
        RightDistance = search();
        delay(1000);
        Serial.print("Right Distance = ");
        Serial.println(RightDistance);
        servo.write(90);
        delay(1000);
        servo.write(1800);
        delay(1000);
        LeftDistance = search();
        delay(1000);
        Serial.print("Left Distance = ");
        Serial.println(LeftDistance);
        servo.write(90);
        delay(1000);

          if(LeftDistance > RightDistance)
            {
              
              RobotLeft();
              delay(1000);            
                            
            }

            else 
            {
              RobotRight();
              delay(1000);              
            }
           
         RobotStop();
         delay(1000);
        
      
      }

  else if(distance>=30 && distance<=70)
  {
    analogWrite(MotorA_PWM, 180); // Update speed in MOTORA Output Terminal
    analogWrite(MotorB_PWM, 180); // Update speed in MOTORB Output Terminal
    RobotForward(); //Robot Move to Forward Direction
    
  }
   else
     {
       analogWrite(MotorA_PWM, 255); // Update speed in MOTORA Output Terminal
    analogWrite(MotorB_PWM, 255); // Update speed in MOTORB Output Terminal
        RobotForward(); //Robot Move to Forward Direction
     }
   
    
  }
  
  
