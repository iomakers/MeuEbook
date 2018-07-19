#include <Arduino.h>

#define TAM 128
#define ADCresolution 12
volatile unsigned int i = 0;
// Número de amostras coletadas
//#define ADC_CHANNEL    GPIO_NUM_25


const float A = 3.3;
float offsetTC = 1.45;
float offsetTP = 1.44;
float ganhoTC = 30;
float ganhoTP = 196;
float  ADCcounts;
volatile float I[TAM];
volatile float V[TAM];


float  Irms = 0;
float  Vrms = 0;
const int TCPin = GPIO_NUM_34;
const int TPPin = GPIO_NUM_35;
TaskHandle_t samplerTaskHandle = NULL;
/**
 * Configura os ADCs
 */
void initADC(){
    pinMode(TCPin, INPUT);
    pinMode(TPPin, INPUT);
    ADCcounts = pow(2, ADCresolution);
}

volatile bool flag = false;

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;


static void sampler(void *){
  uint32_t ulNotificationValue;
  const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 200 );
  while(1){
      ulNotificationValue = ulTaskNotifyTake(pdFALSE, xMaxBlockTime);
      if( ulNotificationValue == 1 ){

            if (flag) {
                /* leitura de tensão e corrente */
                I[i] = ganhoTC*(((analogRead(TCPin)*A)/ADCcounts)-offsetTC);
                V[i] = ganhoTP*(((analogRead(TPPin)*A)/ADCcounts)-offsetTP);
                //I[i] = analogRead(TCPin);
                i++;
           }
            // zera o contador quando é ultrapassado valor de 16
            if(i>TAM-1){
              i = 0;
             flag = false;
            }
      }
  }
}


/**
 * [calculateRMS Tarefa que calcula o RMS da corrente e tensão]
 * @param [name] [description]
 */
static void calculateRMS(void *) {

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
   }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

}
