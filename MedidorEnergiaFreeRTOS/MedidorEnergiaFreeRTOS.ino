/**
* Objetivo: Medidor de Energia
* 
*
* Author: João Campos
* 
*
*/
// Tamanho vetor de corrente e tensão
#define TAM 128
// Resolução do ADC
#define ADCresolution 12
volatile unsigned int i = 0;


// Constantes do medidor
const float A = 3.3;
float offsetTC = 1.45;
float offsetTP = 1.44;
float ganhoTC = 30;
float ganhoTP = 196;
float  ADCcounts;
volatile float I[TAM];
volatile float V[TAM];

volatile bool flag = false;

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

float  Irms = 0;
float  Vrms = 0;
// Definição das portas do TC e TP
const int TCPin = GPIO_NUM_34;
const int TPPin = GPIO_NUM_35;
TaskHandle_t samplerTaskHandle = NULL;

// Declarar protótipos das funções
static void Amostrador(void *);
void IRAM_ATTR onTimer();
static void calculaRMS(void *);

void setup()
{
  
  Serial.begin(115200);
  // inicializa o ADC para leitura de corrente e tensão, ver setupADC.h
   pinMode(TCPin, INPUT);
   pinMode(TPPin, INPUT);
   ADCcounts = pow(2, ADCresolution);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1041, true);
  timerAlarmEnable(timer);
  // Declarar tarefas para rodar no core 0 do Esp32
  xTaskCreatePinnedToCore(&Amostrador, "Amostrador", 4096, NULL, 1000, &samplerTaskHandle, 0);
  xTaskCreatePinnedToCore(&calculaRMS, "calculaRMS", 4096, NULL, 0, NULL, 0);
  
}






void loop(){

  digitalWrite(CARGA_PORT, !mb.Coil(CARGA_COIL));
  mb.Ists(NIVEL_0, digitalRead(NIVEL_PORT));

}

static void Amostrador(void *){
  uint32_t ulNotificationValue;
  const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 200 );
  while(1){
      // Notificação recebida da interrupção do temporizador
      ulNotificationValue = ulTaskNotifyTake(pdFALSE, xMaxBlockTime);
      if( ulNotificationValue == 1 ){

            if (flag) {
                /* leitura de tensão e corrente */
                I[i] = ganhoTC*(((analogRead(TCPin)*A)/ADCcounts)-offsetTC);
                V[i] = ganhoTP*(((analogRead(TPPin)*A)/ADCcounts)-offsetTP);
                
                i++;
           }
            // zera o contador quando é ultrapassado o valor maior que TAM
            if(i>TAM-1){
             i = 0;
             flag = false;
            }
      }
  }
}
/**
 * [calculaRMS Tarefa que calcula o RMS da corrente e tensão]
 * @param [name] [description]
 */
static void calculaRMS(void *) {

  while(1) {
   if (flag == false) {
    
      Irms = 0;
      for (size_t k = 0; k < TAM; k++) {
        Irms = Irms + I[k]*I[k];
      }

      Irms = Irms/TAM;
      Irms = sqrt(Irms);
     
      Vrms = 0;
      for (size_t k = 0; k < TAM; k++) {
        Vrms = Vrms + V[k]*V[k];
      
      }
      Vrms = Vrms/TAM;
      Vrms = sqrt(Vrms);
  
      flag = true;
      Serial.println("Valor Tensao RMS");
      Serial.println(Vrms);
      Serial.println("Valor Corrente RMS");
      Serial.println(Irms);
      
   }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }

}


// Função a ser chamada a ser executada  a cada periodo de amostragem
// dá notificação para a task sampler
void IRAM_ATTR onTimer() {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  vTaskNotifyGiveFromISR( samplerTaskHandle, &xHigherPriorityTaskWoken );
  portYIELD_FROM_ISR();
}


