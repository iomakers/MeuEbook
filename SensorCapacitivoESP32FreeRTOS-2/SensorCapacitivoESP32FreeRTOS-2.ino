/**
 * Sensor Capacitivo Esp32 com interrupção
 *
 */

int limite = 100;
bool tocado = false;
// definir protótipo da função
void foiTocado();

void setup() {

  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  touchAttachInterrupt(T0, foiTocado, limite);
}

void loop() {
  
  if(tocado){
      Serial.println("Voce tocou no pino: ");
      Serial.print(T0);
      tocado = false;
  }
}

void foiTocado(){
  tocado = true;
}
