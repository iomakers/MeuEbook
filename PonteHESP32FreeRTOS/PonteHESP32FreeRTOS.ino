/*
 * Tabela de Verdade da Ponte H L298N
 * Motor A            IN1       IN2
 * Horário            3,3V      GND
 * Anti-Horário       GND       3,3V
 * Ponto Morto        GND       GND
 * FREIO              3,3V      3,3V 
 * Motor B            IN3       IN4
 * Horário            3,3V      GND
 * Anti-Horário       GND       3,3V
 * Ponto Morto        GND       GND
 * FREIO              3,3V      3,3V 
 */

// Definir porta do MOTOR
const int  PORTA_MOTOR_1 = GPIO_NUM_23;
const int  PORTA_MOTOR_2 = GPIO_NUM_27;
// Definir porta do BOTAO
const int  PORTA_BOTAO = GPIO_NUM_26;
// Definir frequência de 1 kHZ
int freq = 1000;
int  resolucao = 8;
int  canalMotor = 0;
// Valor de 8 bits que vai de 0 a 255
uint8_t velocidade = 100;
// declarar protótipo da tarefa do motor
static void ligaMotor(void *);
int estadoLigado = 0;
// Tarefa do botao


static void botaoLigaMotor(void *);
// Usaremos rotina LEDC para ligar o motor e mudar sua velocidade
void setup() {
  ledcSetup(canalMotor, freq, resolucao);
  ledcAttachPin(PORTA_MOTOR_1, canalMotor);
  pinMode(PORTA_MOTOR_2, OUTPUT);
  pinMode(PORTA_BOTAO, INPUT);
// declarar tarefa que irá ligar o motor
  xTaskCreate(ligaMotor, "ligaMotor", 4096,   NULL, 1, NULL);
  xTaskCreate(botaoLigaMotor, "botaoLigaMotor", 4096,   NULL, 1, NULL);
}

void loop() {

  
}

// Tarefa de ligar motor
static void ligaMotor(void *){

  while(1){
	 // Com resolução de 8 Bits resulta valores de escrita entre 0 e 255
   // Gira o Motor  no sentido horario
   if(estadoLigado){
    ledcWrite(canalMotor, velocidade);
    digitalWrite(PORTA_MOTOR_2, LOW);
   }else{
    ledcWrite(canalMotor, 0);
    digitalWrite(PORTA_MOTOR_2, LOW);
   }
  
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

static void botaoLigaMotor(void *){
  while(1){
    // Se botão pressionado, liga motor
    if(digitalRead(PORTA_BOTAO)){
      // Se valor maior que 255 ele estoura e volta para 0
      velocidade = velocidade + 10;
      estadoLigado = 1;
    }else{
      velocidade = 0;
      estadoLigado = 0;
    }
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}









