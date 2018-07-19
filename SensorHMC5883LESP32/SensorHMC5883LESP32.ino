

#include "Wire.h"

#include "I2Cdev.h"
#include "HMC5883L.h"
// declarar instancia do magnetometro no endereço padrão 0x1E
HMC5883L mag;

int16_t mx, my, mz;

void setup()
{
 
  Wire.begin();
  mag.initialize();
  Serial.begin(115200);
  delay(100);
}

void loop()
{
 // realizar leitura do magnetometro
    mag.getHeading(&mx, &mx, &mz);

    // Printar leitura do magnetometo
    Serial.println("Magnetometro:");
    Serial.print("Eixo X: ");
    Serial.println(mx); 
    Serial.print("Eixo Y: ");
    Serial.println(mx); 
    Serial.print("Eixo Z: ");
    Serial.println(mz);
    
    // Transformar valores em graus. Valor 0 indica polo norte
    float sentido = atan2(my, mx);
    if(sentido < 0)
      sentido += 2 * M_PI;
    Serial.print("Sentido:\t");
    Serial.println(sentido * 180/M_PI);
  
  delay(250);
}
