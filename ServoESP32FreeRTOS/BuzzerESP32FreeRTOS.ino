// Definir porta do Buzzer
const int  PORTA_BUZZER = GPIO_NUM_17;
// Definir frequência de 1 kHZ
int freq = 1000;
int  resolucao = 8;
int  canalBuzzer = 0;
// Valor de 8 bits que vai de 0 a 255
uint8_t valorBuzzer = 0;
// declarar protótipo da tarefa da buzina
static void mudaBuzzer(void * );

// Usaremos rotina LEDC para ligar o buzzer
void setup() {
	
  ledcSetup(canalBuzzer, freq, resolucao);
  ledcAttachPin(PORTA_BUZZER, canalBuzzer);
// declarar tarefa que irá mudar o valor sonoro da Buzina
  xTaskCreate(mudaBuzzer, "mudaBuzzer", 4096,   NULL, 1, NULL);
}

void loop() {

  
}

// Tarefa da buzina
static void mudaBuzzer(void *){

  while(1){
	 // Com resolução de 8 Bits resulta valores de escrita entre 0 e 255
	  ledcWrite(canalBuzzer, valorBuzzer);
	  // Quando o valor maior que 255, ele estoura e volta para 0
	  valorBuzzer ++;
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
