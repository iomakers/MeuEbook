
#include "DHT11_ESP32.h"
//cria uma  instancia DHT11
DHT11_ESP32 DHT(GPIO_NUM_4);

void setup()
{
  Serial.begin(115200);

}


void loop()
{
    DHT.errorCode = DHT.sampleData();
    if(DHT.errorCode){
      Serial.println("Leitura de Temperatura:");
      Serial.prinln( DHT.temperature);
      Serial.println("Leitura de Humidade:");
      Serial.prinln( DHT.humidity);
    }else{
      Serial.println("Erro no sensor de temperatura e humidade");
    }

    delay(1000);        // delay in between reads for stability
}
