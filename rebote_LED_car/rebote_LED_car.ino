#include <IRremote.h>

int RECV_PIN = A4;//포트설정
IRrecv irrecv(RECV_PIN);
decode_results results;//구조체정의
int on = 0;//플래그
unsigned long last = millis();

long run_car = 0x00FF18E7;//2번 버튼
long back_car = 0x00FF4AB5;//8번 버튼
long left_car = 0x00FF10EF;//4번 버튼
long right_car = 0x00FF5AA5;//6번 버튼
long stop_car = 0x00FF38C7;//5번 버튼
long left_turn = 0x00FF30CF;//1번 버튼
long left_turn2=0x00FF42BD;//7번버튼
long right_turn = 0x00FF7A85;//3번 버튼
long right_turn2 =0xFF52AD;//9번버튼


//==============================
int Left_motor_back=4;     //좌측모터후진(IN1)
int Left_motor_go=5;     //좌측모터전진(IN2)

int Right_motor_go=6;    // 우측모터전진(IN3)
int Right_motor_back=7;    // 우측모터후진(IN4)

// buzzer and LED pins
int ledPin1=9;
int ledPin2=3;


void setup()
{
  //모터구동을을 위한 초기화
  pinMode(Left_motor_go,OUTPUT);
  pinMode(Left_motor_back,OUTPUT); 
  pinMode(Right_motor_go,OUTPUT);
  pinMode(Right_motor_back,OUTPUT);
  pinMode(13, OUTPUT);//포트설정 출력
 
  pinMode(ledPin1, OUTPUT);  
  pinMode(ledPin2, OUTPUT); 

  
  irrecv.enableIRIn(); // Start the receiver
}
void LED1()
{
  for(int i=0;i<7;i++){
  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,HIGH);
  delay(500);
  digitalWrite(ledPin1,HIGH);
  digitalWrite(ledPin2,LOW);
  delay(500);
  }
}
void LED2()
{
  for(int i=0;i<7;i++){
  digitalWrite(ledPin1,HIGH);
  digitalWrite(ledPin2,LOW);
  delay(500);
  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,HIGH);
  delay(500);
  }
}
void run()     // 전진
{

  digitalWrite(ledPin1,HIGH);
  digitalWrite(ledPin2,HIGH);
  digitalWrite(Right_motor_go,HIGH);  //우측모터전진
  digitalWrite(Right_motor_back,LOW);     
  digitalWrite(Left_motor_go,HIGH);  //좌측모터전진
  digitalWrite(Left_motor_back,LOW);
}

void brake()         //제동, 정지
{

  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,LOW);
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
}

void left()         //좌회전(좌측정지，우측직진)
{

  digitalWrite(ledPin1,HIGH);
  digitalWrite(ledPin2,LOW);
  digitalWrite(Right_motor_go,HIGH); //우측모터전진
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);   //좌측모터정지
  digitalWrite(Left_motor_back,LOW);
}

void spin_left()         //좌측스핀(좌측후진，우측직진)
{
  LED1();
  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,HIGH);
  delay(500);
  digitalWrite(ledPin1,HIGH);
  digitalWrite(ledPin2,LOW);
  delay(500);
  digitalWrite(Right_motor_go,HIGH);  // 우측모터전진
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);   //좌측모터후진
  digitalWrite(Left_motor_back,HIGH);

}

void right()        //우회전(우측정지, 좌측직진)
{

  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,HIGH);
  digitalWrite(Right_motor_go,LOW);   //우측모터정지
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,HIGH);//좌측모터전진
  digitalWrite(Left_motor_back,LOW);

}

void spin_right()        //우측스핀(우측후진, 좌측전진)
{
  LED2();
  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,HIGH);
  delay(500);
  digitalWrite(ledPin1,HIGH);
  digitalWrite(ledPin2,LOW);
  delay(500);
  digitalWrite(Right_motor_go,LOW); //우측모터후진
  digitalWrite(Right_motor_back,HIGH);
  digitalWrite(Left_motor_go,HIGH); //좌측모터전진
  digitalWrite(Left_motor_back,LOW);
}

void back()          //후진
{

  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,LOW);
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,HIGH);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,HIGH);
}


void dump(decode_results *results)
{
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) 
  {
    brake();
  } 
}

void loop()
{
  if (irrecv.decode(&results)) //IR리모컨 라이브러리 호출
  {
     if (millis() - last > 300) //수신신호 결정
    {
      on = !on;//수신신호 반전
      digitalWrite(13, on ? HIGH : LOW);//수신신호를 LED(13)로 표시
      dump(&results);//수신신호 디코딩
    }
    if (results.value == run_car )//2번 버튼
      run();//전진
    if (results.value == back_car )//8번 버튼
      back();//후진
    if (results.value == left_car )//4번 버튼
      left();//좌회전
    if (results.value == right_car )//6번 버튼
      right();//우회전
    if (results.value == stop_car )//5번 버튼
      brake();//정지
    if (results.value == left_turn )//1번 버튼
      spin_left();//좌스핀
    if (results.value == right_turn )//3번 버튼
      spin_right();//우스핀
    if (results.value == left_turn2 )//7번 버튼
      spin_left();//좌스핀
    if (results.value == right_turn2 )//9번 버튼
      spin_right();//우스핀


    last = millis();      
    irrecv.resume(); // Receive the next value
  }
}
