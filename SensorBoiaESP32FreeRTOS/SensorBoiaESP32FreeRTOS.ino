
// definir porta de leitura do sensor boia
const int portaBOIA = GPIO_NUM_17;
// declarar protótipo da tarefa que irá realizar leitura do sensor boia
static void leituraSensorBoia(void * );
void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor boia como entrada
  pinMode(portaBOIA, INPUT);
  // declarar tarefa que irá realizar a leitura do sensor de boia
  xTaskCreate(leituraSensorBoia, "leituraSensorBoia", 4096,   NULL, 1, NULL);


}

void loop() {

}
// Tarefa do sensor de boia
static void leituraSensorBoia(void *){

  while(1){  // realizar leitura do sensor de boia
	  bool leitura = digitalRead(portaBOIA);
	  // Realizar o print da leitura no serial
	  if(leitura){
		Serial.println("Boia nivel alto");
	  }else{
		Serial.println("Boia nivel baixo");
	  }
      // realizar um delay e inicializar leitura daqui a 500 ms
      vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
