

#include "Wire.h"

#include "I2Cdev.h"
#include "ADXL345.h"


const float alpha = 0.2;

float fXg = 0;
float fYg = 0;
float fZg = 0;

int16_t Xg, Yg, Zg;
double dXg, dYg, dZg;

ADXL345 accel;

void setup()
{
 
  Wire.begin();
  accel.initialize();
  accel.setRange(ADXL345_RANGE_2G);
  accel.setRate(ADXL345_RATE_6P25);
  //accel.setFullResolution();
  Serial.begin(115200);
  delay(100);
}

void loop()
{
  
  accel.getAcceleration(&Xg, &Yg, &Zg);
  // dividir por 256.0 para transformar valores em bytes para decimal
  Serial.println("Xg:");
  Serial.println(Xg/256.0);
  Serial.println("Yg:");
  Serial.println(Yg/256.0);
  Serial.println("Zg:");
  Serial.println(Zg/256.0);


  //Filtro passa baixo
  fXg = (Xg/256.0) * alpha + (fXg * (1.0 - alpha));
  fYg = (Yg/256.0) * alpha + (fYg * (1.0 - alpha));
  fZg = (Zg/256.0) * alpha + (fZg * (1.0 - alpha));
  float pitch, roll;
  //Equações do Roll e PITCH
  roll = (atan2(-fYg, fZg)*180.0)/M_PI;
  pitch = (atan2(fXg, sqrt(fYg*fYg + fZg*fZg))*180.0)/M_PI;
  Serial.println("Pitch:");
  Serial.println(pitch);
  Serial.println("Roll:");
  Serial.println(roll);
  
  delay(250);
}
