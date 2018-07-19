#include <ZSharpIR.h> // Incluir biblioteca ZSharp

// Para o modelo GP2Y0A02Y o valor é 20150
#define modelo 20150

// definir porta de leitura do sensor Sharp
const int portaIR = GPIO_NUM_35;

// criar instância ZSharp
ZSharpIR sharp(portaIR, modelo);

void setup() {
  // inicializar serial
  Serial.begin(115200);
  // definir tensão interna de 3300
  sharp.setARefVoltage(3300);
  // definir resolução como 12
  sharp.SetAnalogReadResolution(12);
}

void loop() {
  // realizar leitura do sensor de distância
  int leitura= sharp.distance();
  // Realizar o print da leitura no serial
  Serial.println("Leitura do Sensor de Distancia Sharp:");
  Serial.println(leitura);
  // realizar um delay e inicializar leitura daqui a 2 segundos
  delay(2000);

}
