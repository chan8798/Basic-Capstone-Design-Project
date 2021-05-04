// left motor pins
#define ENA 6
#define IN1 7
#define IN2 8

// right motor pins
#define IN3 9
#define IN4 10
#define ENB 11

void setup() {
  // set up serial port
  Serial.begin(9600);
  
  // set all the motor pins OUTPUT mode
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // wait 2 seconds after power up
  delay(2000);

  // set motors to move forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  for (int pwm = 1; pwm <= 255; pwm++) {
    Serial.println(pwm);
    analogWrite(ENA, pwm);
    analogWrite(ENB, pwm);
    delay(100);
  }

  // set motors to move backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
 
  for (int pwm = 1; pwm <= 255; pwm++) {
    Serial.println(pwm);
    analogWrite(ENA, pwm);
    analogWrite(ENB, pwm);
    delay(100);
  }

  // stop motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  // nothing to do here
}
