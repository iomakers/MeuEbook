

#include "Wire.h"

#include "I2Cdev.h"
#include "BMP085.h"

// declarar instância no endereço padrão em 0x77
BMP085 barometer;

float temperatura;
float pressao;
int32_t altitude;

// declarar protótipo da tarefa que irá realizar leitura do sensor barometro
static void leituraBarometro(void * );
void setup()
{
  Wire.begin();
  barometer.initialize();
  Serial.begin(115200);
 // declarar tarefa de leitura do barometro
  xTaskCreate(leituraBarometro, "leituraBarometro", 4096,   NULL, 1, NULL);
  
  delay(100);
}

void loop()
{



}

// Tarefa da leitura do sensor barômetro
static void leituraBarometro(void *){

  while(1){
     // Coloca barometro no modo de temperatura
    barometer.setControl(BMP085_MODE_TEMPERATURE);
    
    //realizar leitura de temperatura em Celsius
    temperatura = barometer.getTemperatureC();

    // Coloca em modo leitura de pressão
    barometer.setControl(BMP085_MODE_PRESSURE_3);

    // realiza leitura da pressão em Pascais (Pa)
    pressao = barometer.getPressure();

    // Calcula valor da altitude baseado na leitura de pressão
    altitude = barometer.getAltitude(pressao);

     // Printar leituras do barômetro
    Serial.println("Barometro");
    Serial.print("Temperatura: ");Serial.print(temperatura); Serial.println(" Cº");
    Serial.print("Pressao: ");Serial.print(pressao); Serial.println(" Pa");
    Serial.print("Altitude: "); Serial.print(altitude); Serial.println(" m");
  
    //delay(500);
	     
     // realizar um delay e inicializar leitura daqui a 200 ms
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

