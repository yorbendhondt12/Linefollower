const int buttonPin = 2;
const int ledPin = 4;
volatile int buttonState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT); // Interne pull-up weerstand inschakelen
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, RISING);
}

void loop() {
  // De hoofdcode hier kan andere taken uitvoeren terwijl het wacht op de interrupt
}

void buttonInterrupt() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("High");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("Low");
  }
}
