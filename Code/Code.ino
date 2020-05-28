#include <SPI.h>
#include <symax_protocol.h>

#define CLACSON 3
#define LIGHTS 4
#define MOTOR1 5
#define MOTOR2 6
#define STEERING1 7
#define STEERING2 8
#define NRF_CE 9
#define NRF_CS 10

nrf24l01p wireless; 
symaxProtocol protocol;
rx_values_t rxValues;
uint8_t value;

bool lostConnection = true;
bool newConnection = false;

void warning(int timer){
  digitalWrite(LIGHTS,HIGH);
  tone(CLACSON,350);
  delay(timer);
  digitalWrite(LIGHTS,LOW);
  noTone(CLACSON);
  delay(timer);
}

void setup(){
  warning(200);
  
  //Open Serial Comunication
  Serial.begin(115200);
  
  //nRF24L01
  pinMode(SS, OUTPUT);
  wireless.setPins(NRF_CE,NRF_CS);
  wireless.setPwr(PWRLOW);
  protocol.init(&wireless);
  
  //Car Output pin
  pinMode(CLACSON,OUTPUT);
  pinMode(LIGHTS,OUTPUT);
  pinMode(MOTOR1,OUTPUT);
  pinMode(MOTOR2,OUTPUT);
  pinMode(STEERING1,OUTPUT);
  pinMode(STEERING2,OUTPUT);
}

void loop(){
  value = protocol.run(&rxValues);
  switch(value){
    case  NOT_BOUND:
      if(not lostConnection){
        warning(500);
        lostConnection = true;
      }
      Serial.println("Not bound");
      analogWrite(MOTOR1,0);
      analogWrite(MOTOR2,0);
      digitalWrite(STEERING1,LOW);
      digitalWrite(STEERING2,LOW);
      newConnection = false;
      break;

    case  BIND_IN_PROGRESS:
      digitalWrite(LIGHTS,HIGH);
      Serial.println("Bind in progress");
      analogWrite(MOTOR1,0);
      analogWrite(MOTOR2,0);
      digitalWrite(STEERING1,LOW);
      digitalWrite(STEERING2,LOW);
      break;
    
    case BOUND_NEW_VALUES:
      if(not newConnection){
        digitalWrite(LIGHTS,LOW);
        warning(100);
        warning(100);
        newConnection = true;
        lostConnection = false;
      }
      
      //STEERING
      if(rxValues.roll < 40 && rxValues.roll > -40){
        digitalWrite(STEERING1,LOW);
        digitalWrite(STEERING2,LOW);
      }
      else if(rxValues.roll > 40){  //RIGHT
        digitalWrite(STEERING1,HIGH);
        digitalWrite(STEERING2,LOW);
      }
      else if(rxValues.roll < -40){ //LEFT
        digitalWrite(STEERING1,LOW);
        digitalWrite(STEERING2,HIGH);
      }
      
      //MOTOR
      if(rxValues.pitch < 40 && rxValues.pitch > -40){
        analogWrite(MOTOR1,LOW);
        analogWrite(MOTOR2,LOW);
      }
      else if(rxValues.pitch > 40 && rxValues.throttle > 75){ //FARWARD
        analogWrite(MOTOR1,LOW);
        analogWrite(MOTOR2,rxValues.throttle);
      }
      else if(rxValues.pitch < -40 && rxValues.throttle > 75){//BACK
        analogWrite(MOTOR1,rxValues.throttle);
        analogWrite(MOTOR2,LOW);
      }

      //LIGHTS
      if(rxValues.highspeed){
        digitalWrite(LIGHTS,HIGH);
      }
      else{
        digitalWrite(LIGHTS,LOW);
      }
      
      //CLACSON
      if(rxValues.flip){
        tone(CLACSON,700);
      }
      else{
        noTone(CLACSON);
      }
      
      Serial.print("\t"); Serial.print(rxValues.throttle);
      Serial.print("\t"); Serial.print(rxValues.yaw);
      Serial.print("\t"); Serial.print(rxValues.pitch);
      Serial.print("\t"); Serial.print(rxValues.roll);
      Serial.print("\t"); Serial.print(rxValues.highspeed);
      Serial.print("\t"); Serial.println(rxValues.flip);
      break;

    case BOUND_NO_VALUES:
      break;

    default:
      break;
  }
}
