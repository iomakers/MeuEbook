// Definir porta do Buzzer
const int  PORTA_BUZZER = GPIO_NUM_17;
// Definir frequência de 1 kHZ
int freq = 1000;
int  resolucao = 8;
int  canalBuzzer = 0;
// Valor de 8 bits que vai de 0 a 255
uint8_t valorBuzzer = 0;
// Usaremos rotina LEDC para ligar o buzzer
void setup() {
	
  ledcSetup(canalBuzzer, freq, resolucao);
  ledcAttachPin(PORTA_BUZZER, canalBuzzer);

}

void loop() {
	// Com resolução de 8 Bits resulta valores de escrita entre 0 e 255
   ledcWrite(canalBuzzer, valorBuzzer);
   valorBuzzer ++;
   delay(100);
   
}
