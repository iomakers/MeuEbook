#include <Ultrasonic.h>
//conexão dos pinos para o sensor ultrasonico
#define PORTA_TRIGGER   GPIO_NUM_34
#define PORTA_ECHO      GPIO_NUM_35

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(PORTA_TRIGGER, PORTA_ECHO);
// declarar variável distancia do tipo inteiro sem sinal
float distancia;
static void leituraHCSR04(void *);
void setup()
{
    // Inicializa
    Serial.begin(115200);
    // declarar tarefa de leitura do sensor ultrasonico   
    xTaskCreate(&leituraHCSR04, "leituraHCSR04", 4096, NULL, 20, NULL);
}

void loop()
{
    Serial.println("Leitura do Sensor de Distancia usando FreeRTOS:");
    Serial.println(distancia);
    delay(500);        // printar no serial a cada 1 segundo
}

// Leitura do sensor de distancia a cada 1 segundo
static void leituraHCSR04(void *inpar){
  while (1) {
    ultrasonic.measure();
    distancia = ultrasonic.get_cm();
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }

}
