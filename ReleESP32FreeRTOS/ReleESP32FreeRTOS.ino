// definir porta de rele
const int  PORTA_RELE = GPIO_NUM_17;

// declarar protótipo da tarefa que irá realizar leitura do sensor de chuva
static void piscarLED(void * );
void setup() {
  // Definir porta do Led como saída
  pinMode(PORTA_RELE, OUTPUT);
  // declarar tarefa que irá fazer o led piscar
  xTaskCreate(piscarLED, "piscarLED", 4096,   NULL, 1, NULL);
}

void loop() {
}

// Tarefa que pisca o LED
static void piscarLED(void *){
  // variável do estado do LED
  bool estadoLed = false;
  while(1){
      // Liga ou desliga o estado do Led mediante o valor da variável estadoLED
      digitalWrite(PORTA_RELE, estadoLed);
      // muda o estado do led
      estadoLed = !estadoLed;
      // realizar um delay para led piscar a cada 1 segundo
      vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
