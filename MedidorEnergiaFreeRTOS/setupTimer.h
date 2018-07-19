#include <Arduino.h>
#include "setupADC.h"




// Função a ser chamada a ser executada  a cada periodo de amostragem
// dá notificação para a task sampler
void IRAM_ATTR onTimer() {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  vTaskNotifyGiveFromISR( samplerTaskHandle, &xHigherPriorityTaskWoken );
  portYIELD_FROM_ISR();
}


/**
 * Inicializa função timer
 */
void initTimer(){
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1041, true);
  timerAlarmEnable(timer);

  xTaskCreatePinnedToCore(&sampler, "sampler", 4096, NULL, 1000, &samplerTaskHandle, 0);
  xTaskCreatePinnedToCore(&calculateRMS, "calculateRMS", 4096, NULL, 0, NULL, 0);
}
