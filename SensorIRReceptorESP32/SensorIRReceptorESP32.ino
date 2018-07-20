#include <IRremote.h>
 // define porta do Receptor
int RECV_PIN = GPIO_NUM_14;
 
IRrecv irrecv(RECV_PIN);
 
decode_results results;

void setup()
{
	Serial.begin(115200);
	// inicia o receptor
	irrecv.enableIRIn(); 
	
}
 
void loop()
{
   // Decodifica o sinal infravermelho recebido
	if (irrecv.decode(&results))
	{
		Serial.println(results.value, HEX);
		irrecv.resume();
	} 
}

