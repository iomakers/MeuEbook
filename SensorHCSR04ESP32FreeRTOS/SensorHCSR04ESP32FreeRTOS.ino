#include <UltraEsp32.h>
//cria uma  instancia do sensor de distancia
UltraEsp32 ultra(GPIO_NUM_22, GPIO_NUM_23);
static void leituraHCSR04(void *);
void setup()
{
    // Inicializa
    Serial.begin(115200);
    sensor.begin();       //inicializa sensor
    xTaskCreate(&leituraHCSR04, "leituraHCSR04", 4096, NULL, 20, NULL);
}


void loop()
{
    Serial.println("Leitura do Sensor de Distancia:");
    Serial.println(distancia);
    delay(1000);        // printar no serial a cada 1 segundo
}

// Leitura do sensor de distancia a cada 1 segundo
static void leituraHCSR04(void *inpar){
  while (1) {
    distancia  =  ultra.ultrassonicRead();
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }

}
