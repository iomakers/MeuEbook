// Definir porta do SERVP
const int  PORTA_SERVO = GPIO_NUM_17;
// Definir frequência de 50 Hz
int freq = 50;
// resolucao de 12 bits para controlar o servo vai de 0-4095
int  resolucao = 12;
int  canalServo = 0;
// Valor de 8 bits que vai de 0 a 255
uint8_t valorServo = 0;
// declarar protótipo da tarefa da buzina
static void mudaServo(void * );

// Usaremos rotina LEDC para ligar o servo
void setup() {
	
  ledcSetup(canalServo, freq, resolucao);
  ledcAttachPin(PORTA_SERVO, canalServo);
// declarar tarefa que irá mudar o valor do servo
  xTaskCreate(mudaServo, "mudaServo", 4096,   NULL, 1, NULL);
}

void loop() {

  
}

// Tarefa que roda o servo
static void mudaServo(void *){

  while(1){
    // Aqui vamos limitar o angulo do 1 ms a 2 ms da largura do sinal que é o 
   // sinal que o servo recebe, 20 é o período do sinal de 50 Hz
    int angulo = map(x, 0, 4095, (4095/20)*1, (4095/20)*2);
	 // Com resolução de 12 Bits resulta valores de escrita entre 0 e 4095 no LEDC 
	  ledcWrite(canalServo, angulo);
	  valorServo ++;
    // zera quando valor maior que 4095
    valorServo = valorServo & 0xFFF
    
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
