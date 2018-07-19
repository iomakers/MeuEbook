#include "DHT11_ESP32.h"
//cria uma  instancia DHT11
DHT11_ESP32 DHT(GPIO_NUM_4);

void setup()
{
    // Inicializa Serial
    Serial.begin(115200);

    xTaskCreate(&leituraDHT11, "leituraDHT11", 4096, NULL, 20, NULL);
}


void loop()
{

    if(DHT.errorCode){
      Serial.println("Leitura de Temperatura:");
      Serial.println( DHT.temperature);
      Serial.println("Leitura de Humidade:");
      Serial.println( DHT.humidity);
    }else{
      Serial.println("Erro no sensor de temperatura e humidade");
    }


    delay(1000);        // printar no serial a cada 1 segundo
}

// Leitura do DHT11 a cada 2 segundos
static void leituraDHT11(void * inpar){
  while (1) {
    DHT.errorCode = DHT.sampleData();
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }

}
