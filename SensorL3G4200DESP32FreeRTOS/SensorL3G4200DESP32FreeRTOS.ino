

#include "Wire.h"

#include "I2Cdev.h"
#include <L3G4200D.h>

// criar instancia do giroscopio
L3G4200D gyro;

int16_t avx, avy, avz;
static void leituraGyro(void * );

void setup()
{
  Wire.begin();
  gyro.initialize();
  gyro.setFullScale(2000);
  Serial.begin(115200);
  delay(100);
  xTaskCreate(leituraGyro, "leituraGyro", 4096,   NULL, 1, NULL);
}

void loop()
{

  Serial.println("Velocidade Angular:");
  Serial.print("Eixo X: ");
  Serial.println(avx/256.0); 
  Serial.print("Eixo Y: ");
  Serial.println(avy/256.0); 
  Serial.print("Eixo Z: ");
  Serial.println(avz/256.0);
  // Printar a cada 1 segundo
  delay(1000);
}

// Tarefa da leitura do sensor Gyro
static void leituraGyro(void *){

  while(1){
     // realizar leitura do sensor de gyro
      gyro.getAngularVelocity(&avx, &avy, &avz);
      // realizar um delay e inicializar leitura daqui a 250 ms
      vTaskDelay(250 / portTICK_PERIOD_MS);
  }
}
