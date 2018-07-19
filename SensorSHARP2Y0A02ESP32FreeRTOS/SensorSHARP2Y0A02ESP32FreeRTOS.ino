#include <ZSharpIR.h> // Incluir biblioteca ZSharp

// Para o modelo GP2Y0A02Y o valor é 20150
#define modelo 20150

// definir porta de leitura do sensor Sharp
const int portaIR = GPIO_NUM_35;

// criar instância ZSharp
ZSharpIR sharp(portaIR, modelo);

// declarar protótipo da tarefa que irá realizar leitura do sensor de chuva
static void leituraSensorSharp(void * );
void setup() {
  // inicializar serial
  Serial.begin(115200);
  // declarar tarefa que irá realizar a leitura do sensor de chuva
  xTaskCreate(leituraSensorSharp, "leituraSensorSharp", 4096,   NULL, 1, NULL);
// definir tensão interna de 3300
  sharp.setARefVoltage(3300);
  // definir resolução como 12
  sharp.SetAnalogReadResolution(12);

}

void loop() {

}
// Tarefa do sensor sharp
static void leituraSensorSharp(void *){

  while(1){
		  // realizar leitura do sensor de distância
	  int leitura= sharp.distance();
	  // Realizar o print da leitura no serial
	  Serial.println("Leitura do Sensor de Distancia Sharp usando FreeRTOS:");
	  Serial.println(leitura);
      // realizar um delay e inicializar leitura daqui a 1 segundos
      vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
