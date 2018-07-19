

#include "Wire.h"

#include "I2Cdev.h"
#include "HMC5883L.h"
// declarar instancia do magnetometro no endereço padrão 0x1E
HMC5883L mag;

int16_t mx, my, mz;

static void leituraMag(void *);

void setup()
{ 
  Wire.begin();
  mag.initialize();
  Serial.begin(115200);
   // declarar tarefa de leitura do Magnetomentro
  xTaskCreate(leituraMag, "leituraMag", 4096,   NULL, 1, NULL);
  delay(100);
}

void loop()
{
 

    // Printar leitura do magnetomento
    Serial.println("Magnetomentro:");
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
  
  delay(500);
}

// Tarefa da leitura do sensor magnetometro
static void leituraMag(void *){
  while(1){
	// realizar leitura do magnetometro
	mag.getHeading(&mx, &mx, &mz);
	     
     // realizar um delay e inicializar leitura daqui a 50 ms
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

