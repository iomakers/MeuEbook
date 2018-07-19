#include <IRremote.h>
 
int RECV_PIN = 15;
 
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
		if (irrecv.decode(&results))
		{
			Serial.println(results.value, HEX);
			irrecv.resume();
		}
}