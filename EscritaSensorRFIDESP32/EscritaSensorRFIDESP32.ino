#include <mfrc522.h> //biblioteca responsável pela comunicação com o módulo RFID-RC522
#include <SPI.h> //biblioteca para comunicação do barramento SPI

#define SS_PIN    21
#define RST_PIN   22

#define SIZE_BUFFER     18
#define MAX_SIZE_BLOCK  16

//esse objeto key ('chave') é utilizado para autenticação
MFRC522::MIFARE_Key key;
//código de status de retorno da autenticação
MFRC522::StatusCode status;

// Definições pino módulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  // Inicia a serial
  Serial.begin(9600);
  SPI.begin(); // Inicia barramento SPI
  // Inicia MFRC522
  mfrc522.PCD_Init();
  // Mensagens iniciais no serial monitor
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();

}

void loop()
{
   // Aguarda a aproximacao do cartao
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Seleciona um dos cartoes
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

 // Grava dados no RFID
  gravarDados();
 
  // instrui o PICC quando no estado ACTIVE a ir para um estado de "parada"
  mfrc522.PICC_HaltA();
  // "stop" a encriptação do PCD, deve ser chamado após a comunicação com autenticação, caso contrário novas comunicações não poderão ser iniciadas
  mfrc522.PCD_StopCrypto1();
}



//faz a gravação dos dados no cartão/tag
void gravarDados()
{
  //imprime os detalhes tecnicos do cartão/tag
  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));
  // aguarda 30 segundos para entrada de dados via Serial
  Serial.setTimeout(30000L) ;
  Serial.println(F("Insira os dados a serem gravados com o caractere '$' ao final\n[máximo de 16 caracteres]:"));

  //Prepara a chave - todas as chaves estão configuradas para FFFFFFFFFFFFh (Padrão de fábrica).
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //buffer para armazenamento dos dados que iremos gravar
  byte buffer[MAX_SIZE_BLOCK] = "";
  byte bloco; //bloco que desejamos realizar a operação
  byte tamanhoDados; //tamanho dos dados que vamos operar (em bytes)

  //recupera no buffer os dados que o usuário inserir pela serial
  //serão todos os dados anteriores ao caractere '$'
  tamanhoDados = Serial.readBytesUntil('$', (char*)buffer, MAX_SIZE_BLOCK);
  //espaços que sobrarem do buffer são preenchidos com espaço em branco
  for(byte i=tamanhoDados; i < MAX_SIZE_BLOCK; i++)
  {
    buffer[i] = ' ';
  }

  bloco = 1; //bloco definido para operação
  String str = (char*)buffer; //transforma os dados em string para imprimir
  Serial.println(str);

  //Authenticate é um comando para autenticação para habilitar uma comunicação segura
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,
                                    bloco, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Autenticacao Falhou: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }


  //Grava no bloco
  status = mfrc522.MIFARE_Write(bloco, buffer, MAX_SIZE_BLOCK);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() Falhou: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else{
    Serial.println(F("MIFARE_Write() Sucesso: "));

  }

}
