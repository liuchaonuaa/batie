#include <hidef.h>  
#include <MC9S12XEP100.h>
#include <string.h>

void Dly_ms(int ms);
void SPI_Write_Byte(byte add,byte data);
void SPI_Write_DLO_Byte(byte data);
void SPI_Write_FLO_Byte(byte data);
byte SPI_Read_Byte(byte add);
void Dly_ns(int ns);