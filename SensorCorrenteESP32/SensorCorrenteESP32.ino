// definir porta de leitura do sensor de tensão
// tem de ser uma porta com conversor analógico Digital
const int portaCorrente = GPIO_NUM_35;

#define  TAMANHO 100

// Offset do sensor de corrente
float offset = 1.2;
// vetor de leituras
float leituras[TAMANHO];
float ganho = 30;
int i = 0;
void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor de tensao como entrada
  pinMode(portaCorrente, INPUT);
}

void loop() {
  // realizar leitura do sensor de corrente
  leituras[i] = analogRead(portaCorrente);
  // mapear valores de 0-4095 para 0 a 3.3 V
  leituras[i] = (leituras[i]/4095)*3.3;
  // retirar offset na leitura
  leituras[i] = leituras[i] - offset;
  // Multiplicar pelo ganho do sensor de corrente (transformador)
  leituras[i] = ganho*leituras[i];
  i++;
  // Se realizadas 100 leituras, calcular rms e printar na serial
  if(i>99){
    float rms = 0;
    // calcular RMS do sensor de tensão
    for (int k = 0; k < i; k++) {
      rms = rms + leituras[i]*leituras[i];
    }
    rms = sqrt(rms/TAMANHO);

    // Realizar o print da leitura no serial
    Serial.println("Leitura do Sensor de Corrente, valor RMS:");
    Serial.println(rms);
    i = 0;
  }

  // realizar um delay de 20 ms
  delay(20);

}
