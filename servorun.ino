  
#include <Servo.h> 
#include <PWMServo.h>

const int servoPin = 9; 
const int coinPin = 3;
volatile boolean check = LOW;

Servo Servo1; 


void setup() { 

  pinMode (coinPin,INPUT_PULLUP);
  
  Servo1.attach(servoPin); 
  attachInterrupt(digitalPinToInterrupt(coinPin), coinInserted, FALLING);
   
}

void loop(){ 
  if(check){
    Servo1.write(90);
    delay(500);
    Servo1.write(0);
    check=!check;
  }
}

void coinInserted(){

  check=!check;
   
}
