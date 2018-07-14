
// definir porta de leitura do sensor de presenca
const int portaPresenca = GPIO_NUM_20;
// declarar protótipo da tarefa que irá realizar leitura do sensor de presenca
static void leituraSensorPresenca(void * );
void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor de chuva como entrada
  pinMode(portaPresenca, INPUT);
  // declarar tarefa que irá realizar a leitura do sensor de chuva
  xTaskCreate(leituraSensorPresenca, "leituraSensorPresenca", 4096,   NULL, 1, NULL);

  
}

void loop() {
 
}
// Tarefa do sensor de Presenca
static void leituraSensorPresenca(void *){

  while(1){
     // realizar leitura do sensor de presenca
      bool leitura = digitalRead(portaPresenca);
      // Realizar o print da leitura no serial
      if(leitura){
        Serial.println("Presenca detectada");
      }else{
        Serial.println("Sem presenca de ninguem");
      }
      // realizar um delay e inicializar leitura daqui a 500 ms
      vTaskDelay(500 / portTICK_PERIOD_MS);
  } 
}




