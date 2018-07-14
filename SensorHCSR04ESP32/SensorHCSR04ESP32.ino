
#include <UltraEsp32.h>

double  distancia  = 0;
//cria uma  instancia do sensor de distancia
UltraEsp32 ultra(GPIO_NUM_22, GPIO_NUM_23);

void setup()
{
    // Inicializa
    Serial.begin(115200);
}


void loop()
{
    double  distancia  =  ultra.ultrassonicRead();
    Serial.println("Leitura do Sensor de Distancia:");
    Serial.println(distancia);
    delay(1000);
}
