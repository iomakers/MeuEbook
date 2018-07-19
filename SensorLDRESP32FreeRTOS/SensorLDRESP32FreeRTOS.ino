
// definir porta de leitura do sensor de LDR
const int portaLDR = GPIO_NUM_35;
// declarar protótipo da tarefa que irá realizar leitura do sensor de LDR
static void leituraSensorLDR(void * );
void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor de chuva como LDR
  pinMode(portaLDR, INPUT);
  // declarar tarefa que irá realizar a leitura do sensor de LDR
  xTaskCreate(leituraSensorLDR, "leituraSensorLDR", 4096,   NULL, 1, NULL);


}

void loop() {

}
// Tarefa do sensor LDR
static void leituraSensorLDR(void *){

  while(1){
     // realizar leitura do sensor de ldr
      int leitura = analogRead(portaLDR);
      // Realizar o print da leitura no serial
      Serial.println("Leitura do Sensor LDR usando FreeRTOS:");
      Serial.println(leitura);
      // realizar um delay e inicializar leitura daqui a 1 segundos
      vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
