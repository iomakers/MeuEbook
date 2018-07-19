

#include "Wire.h"

#include "I2Cdev.h"
#include "BMP085.h"

// declarar instância no endereço padrão em 0x77
BMP085 barometer;

float temperatura;
float pressao;
int32_t altitude;



void setup()
{
 
  Wire.begin();
  barometer.initialize();
  Serial.begin(115200);
  delay(100);
}

void loop()
{

  // Coloca barômetro no modo de temperatura
    barometer.setControl(BMP085_MODE_TEMPERATURE);
    
    //realizar leitura de temperatura em Celsius
    temperatura = barometer.getTemperatureC();

    // Coloca em modo leitura de pressão
    barometer.setControl(BMP085_MODE_PRESSURE_3);

    // realiza leitura da pressão em Pascais (Pa)
    pressao = barometer.getPressure();

    // Calcula valor da altitude baseado na leitura de pressão
    altitude = barometer.getAltitude(pressao);

    // Printar leituras do barametro
    Serial.println("Barametro");
    Serial.print("Temperatura: ");Serial.println(temperatura); 
    Serial.print("Pressao: ");Serial.println(pressao); 
    Serial.print("Altitude: "); Serial.println(altitude);
  
    delay(250);
}
