#include <IRremote.h>
 // define porta do Receptor
int RECV_PIN = GPIO_NUM_14;
 
IRrecv irrecv(RECV_PIN);
 
decode_results results;
 static void receptorIR(void * );
void setup()
{
	Serial.begin(115200);
	// inicia o receptor
	irrecv.enableIRIn(); 
	xTaskCreate(receptorIR, "receptorIR", 4096,   NULL, 1, NULL);
}
 
void loop()
{
	    
}

// Tarefa do receptor
static void receptorIR(void *){

  while(1){
      // Decodifica o sinal infravermelho recebido
		if (irrecv.decode(&results))
		{
			Serial.println(results.value, HEX);
			irrecv.resume();
		}
      // realizar um delay e inicializar leitura daqui a 50 ms
      vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}
