#include "ModbusIP_Init.h"

// registradores input
const int SENSOR_CORRENTE_0 = 0;
const int SENSOR_CORRENTE_1 = 1;
const int SENSOR_TENSAO_0 = 2;
const int SENSOR_TENSAO_1 = 3;
const int NIVEL_0 = 0;
const int CARGA_COIL = 0;

static void atualizaDados(void *);
const float periodoAtualizacao = 0.5;// segundos

void setup_modbus(){

    mb.addIreg(SENSOR_CORRENTE_0);
    mb.addIreg(SENSOR_CORRENTE_1);
    mb.addIreg(SENSOR_TENSAO_0);
    mb.addIreg(SENSOR_TENSAO_1);
    mb.addCoil(CARGA_COIL);
    mb.addIsts(NIVEL_0);
    mb_config_init("ScadaBR", "ScadaBRunp");
    xTaskCreatePinnedToCore(&atualizaDados, "atualiza", 4096, NULL, 20, NULL, 0);

}

/**
 * [atualizaDados atualiza dados em Modbus]
 * @param inpar [description]
 */
static void atualizaDados(void *inpar) {
    while(1) {
      word registro[2];
      floatToWordArray(Irms, registro);

      mb.Ireg(SENSOR_CORRENTE_0, registro[1]);
      mb.Ireg(SENSOR_CORRENTE_1, registro[0]);

      floatToWordArray(Vrms, registro);

      mb.Ireg(SENSOR_TENSAO_0, registro[1]);
      mb.Ireg(SENSOR_TENSAO_1, registro[0]);
      
      vTaskDelay((periodoAtualizacao*1000) / portTICK_PERIOD_MS);
  }

}
