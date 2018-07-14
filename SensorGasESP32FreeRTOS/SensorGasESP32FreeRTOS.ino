
// definir porta de leitura do sensor de gas
const int portaGas = GPIO_NUM_35;
// declarar protótipo da tarefa que irá realizar leitura do sensor de gas
static void leituraSensorGas(void * );
void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor de gas como entrada
  pinMode(portaGas, INPUT);
  // declarar tarefa que irá realizar a leitura do sensor de gas
  xTaskCreate(leituraSensorGas, "leituraSensorGas", 4096,   NULL, 1, NULL);


}

void loop() {

}
// Tarefa do sensor de gas
static void leituraSensorGas(void *){

  while(1){
     // realizar leitura do sensor de chuva
      int leitura = analogRead(portaGas);
      // Realizar o print da leitura no serial
      Serial.println("Leitura do Sensor de Gas:");
      Serial.println(leitura);
      // realizar um delay e inicializar leitura daqui a 2 segundos
      vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}
