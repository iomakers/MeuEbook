
// definir porta de leitura do sensor de chuva
const int portaChuva = GPIO_NUM_35;
// declarar protótipo da tarefa que irá realizar leitura do sensor de chuva
static void leituraSensorChuva(void * );
void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor de chuva como entrada
  pinMode(portaChuva, INPUT);
  // declarar tarefa que irá realizar a leitura do sensor de chuva
  xTaskCreate(leituraSensorChuva, "leituraSensorChuva", 4096,   NULL, 1, NULL);


}

void loop() {

}
// Tarefa do sensor de chuva
static void leituraSensorChuva(void *){

  while(1){
     // realizar leitura do sensor de chuva
      int leitura = analogRead(portaChuva);
      // Realizar o print da leitura no serial
      Serial.println("Leitura do Sensor de Chuva usando FreeRTOS:");
      Serial.println(leitura);
      // realizar um delay e inicializar leitura daqui a 1 segundos
      vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
