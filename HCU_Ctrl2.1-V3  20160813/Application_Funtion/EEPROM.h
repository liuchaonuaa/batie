#include <hidef.h>  
#include <MC9S12XEP100.h>
#include <string.h>
//#define EEPROM_ADDR_BASE ((unsigned char *far)0x13FC00)
#define EEPROM_ADDR_BASE ((unsigned char *far)0x13F800)
#define EEPROM_ADDR_PAGE_BASE ((unsigned char *near)0x0800)


extern Word  eeprom_counter;
extern Byte  eeprom_en;
extern Byte  eeprom_modify;
extern Byte  eeprom_record[16];
extern Byte  eeprom_page;



void EPROM_read(unsigned char *far addr,unsigned char * databuf,unsigned char len) ;

void EPROM_write(unsigned char *far addr_dest,unsigned char * addr_source,unsigned char len) ;
void EPROM_write_byte(unsigned char *far addr_dest,byte data);
byte EPROM_read_byte(unsigned char *far addr_dest);
void EPROM_write_epage_byte(Word addr_dest,byte page,byte data);
byte EPROM_read_epage_byte(Word addr,byte page);

void EEPROM_TEST(void);