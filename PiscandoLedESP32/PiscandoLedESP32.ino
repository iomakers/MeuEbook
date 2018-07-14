const int  PORTA_LED = GPIO_NUM_8;

void setup() {

  pinMode(PORTA_LED, OUTPUT);

}

void loop() {
  digitalWrite(PORTA_LED, HIGH);
  delay(500);
  digitalWrite(PORTA_LED, LOW);
  delay(500);
}
