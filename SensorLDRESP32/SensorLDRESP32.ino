// definir porta de leitura do sensor de ldr
const int portaLDR = GPIO_NUM_35;

void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor ldr como entrada
  pinMode(portaLDR, INPUT);
}

void loop() {
  // realizar leitura do sensor ldr
  int leitura = analogRead(portaLDR);
  // Realizar o print da leitura no serial
  Serial.println("Leitura do Sensor de LDR:");
  Serial.println(leitura);
  // realizar um delay e inicializar leitura daqui a 2 segundos
  delay(2000);

}
