
#ifndef __XGATE_H_
#define __XGATE_H_
#ifndef NO_ERR_xgate
  #define NO_ERR_xgate 0x00
  #define IS_ERR_xgate 0x01
#endif

#include <MC9S12XEP100.h>
#include <hidef.h>    
#include <string.h>



/* XGATE vector table entry */
typedef void (*_NEAR XGATE_Function)(int);
typedef struct {
  XGATE_Function pc;        /* pointer to the handler */
  int dataptr;              /* pointer to the data of the handler */
} XGATE_TableEntry;

#pragma push								/* save current segment definitions */

#pragma CONST_SEG __GPAGE_SEG XGATE_VECTORS  /* for the HCS12X/XGATE shared setup, HCS12X needs global addressing to access the vector table. */

#define XGATE_VECTOR_OFFSET 9							   /* the first elements are unused and need not to be allocated (to save space) */

extern const XGATE_TableEntry XGATE_VectorTable[];

#pragma pop									/* restore previous segment definitions */


/* this code is to demonstrate how to share data between XGATE and S12X */
#pragma push								/* save current segment definitions */






#pragma DATA_SEG SHARED_DATA /* allocate the following variables in the segment SHARED_DATA */
volatile extern int shared_counter; /* volatile because both cores are accessing it. */
volatile extern Word i_test_transfer;
volatile extern Word i_test_transfer1;
volatile extern Word analog_channel[10];

//--------------------------------------CAN-----------------------------------------------
volatile extern Byte CAN1_ID_box[8][4];
volatile extern Byte CAN1_TxBuffer_box[8][8];
volatile extern Byte CAN3_ID_box[5][4];
volatile extern Byte CAN3_TxBuffer_box[5][8];
volatile extern Byte CAN2_ID_box[1][4];
volatile extern Byte CAN2_TxBuffer_box[1][8];
volatile extern Byte CAN0_ID_box[2][4];
volatile extern Byte CAN0_TxBuffer_box[2][8];

//--------------------------------------PWM-----------------------------------------------
volatile extern Byte pwm_num;
volatile extern Word pwm_value;
volatile extern Byte xgate_pc_2ms;
volatile extern Byte xgate_pc_10ms;
volatile extern Byte xgate_pc_20ms;
volatile extern Byte xgate_pc_50ms;
volatile extern Byte xgate_pc_100ms;
volatile extern Byte xgate_pc_200ms;
volatile extern Byte xgate_pc_500ms;




#pragma DATA_SEG DEFAULT
void  Analog_channle_scan();
void  Analog_channel_sum();




#pragma pop									/* restore previous segment definitions */


#endif /* __XGATE_H_ */
