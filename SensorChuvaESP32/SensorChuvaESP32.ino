// definir porta de leitura do sensor de chuva
const int portaChuva = GPIO_NUM_35

void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor de chuva como entrada
  pinMode(portaChuva, INPUT);
}

void loop() {
  // realizar leitura do sensor de chuva
  int leitura = analogRead(portaChuva);
  // Realizar o print da leitura no serial
  Serial.println("Leitura do Sensor de Chuva:");
  Serial.println(leitura);
  // realizar um delay e inicializar leitura daqui a 2 segundos
  delay(2000);

}
