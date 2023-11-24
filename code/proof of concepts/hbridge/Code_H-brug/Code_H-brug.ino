#define AIN1 6
#define AIN2 13
#define BIN1 9
#define BIN2 10

void setup() {
  Serial.begin(9600);
  
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  
}
 
void loop() {

  for (int i = 0; i <= 255; i += 1) {
    analogWrite(AIN1, i);
    digitalWrite(AIN2, LOW);
    analogWrite(BIN1, i);
    digitalWrite(BIN2, LOW);
    delay(10);
  }
  
  delay(1000);
  analogWrite(AIN1, LOW);
  analogWrite(BIN1, LOW);
  
  for (int i = 0; i <= 255; i += 1) {
    analogWrite(AIN1, LOW);
    digitalWrite(AIN2, i);
    analogWrite(BIN1, LOW);
    digitalWrite(BIN2, i);
    delay(10);
  }

  delay(1000);
  analogWrite(AIN1, LOW);
  analogWrite(BIN1, LOW);

  delay(1000);
}
