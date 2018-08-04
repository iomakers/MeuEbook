/**
 * Sensor Capacitivo Esp32
 *
 */

void setup() {

  Serial.begin(115200);
  delay(1000); 
}
void loop() {


  Serial.println("Leitura Capacitiva: ");
  Serial.println(touchRead(T0));   

  
  delay(1000);
}
