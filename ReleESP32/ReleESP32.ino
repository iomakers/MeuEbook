// Definir porta do relé
const int  PORTA_RELE = GPIO_NUM_17;

void setup() {
  // Definir porta do relé como saída
  pinMode(PORTA_RELE, OUTPUT);
}

void loop() {
  digitalWrite(PORTA_RELE, HIGH);
  delay(1000);
  digitalWrite(PORTA_RELE, LOW);
  delay(1000);
}
