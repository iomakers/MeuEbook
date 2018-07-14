
// definir porta de leitura do sensor de corrente
const int portaCorrente = GPIO_NUM_35;
#define  TAMANHO 100
// Offset do sensor de tensão
float offset = 1.2;
// vetor de leituras
float leituras[TAMANHO];
float ganho = 200;
int i = 0;
// declarar protótipo da tarefa que irá realizar leitura do sensor de tensao
static void leituraSensorCorrente(void * );

void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor de tensao como entrada
  pinMode(portaCorrente, INPUT);
  // declarar tarefa que irá realizar a leitura do sensor de tensao
  xTaskCreate(leituraSensorCorrente, "leituraSensorCorrente", 4096,   NULL, 1, NULL);


}

void loop() {

}
// Tarefa do sensor de tensao
static void leituraSensorCorrente(void *){

  while(1){
    // realizar leitura do sensor de corrente
    leituras[i] = analogRead(portaCorrente);
    // mapear valores de 0-4095 para 0 a 3.3 V
    leituras[i] = (leituras[i]/4095)*3.3;
    // retirar offset na leitura
    leituras[i] = leituras[i] - offset;
    // Multiplicar pelo ganho do sensor de tensao (transformador)
    leituras[i] = ganho*leituras[i];
    i++;


    if(i>99){
      float rms = 0;
      // calcular RMS do sensor de corrente
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
      vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}
