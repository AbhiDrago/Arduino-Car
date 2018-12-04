#include <SoftwareSerial.h>

#define IN1 2      //IN1
#define IN2 3        //IN2
#define ENA 6          //ENA
#define ENB 7        //ENB
#define IN3 4          //IN3
#define IN4 5          //IN4
#define trigger 11      //Trigger
#define echo 10        //Echo
SoftwareSerial BT(0, 1); //TX, RX respetively

void followMe(void);
void avoidMe(void);
void back(void);
void left(void);
void right(void);
void stopm(void);
void forward(void);
void inputs(void);
void sharpright(void);

char val;
int duration;
float distance;
String readvoice;
int flag=0;
//flag = 0 -> Stop
//flag = 1 -> Forward
//flag = 2 -> Back
//flag = 3 -> Right
//flag = 4 -> Left
//flag = 5 -> FollowMe
//flag = 6 -> AvoidMe

void setup(void){
  BT.begin(9600);
  Serial.begin (9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(IN1 ,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
}


void loop(void) {
  
  while (BT.available()){  //Check if there is an available byte to read
    delay(10); //Delay added to make thing stable
    char c = BT.read(); //Conduct a serial read
    readvoice += c; //build the string- "forward", "reverse", "left" and "right"

    val = Serial.read();
    Serial.println(val);
  } 
  if( val == 'F'){ // Forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW); 
  }else if(val == 'B'){ // Backward
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH); 
  }else if(val == 'L'){ //Left
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }else if(val == 'R'){ //Right
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW); 
  }else if(val == 'S'){ //Stop
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW); 
  }else if(val == 'I'){ //Forward Right
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }else if(val == 'J'){ //Backward Right
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }else if(val == 'G'){ //Forward Left
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }else if(val == 'H'){ //Backward Left
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH); 
  }
  
  if (readvoice.length() > 0) {
    Serial.println(readvoice);
    if(readvoice == "*follow me#"){
      followMe();
      flag=5;
    }else if(readvoice == "*avoid me#"){
      avoidMe();
      flag = 6;
    }else if(readvoice == "*stop#"){
      stopm();
      flag = 0;
    }else if(readvoice == "*forward#"){
      flag=1;
      forward();
    }else if(readvoice == "*back#"){
      flag=2;
      back();
    }else if(readvoice == "*left#"){
      flag=4;
      left();
    }else if(readvoice == "*right#"){
      flag=3;
      right();
    }
  }
  if(flag == 1){
      forward();
  }else if(flag == 2){
      back();
  }else if(flag == 3){
      right();
  }else if(flag == 4){
      left();
  }else if(flag == 5){
      followMe();
  }else if(flag == 6){
      avoidMe();
  }
  readvoice="";
}


void followMe(void){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) / 29.1;
  digitalWrite(trigger, LOW); 
  Serial.print("forward Distance: ");
  Serial.println(distance);
  if(distance>30){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }else{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
}
void avoidMe(void){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) / 29.1;
  digitalWrite(trigger, LOW); 
  Serial.print("forward Distance: ");
  Serial.println(distance);
  if(distance<30){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    back();
    left();
    right();
  }else{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
}
void forward(void){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) / 29.1;
  digitalWrite(trigger, LOW); 
  Serial.print("forward Distance: ");
  Serial.println(distance);
  if(distance<30){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    flag=0;
  }
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void back(void){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void stopm(void){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void left(void){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void right(void){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
