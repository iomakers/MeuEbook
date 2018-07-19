// definir porta de leitura do sensor de presenca
const int portaPresenca = GPIO_NUM_12;

void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor de presenca como entrada
  pinMode(portaPresenca, INPUT);
}

void loop() {
  // realizar leitura do sensor de presenca
  bool leitura = digitalRead(portaPresenca);
  // Realizar o print da leitura no serial
  if(leitura){
    Serial.println("Presenca detectada");
  }else{
    Serial.println("Sem presenca de ninguem");
  }

  // realizar um delay  e inicializar leitura daqui a 500 ms
  delay(500);

}
