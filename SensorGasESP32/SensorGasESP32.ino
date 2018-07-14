// definir porta de leitura do sensor de gas
const int portaGas = GPIO_NUM_35;

void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor de gas como entrada
  pinMode(portaGas, INPUT);
}

void loop() {
  // realizar leitura do sensor de gas
  int leitura = analogRead(portaGas);
  // Realizar o print da leitura no serial
  Serial.println("Leitura do Sensor de Gas:");
  Serial.println(leitura);
  // realizar um delay e inicializar leitura daqui a 2 segundos
  delay(2000);

}
