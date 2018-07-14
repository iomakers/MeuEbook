/**
 * Referencias:
 * https://github.com/muggn/GY80
 */

#include <Wire.h>
#include <GY80.h>
//cria uma GY80 instancia
GY80 sensor = GY80();
GY80_scaled val;
void setup()
{
    // Inicializa
    Serial.begin(115200);
    sensor.begin();       //inicializa sensor
    xTaskCreate(&leituraGY80, "leituraGY80", 4096, NULL, 20, NULL);
}


void loop()
{


    Serial.print("Mag:");                         //magnetometer values
    Serial.print(val.m_x,2);
    Serial.print(',');
    Serial.print(val.m_y,2);
    Serial.print(',');
    Serial.print(val.m_z,2);
    Serial.print(' ');
    Serial.print("Acc:");                         //accelerometer values
    Serial.print(val.a_x,3);
    Serial.print(',');
    Serial.print(val.a_y,3);
    Serial.print(',');
    Serial.print(val.a_z,3);
    Serial.print(' ');
    Serial.print("Gyro:");                        //gyroscope values
    Serial.print(val.g_x,1);
    Serial.print(',');
    Serial.print(val.g_y,1);
    Serial.print(',');
    Serial.print(val.g_z,1);
    Serial.print(' ');
    Serial.print("P:");                           //pressure values
    Serial.print(val.p,5);
    Serial.print(' ');
    Serial.print("T:");                           //temperature values
    Serial.println(val.t,1);


    delay(1000);        // printar no serial a cada 1 segundo
}

// Leitura do GY80 a cada 250 ms
static void leituraGY80(){
  while (1) {
    val = sensor.read_scaled();
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }

}
