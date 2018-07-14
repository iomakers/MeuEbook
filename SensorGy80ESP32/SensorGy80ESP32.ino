/**
 * References:
 * https://github.com/muggn/GY80
 */

#include <Wire.h>
#include <GY80.h>
//cria uma GY80 instancia
GY80 sensor = GY80();

void setup()
{
    // Inicializa
    Serial.begin(115200);
    sensor.begin();       //inicializa sensor
}


void loop()
{
    GY80_scaled val = sensor.read_scaled();       //obtem valores de todos os sensores
    // print na serial todos os valores

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


    delay(250);        // delay in between reads for stability
}
