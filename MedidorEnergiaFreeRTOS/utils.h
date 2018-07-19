#include <Arduino.h>


void floatToWordArray(float , word * );


void floatToWordArray(float number, word *reg){
 byte*  ArrayOfFourBytes;
 ArrayOfFourBytes = (byte*) &number;
 reg[0] = (ArrayOfFourBytes[1]<<8)| ArrayOfFourBytes[0];
 reg[1] = (ArrayOfFourBytes[3]<<8)| ArrayOfFourBytes[2];
}
