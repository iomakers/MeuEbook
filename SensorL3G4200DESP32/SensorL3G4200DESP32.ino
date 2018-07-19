

#include "Wire.h"

#include "I2Cdev.h"
#include <L3G4200D.h>

// criar instancia do giroscopio
L3G4200D gyro;

int16_t avx, avy, avz;

void setup()
{
  Wire.begin();
  gyro.initialize();
  gyro.setFullScale(2000);
  Serial.begin(115200);
  delay(100);
}

void loop()
{
  //Realiza leitura da velocidade angular 
  gyro.getAngularVelocity(&avx, &avy, &avz);

  Serial.println("Velocidade Angular:");
  Serial.print("Eixo X: ");
  Serial.println(avx/256.0); 
  Serial.print("Eixo Y: ");
  Serial.println(avy/256.0); 
  Serial.print("Eixo Z: ");
  Serial.println(avz/256.0);
  
  delay(250);
}
