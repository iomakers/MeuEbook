

#include "Wire.h"

#include "I2Cdev.h"
#include "ADXL345.h"


const float alpha = 0.5;

float fXg = 0;
float fYg = 0;
float fZg = 0;

int16_t Xg, Yg, Zg;

float pitch, roll;
  
ADXL345 accel;
// declarar protótipo da tarefa que irá realizar leitura do sensor acelerometro
static void leituraAcel(void * );
void setup()
{
 
  Wire.begin();
  accel.initialize();
  accel.setRange(ADXL345_RANGE_2G);
  accel.setRate(ADXL345_RATE_6P25);
  //accel.setFullResolution();
  Serial.begin(115200);
  // declarar tarefa de leitura do acelerametro
  xTaskCreate(leituraAcel, "leituraAcel", 4096,   NULL, 1, NULL);
  delay(100);
}

void loop()
{
  
 
  // dividir por 256.0 para transformar valores em bytes para decimal
  Serial.println("Xg:");
  Serial.println(Xg/256.0);
  Serial.println("Yg:");
  Serial.println(Yg/256.0);
  Serial.println("Zg:");
  Serial.println(Zg/256.0);

  Serial.println("Pitch:");
  Serial.println(pitch);
  Serial.println("Roll:");
  Serial.println(roll);
  // Printar na serial a cada 500 ms
  delay(500);
}


// Tarefa da leitura do sensor acelerametro
static void leituraAcel(void *){

  while(1){
     // Realizar leitura do sensor acelerametro
       accel.getAcceleration(&Xg, &Yg, &Zg);
     // Filtro passa baixo
	  fXg = (Xg/256.0) * alpha + (fXg * (1.0 - alpha));
	  fYg = (Yg/256.0) * alpha + (fYg * (1.0 - alpha));
	  fZg = (Zg/256.0) * alpha + (fZg * (1.0 - alpha));

	  // Equações do Roll e PITCH
	  roll = (atan2(-fYg, fZg)*180.0)/M_PI;
	  pitch = (atan2(fXg, sqrt(fYg*fYg + fZg*fZg))*180.0)/M_PI;
	   
	   
      // realizar um delay e inicializar leitura daqui a 50 ms
      vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}


