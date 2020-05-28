#define CLACSON 3
#define LIGHTS 4
#define MOTOR1 5
#define MOTOR2 6
#define STEERING1 7
#define STEERING2 8

void warning(int timer){
  digitalWrite(LIGHTS,HIGH);
  tone(CLACSON,350);
  delay(timer);
  digitalWrite(LIGHTS,LOW);
  noTone(CLACSON);
  delay(timer);
}

void setup() {
  //Open Serial Comunication
  Serial.begin(115200);
  
  //Car Output pin
  pinMode(CLACSON,OUTPUT);
  pinMode(LIGHTS,OUTPUT);
  pinMode(MOTOR1,OUTPUT);
  pinMode(MOTOR2,OUTPUT);
  pinMode(STEERING1,OUTPUT);
  pinMode(STEERING2,OUTPUT);

  warning(200);
}

void loop(){
  //TEST LIGHTS
  Serial.println("LIGHTS: ON");
  digitalWrite(LIGHTS,HIGH);
  delay(500);
  Serial.println("LIGHTS: OFF");
  digitalWrite(LIGHTS,LOW);
  delay(500);

  //TEST CLACSON
  Serial.println("CLACSON: ON");
  tone(CLACSON,700);
  delay(500);
  Serial.println("CLACSON: OFF");
  noTone(CLACSON);
  delay(500);

  //TEST MOTOR
  Serial.println("MOTOR1: OFF");
  Serial.println("MOTOR2: ON");
  for(int i=0; i<=255; i+=5){
    analogWrite(MOTOR1,LOW);
    analogWrite(MOTOR2,i);
    delay(100);
  }
  Serial.println("MOTOR1: OFF");
  Serial.println("MOTOR2: OFF");
  analogWrite(MOTOR1,LOW);
  analogWrite(MOTOR2,LOW);
  delay(500);

  Serial.println("MOTOR1: ON");
  Serial.println("MOTOR2: OFF");
  for(int i=0; i<=255; i+=5){
    analogWrite(MOTOR1,i);
    analogWrite(MOTOR2,LOW);
    delay(100);
  }
  Serial.println("MOTOR1: OFF");
  Serial.println("MOTOR2: OFF");
  analogWrite(MOTOR1,LOW);
  analogWrite(MOTOR2,LOW);
  delay(500);

  //TEST STEERING MOTOR
  Serial.println("STEERING1: ON");
  Serial.println("STEERING2: OFF");
  digitalWrite(STEERING1,HIGH);
  digitalWrite(STEERING2,LOW);
  delay(500);
  Serial.println("STEERING1: OFF");
  Serial.println("STEERING2: OFF");
  digitalWrite(STEERING1,LOW);
  digitalWrite(STEERING2,LOW);
  delay(500);

  Serial.println("STEERING1: OFF");
  Serial.println("STEERING2: ON");
  digitalWrite(STEERING1,LOW);
  digitalWrite(STEERING2,HIGH);
  delay(500);
  Serial.println("STEERING1: OFF");
  Serial.println("STEERING2: OFF");
  digitalWrite(STEERING1,LOW);
  digitalWrite(STEERING2,LOW);
  delay(500);
}
