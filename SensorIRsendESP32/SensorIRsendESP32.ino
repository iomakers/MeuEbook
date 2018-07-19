/*
Adaptado de https://github.com/SensorsIot/Definitive-Guide-to-IR/blob/master/IRMQTT_ESP32/IRMQTT_ESP32.ino

*/

#include <IRremote.h>

int RECV_PIN = GPIO_NUM_14;
int SEND_PIN = GPIO_NUM_5;


decode_results results;

IRrecv irrecv(RECV_PIN);
IRsend irsend(SEND_PIN);


int codeType = -1; 
unsigned long codeValue; 
unsigned int rawCodes[RAWBUF]; 
int codeLen; 
int toggle = 0; 


void storeCode(decode_results *results) {

  char buf[10];
  String cType = "";
  String IRcommand = "";


  codeType = results->decode_type;

  if (codeType == UNKNOWN) {
    Serial.println("Codigo desconhecido recebido, salvando como raw");
    codeLen = results->rawlen - 1;
   
    for (int i = 1; i <= codeLen; i++) {
      if (i % 2) {
        // Mark
        rawCodes[i - 1] = results->rawbuf[i] * USECPERTICK - MARK_EXCESS;
        Serial.print(" m");
      }
      else {
        // Space
        rawCodes[i - 1] = results->rawbuf[i] * USECPERTICK + MARK_EXCESS;
        Serial.print(" s");
      }
      Serial.print(rawCodes[i - 1], DEC);
    }
    Serial.println("");
  }
  else {
    if (codeType == NEC) {
      Serial.print("Recebido NEC: ");
      if (results->value == REPEAT) {
        
        Serial.println("ignorando.");
        return;
      } else cType = "NEC";
    }
    else if (codeType == SONY) {
      Serial.print("Recebido Sony: ");
      cType = "SON";
    }
    else if (codeType == PANASONIC) {
      Serial.print("Recebido PANASONIC: ");
      cType = "PAN";
    }
    else if (codeType == JVC) {
      Serial.print("Recebido JVC: ");
      cType = "JVC";
    }
    else if (codeType == RC5) {
      Serial.print("Recebido RC5: ");
      cType = "RC5";
    }
    else if (codeType == RC6) {
      Serial.print("Recebido RC6: ");
      cType = "RC6";
    }
    else {
      Serial.print("Codigo inesperado");
      Serial.print(codeType, DEC);
      Serial.println("");
      cType = "UNKNOWN";
    }
    codeValue = results->value;
    codeLen = results->bits;
    Serial.println(results->value, HEX);
    Serial.println(results->bits);
  }
}

void sendCode( int codeType, unsigned long codeValue, int codeLen) {
  if (codeType == NEC) {
    irsend.sendNEC(codeValue, codeLen);
    Serial.print("Sent NEC ");
    Serial.println(codeValue, HEX);
    Serial.println(codeLen);
  }
  else if (codeType == SONY) {
    irsend.sendSony(codeValue, codeLen);
    Serial.print("Sent Sony ");
    Serial.println(codeValue, HEX);
  }
  else if (codeType == PANASONIC) {
    irsend.sendPanasonic(codeValue, codeLen);
    Serial.print("Sent Panasonic");
    Serial.println(codeValue, HEX);
  }
  else if (codeType == JVC) {
    irsend.sendJVC(codeValue, codeLen, false);
    Serial.print("Sent JVC");
    Serial.println(codeValue, HEX);
  }
  else if (codeType == RC5 || codeType == RC6) {
    toggle = 1 - toggle;
    
    codeValue = codeValue & ~(1 << (codeLen - 1));
    codeValue = codeValue | (toggle << (codeLen - 1));
    if (codeType == RC5) {
      Serial.print("Sent RC5 ");
      Serial.println(codeValue, HEX);
      irsend.sendRC5(codeValue, codeLen);
    }
    else {
      irsend.sendRC6(codeValue, codeLen);
      Serial.print("Sent RC6 ");
      Serial.println(codeValue, HEX);
    }
  }
  else if (codeType == UNKNOWN /* i.e. raw */) {
    // Assume 38 KHz
    irsend.sendRaw(rawCodes, codeLen, 38);
    Serial.println("Sent raw");
  }
}

void setup()
{

  Serial.begin(115200);
  
  irrecv.enableIRIn(); // Iniciar o receptor

}

void loop() {
	
  if (irrecv.decode(&results)) { 
	// printa na serial os dados recebidos
    storeCode(&results);
    irrecv.resume(); 
  	// envia o código recebido
  	sendCode(results.decode_type, results.value, results.bits);
  }

}
