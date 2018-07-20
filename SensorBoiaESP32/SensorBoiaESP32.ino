// definir porta de leitura do sensor de boia
const int portaBOIA = GPIO_NUM_17;

void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor de boia como entrada
  pinMode(portaBOIA, INPUT);
}

void loop() {
  // realizar leitura do sensor de boia
  bool leitura = digitalRead(portaBOIA);
  // Realizar o print da leitura no serial
  if(leitura){
    Serial.println("Boia nivel alto");
  }else{
    Serial.println("Boia nivel baixo");
  }

  // realizar um delay  e inicializar leitura daqui a 500 ms
  delay(500);

}
