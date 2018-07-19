/**
 * Este exemplo mostra como criar um servidor que envia dados via Json para qualquer api que quiser poder consumir.
 *
 *
 * autor: João Campos
 */
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "Wire.h"
#include <ArduinoJson.h>
#include "I2Cdev.h"
#include <L3G4200D.h>
#include "HMC5883L.h"
#include "BMP085.h"
#include "ADXL345.h"



const char *ssid = "MS NET";
const char *password = "internet2018";

WebServer server(80);
 // criar instancia do giroscopio
 L3G4200D gyro;

 int16_t avx, avy, avz;

 // declarar instancia do magnetometro no endereço padrão 0x1E
 HMC5883L mag;

 int16_t mx, my, mz;

 // declarar instancia no endereço padrão em 0x77
 BMP085 barometer;

 float temperatura;
 float pressao;
 int32_t altitude;

 ADXL345 accel;

 const float alpha = 0.5;

 float fXg = 0;
 float fYg = 0;
 float fZg = 0;

 int16_t Xg, Yg, Zg;

 float pitch, roll;

char JSONmessageBuffer[200];

static void leituraMag(void *);
static void leituraGyro(void * );
static void leituraBarometro(void *);
static void leituraAcel(void * );
static void updateJSON(void * );
void sendJSON();

 SemaphoreHandle_t xSemaphore = NULL;

void setup()
 {
   Serial.begin(115200);
   Wire.begin();
   gyro.initialize();
   gyro.setFullScale(2000);
   mag.initialize();
   barometer.initialize();
   accel.initialize();
   accel.setRange(ADXL345_RANGE_2G);
   accel.setRate(ADXL345_RATE_6P25);
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
   if (MDNS.begin("esp32")) {
      Serial.println("MDNS responder started");
    }

  server.on("/", sendJSON);
  server.begin();

  
   delay(100);
   xTaskCreatePinnedToCore(leituraGyro, "leituraGyro", 4096,   NULL, 1, NULL, 1);
   //xTaskCreatePinnedToCore(leituraMag, "leituraMag", 4096,   NULL, 2, NULL, 1);
   //xTaskCreatePinnedToCore(leituraBarometro, "leituraBarometro", 4096,   NULL, 3, NULL, 1);
   //xTaskCreatePinnedToCore(leituraAcel, "leituraAcel", 4096,   NULL, 1, NULL, 1);
   xTaskCreatePinnedToCore(updateJSON, "updateJSON", 4096,   NULL, 1, NULL,1);
   
}

void loop()
{
  server.handleClient();
}

void sendJSON() {
  server.send(200, "application/json", JSONmessageBuffer);
}



// Tarefa que atualiza json
static void updateJSON(void *){
  while(1){
 // criar Json dos dados
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();
  JsonArray& dataGYRO =  JSONencoder.createNestedArray("GYRO");
  JsonArray& dataACCEL = JSONencoder.createNestedArray("ACCEL");
  JsonArray& dataBAROM = JSONencoder.createNestedArray("BAR");
  JsonArray& dataMAG =   JSONencoder.createNestedArray("MAG");
  JSONencoder["device"] = "ESP32";
  JSONencoder["timestamp"] = "ESP32";
  dataGYRO.add(avx);
  dataGYRO.add(avy);
  dataGYRO.add(avz);
  dataACCEL.add(fXg);
  dataACCEL.add(fYg);
  dataACCEL.add(fZg);
  dataBAROM.add(temperatura);
  dataBAROM.add(pressao);
  dataMAG.add(mx);
  dataMAG.add(my);
  dataMAG.add(mz);
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
     // realizar um delay e inicializar leitura daqui a 500 ms
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}


 // Tarefa da leitura do sensor Gyro
static void leituraGyro(void *){

   while(1){
      // realizar leitura do sensor de gyro
   
       gyro.getAngularVelocity(&avx, &avy, &avz);
       
       
       
       vTaskDelay(250 / portTICK_PERIOD_MS);
   }
}


 // Tarefa da leitura do sensor magnetometro
static void leituraMag(void *){
   while(1){

    
  	// realizar leitura do magnetometro
    	mag.getHeading(&mx, &my, &mz);
     
      // realizar um delay e inicializar leitura daqui a 50 ms
     vTaskDelay(200 / portTICK_PERIOD_MS);
   }
}

 // Tarefa da leitura do sensor barometro
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
    
      // realizar um delay e inicializar leitura daqui a 50 ms
     vTaskDelay(200 / portTICK_PERIOD_MS);
   }
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
      vTaskDelay(200 / portTICK_PERIOD_MS);
   }
}
