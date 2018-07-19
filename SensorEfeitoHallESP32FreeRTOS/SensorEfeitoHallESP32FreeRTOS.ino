
// definir porta de leitura do sensor de efeito Hall
const int portaHall = GPIO_NUM_35;
// declarar protótipo da tarefa que irá realizar leitura do sensor de efeito Hall
static void leituraSensorHall(void * );
void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor de efeito Hall como entrada
  pinMode(portaHall, INPUT);
  // declarar tarefa que irá realizar a leitura do sensor de efeito Hall
  xTaskCreate(leituraSensorHall, "leituraSensorHall", 4096,   NULL, 1, NULL);


}

void loop() {

}
// Tarefa do sensor de efeito Hall
static void leituraSensorHall(void *){

  while(1){
     // realizar leitura do sensor de efeito Hall
      int leitura = analogRead(portaHall);
      // Realizar o print da leitura no serial
      Serial.println("Leitura do Sensor de Efeito Hall usando FreeRTOS:");
      Serial.println(leitura);
      // realizar um delay e inicializar leitura daqui a 1 segundos
      vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
