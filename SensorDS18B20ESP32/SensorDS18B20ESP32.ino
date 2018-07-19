
#include <OneWire.h>
#include <DallasTemperature.h>

// Definir a porta do Esp32
#define ONE_WIRE_BUS GPIO_NUM_32

// Definir uma instância One Wire
OneWire oneWire(ONE_WIRE_BUS);

// Passar a instância One para o sensor dallas. 
DallasTemperature sensors(&oneWire);

/*
 * Inicializar os sensores DALLAS
 */
void setup(void)
{
 
  Serial.begin(115200);
 
  // Inicializa os sensores
  sensors.begin();
}


void loop(void)
{ 
  // Requisitar todos os sensores no barramento
  Serial.print("Requisitando as temperaturas...");
  sensors.requestTemperatures(); 
  Serial.println("Completo");
 
  Serial.print("Temperatura do dispositivo com indice 0: ");
  // escolhe o sensor com indice 0 para printar os dados da temperatura
  Serial.println(sensors.getTempCByIndex(0));  
  // realizar leitura a cada 1 segundo
  delay(1000);
}
