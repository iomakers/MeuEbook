// definir porta de leitura do sensor de Vazao
const int portaVazao = GPIO_NUM_35;

// declarar protótipo da tarefa que irá realizar leitura do sensor de vazao
static void leituraVazao(void * );
volatile unsigned int pulsos_vazao = 0;
float vazao = 0;
// interrupção
void IRAM_ATTR gpio_isr_handler_up(void* arg)
{
  pulsos_vazao++;
  portYIELD_FROM_ISR();
}

/*
Inicializa sensor de vazão com interrupção na subida de um pulso
 */
void iniciaVazao(gpio_num_t Port){
  gpio_set_direction(Port, GPIO_MODE_INPUT);
  gpio_set_intr_type(Port, GPIO_INTR_NEGEDGE);
  gpio_set_pull_mode(Port, GPIO_PULLUP_ONLY);
  gpio_intr_enable(Port);
  gpio_install_isr_service(0);
  gpio_isr_handler_add(Port, gpio_isr_handler_up, (void*) Port);
}

void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir porta do sensor de gas como entrada
  iniciaVazao((gpio_num_t) portaVazao);

  xTaskCreate(&leituraVazao, "leituraVazao", 4096, NULL, 20, NULL);
}

void loop() {
  Serial.println("Leitura do Sensor de Vazao:");
  Serial.println(vazao);
  delay(2000);
}

static void leituraVazao(void *){
  while (1) {
	  
    vazao = pulsos_vazao/5.5;
	Serial.println("Pulsos num segundo:");
    Serial.println(pulsos_vazao);
    pulsos_vazao = 0;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

}
