
#include <OneWire.h>
#include <DallasTemperature.h>

// Definir a porta do Esp32
#define ONE_WIRE_BUS GPIO_NUM_32

// Definir uma instância One Wire
OneWire oneWire(ONE_WIRE_BUS);

// Passar a instância One para o sensor dallas. 
DallasTemperature sensors(&oneWire);
// declarar protótipo da tarefa que irá realizar leitura do sensor de temperatura
static void leituraSensorTemperatura(void * );
/*
 * Inicializar os sensores DALLAS
 */
void setup(void)
{
 
  Serial.begin(115200);
 
  // Inicializa os sensores
  sensors.begin();
  xTaskCreate(leituraSensorTemperatura, "leituraSensorTemperatura", 4096,   NULL, 1, NULL);
}


void loop(void)
{ 
  
}

// Tarefa do sensor Temperatura
static void leituraSensorTemperatura(void *){

  while(1){
	// Requisitar todos os sensores no barramento
	  Serial.print("Requisitando as temperaturas...");
	  sensors.requestTemperatures(); 
	  Serial.println("Completo");
	 
	  Serial.print("Temperatura do dispositivo com indice 0 com FreeRTOS: ");
	  // escolhe o sensor com indice 0 para printar os dados da temperatura
	  Serial.println(sensors.getTempCByIndex(0));  
      vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

