// definir porta de leitura do sensor de efeito Hall
const int portaHall = GPIO_NUM_35;

void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor de efeito Hall como entrada
  pinMode(portaHall, INPUT);
}

void loop() {
  // realizar leitura do sensor de efeito Hall
  int leitura = analogRead(portaHall);
  // Realizar o print da leitura no serial
  Serial.println("Leitura do Sensor de Efeito Hall:");
  Serial.println(leitura);
  // realizar um delay e inicializar leitura daqui a 1 segundos
  delay(1000);

}
