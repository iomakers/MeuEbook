// Definir porta do Buzzer
const int  PORTA_LED = GPIO_NUM_17;
// Definir frequência de 5 HZ
int freq = 5;
int  resolucao = 8;
int  canalLED = 0;
// Valor de 8 bits que vai de 0 a 255
uint8_t valorLED = 0;
// declarar protótipo da tarefa da buzina
static void piscarLED(void * );

// Usaremos rotina LEDC para ligar o buzzer
void setup() {
	
  ledcSetup(canalLED, freq, resolucao);
  ledcAttachPin(PORTA_LED, canalLED);
// declarar tarefa que irá mudar o valor do brilho do LED
  xTaskCreate(piscarLED, "piscarLED", 4096,   NULL, 1, NULL);
}

void loop() {

  
}

// Tarefa da buzina
static void piscarLED(void *){

  while(1){
	 // Com resolução de 8 Bits resulta valores de escrita entre 0 e 255
	  ledcWrite(canalLED, valorLED);
	  // Quando o valor maior que 255, ele estoura e volta para 0
	  valorLED ++;
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}


