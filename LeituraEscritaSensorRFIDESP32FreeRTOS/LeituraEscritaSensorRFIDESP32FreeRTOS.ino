#include <MFRC522.h> //biblioteca responsável pela comunicação com o módulo RFID-RC522
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
byte dadosGravar[25];
TaskHandle_t referenciaLeituraDados = NULL;
TaskHandle_t referenciaGravarDados = NULL;
// declarar protótipos das tarefas
static void  gravarDados(void *);
static void leituraDados(void *);
static void  menu(void *);
static void  leDadosSerial(void *);
// implementar máquina de estados
uint8_t estado = 0;
void setup() {
  // Inicia a serial
  Serial.begin(115200);
  SPI.begin(); // Inicia barramento SPI
  // Inicia MFRC522
  mfrc522.PCD_Init();
  // Mensagens iniciais no serial monitor
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();

  xTaskCreate(&gravarDados, "gravarDados", 4096, NULL, 0, &referenciaGravarDados);
  xTaskCreate(&menu, "menu", 4096, NULL, 0, NULL);
  xTaskCreate(&leDadosSerial, "leDadosSerial", 4096, NULL, 0, NULL);
}

void loop()
{


}

/*
estado = 0 -- printa o menu
estado = 1 -- Fica na espera de dados
estado = 2 -- Realiza leitura e fica no estado até pressionar enter
estado = 3 -- Printa menu de introduzir caracteres
estado = 4 -- Realiza leitura dos dados e espera que usuário pressiona enter para a tarefa ser notificada
estado = 5 -- Printa gravando dados
 */


static void  menu(void *){

  while(1){
    // Printa o menu uma vez
    if(estado == 0){
      Serial.println(F("\nEscolha uma opção:"));
      Serial.println(F("0 - Leitura de Dados"));
      Serial.println(F("1 - Gravação de Dados\n"));
      estado = 1;
     
    }
    if(estado == 2){
      Serial.println(F("\n Lendo Dados:"));
      Serial.println(F("\n Pressione enter para voltar ao menu:"));
    }


    if(estado == 3){
      Serial.println(F("\nIntroduza caracteres ate no maximo de 18 de comprimento:"));
      Serial.println(F("Pressiona & para terminar "));
      estado = 4;
      //Serial.println(F("Prima ESC para Voltar MENU INICIAL\n"));
    }
    if(estado == 5){
      Serial.println(F("\nGravando Dados:"));
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

}

static void leDadosSerial(void *){
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  int  ind = 0;
  while(1){

    if(estado == 1){
      while(Serial.available() && (estado == 1)) {

          char op = Serial.read();
        
          if(op == '\n'){
             estado = 0;
          }    
          if(op == 48){
            estado = 2;
            xTaskCreate(&leituraDados, "LeituraDados", 4096, NULL, 1000, &referenciaLeituraDados);
          }
          if(op == 49){
            // estado printar gravar dados
            estado = 3;
            // zerar o indice
            ind = 0;
            // zera os dados sempre em cada iteração
            for (size_t i = 0; i < 19; i++) {
               dadosGravar[i] = ' ';
            }
          }
          Serial.println((int)op);
          Serial.println(estado);
      }
    }
    // Se pressionado enter deleta tarefa de leitura de dados
    if(estado == 2){
          while(Serial.available() && (estado == 2)) {
              if(Serial.read() == '\n'){
                estado = 0;
                vTaskDelete(referenciaLeituraDados);
              };
          }
    }

  // Se pressionado enter notifica tarefa para gravar dados
  // se dados maior que o buffer para de gravar
    if(estado == 4)
      while(Serial.available() && (estado == 4)) {
            char dado = Serial.read();   
            if(dado == '&'){
             xTaskNotifyGive(referenciaGravarDados);
             estado = 5;
             portYIELD();
            };
            if(ind<19){
              dadosGravar[ind] = (byte)dado;
              ind ++;
            }
             Serial.println((char*)dadosGravar);  
        }



    // executa  a cada 50 ms a leitura do serial
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}


//faz a gravação dos dados no cartão/tag
static void  gravarDados(void *)
{
  uint32_t ulNotificationValue;
  const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 200 );
  while(1){
          ulNotificationValue = ulTaskNotifyTake(pdFALSE, xMaxBlockTime);
          if( ulNotificationValue == 1 ){
            Serial.println(F("Tarefa gravar dados em execucao:"));
          
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
          //imprime os detalhes tecnicos do cartão/tag
          mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));
          
          

          //Prepara a chave - todas as chaves estão configuradas para FFFFFFFFFFFFh (Padrão de fábrica).
          for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

        
          byte bloco = 1; //bloco definido para operação
          String str = (char*)dadosGravar; //transforma os dados em string para imprimir
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
          status = mfrc522.MIFARE_Write(bloco, dadosGravar, MAX_SIZE_BLOCK);
          if (status != MFRC522::STATUS_OK) {
            Serial.print(F("MIFARE_Write() Falhou: "));
            Serial.println(mfrc522.GetStatusCodeName(status));
            return;
          }
          else{
            Serial.println(F("MIFARE_Write() Sucesso: "));
          }
            // instrui o PICC quando no estado ACTIVE a ir para um estado de "parada"
            mfrc522.PICC_HaltA();
            // "stop" a encriptação do PCD, deve ser chamado após a comunicação com autenticação, caso contrário novas comunicações não poderão ser iniciadas
            mfrc522.PCD_StopCrypto1();
            estado = 0;
          }
      }
}


static void leituraDados(void *){
  uint32_t ulNotificationValue;
  const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 200 );
  while(1){
    Serial.println(F("Tarefa ler dados em execucao:"));
      		  // só atualiza o vetor quando o mutex é dado pela função calcula rms
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
           //imprime os detalhes técnicos do cartão/tag
           mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));

           //Prepara a chave - todas as chaves estão configuradas para FFFFFFFFFFFFh (Padrão de fábrica).
           for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

           //bloco que faremos a operação
           byte bloco = 1;
           byte tamanho = SIZE_BUFFER;
            //buffer para colocar os dados lidos
           byte buffer[SIZE_BUFFER] = {0};

           //faz a autenticação do bloco que vamos operar
           status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, bloco, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
           if (status != MFRC522::STATUS_OK) {
             Serial.print(F("Autenticacao Falhou: "));
             Serial.println(mfrc522.GetStatusCodeName(status));
             return;
           }
           //faz a leitura dos dados do bloco
           status = mfrc522.MIFARE_Read(bloco, buffer, &tamanho);
           if (status != MFRC522::STATUS_OK) {
             Serial.print(F("Leitura Falhou "));
             Serial.println(mfrc522.GetStatusCodeName(status));
             return;
           }
           else{
           }
           Serial.print(F("\nDados bloco ["));
           Serial.print(bloco);Serial.print(F("]: "));
           //imprime os dados lidos
           Serial.write(buffer, MAX_SIZE_BLOCK);
           Serial.println(" ");

           // instrui o PICC quando no estado ACTIVE a ir para um estado de "parada"
           mfrc522.PICC_HaltA();
           // "stop" a encriptação do PCD, deve ser chamado após a comunicação com autenticação, caso contrário novas comunicações não poderão ser iniciadas
           mfrc522.PCD_StopCrypto1();
           // executa  a cada 100 ms a leitura do serial
           vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
