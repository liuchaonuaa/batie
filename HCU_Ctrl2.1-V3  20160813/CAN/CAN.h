#include <hidef.h>  
#include <MC9S12XEP100.h>
#include <string.h>
#include "Application_Funtion.h"





#ifndef NO_ERR
  #define NO_ERR 0x00
  #define IS_ERR 0x01
#endif

 unsigned long GET_ID(int i);//获取相应中断通道的中断ID号   i是通道号
 void CAN0_transfer_load(byte num,unsigned long ID);//num通道号，ID为发送的ID号码
 void Set_CAN_ID(unsigned long ID,int CAN_NUM,byte pf); // ID为发送的ID号，CAN_NUM为通道号，pf为待发送帧
 void CAN0receive(void);
 void CAN1_transfer_load(byte num,unsigned long ID);//num通道号，ID为发送的ID号码
 void CAN1receive(void);
 void CAN2_transfer_load(byte num,unsigned long ID);//num通道号，ID为发送的ID号码
 void CAN2receive(void);
 void CAN3_transfer_load(byte num,unsigned long ID);//num通道号，ID为发送的ID号码
 void CAN3receive(void);
 void CAN0_DistillMessage();
 void CAN1_DistillMessage();
 void CAN2_DistillMessage();
 void CAN3_DistillMessage();
 int CAN0_transfer_start(byte pf, byte Ext);
 int CAN1_transfer_start(byte pf, byte Ext);
 int CAN2_transfer_start(byte pf, byte Ext);
 int CAN3_transfer_start(byte pf, byte Ext);
                                 
//-------------------------------------CAN--------------------------------------------------------

#define  CAN0 0
#define  CAN1 1
#define  CAN2 2
#define  CAN3 3




extern byte CAN0_TxBuffer[8];
extern byte CAN0_RxBuffer[8];
extern byte CAN1_TxBuffer[8];
extern byte CAN1_RxBuffer[8];
extern byte CAN2_TxBuffer[8];
extern byte CAN2_RxBuffer[8];
extern byte CAN3_TxBuffer[8];
extern byte CAN3_RxBuffer[8];
extern byte CAN0_ID[4];
extern byte CAN1_ID[4];
extern byte CAN2_ID[4];
extern byte CAN3_ID[4];



/******************** CANA宏定义  **********************************/
/******************** 电机模式宏定义  ******************************/
#define MOTOR_STOP_MODE 0          //  停止模式
#define MOTOR_FORWARD_MODE 1       //  前进模式
#define MOTOR_BRAKE_MODE 2         //  制动模式
#define MOTOR_BACKWARD_MODE 4      //  倒退模式

/******************** CAN3 MACRO  **********************************/
//Send IDs
#define VCU_To_All       2               //VCU2/3 send cab active side to other VCUs  
#define VCU2             1
                         
#define VCU_To_BMS1_ID    3  
#define VCU_To_BMS1       2

#define VCU_To_BMS2_ID    4  
#define VCU_To_BMS2       3

#define VCU3_To_HMI14    20
#define VCU_To_HMI14     4

#define VCU3_To_HMI23    22
#define VCU_To_HMI23     5



#define HIM2_SEND_ID   0x160110
#define HIM2_RECV_ID   0x160111


#define HIM4_SEND_ID   0x160310
#define HIM4_RECV_ID   0x160311




//Receive IDs
#define From_Other_VCU   100             
#define BMS1_MainInfo1   5
#define BMS2_MainInfo1   6
#define BMS1_MainInfo2   7
#define BMS2_MainInfo2   8
#define BMS1_AddInfo     9
#define BMS2_AddInfo     10
#define BMS1_MaxPow      11
#define BMS2_MaxPow      12
#define BMS1_Isolation   13
#define BMS2_Isolation   14
#define BMS1_Others      15
#define BMS2_Others      16
#define HMI1_VCU23       23
#define HMI4_VCU23       24




/******************** CAN1 MACRO  **********************************/
//Send IDs
#define VCU_DCU_ID1 0x0C19F0A7
#define VCU_DCU_1 1

#define VCU_DCU_ID2 0x0C19F1A7
#define VCU_DCU_2 2

#define VCU_DCU_ID3 0x0C19F2A7
#define VCU_DCU_3 3

#define VCU_DCU_ID4 0x0C19F3A7
#define VCU_DCU_4 4

#define VCU_DCU_ID5 0x0C19F4A7
#define VCU_DCU_5 5

#define VCU_DCU_ID6 0x0C19F5A7
#define VCU_DCU_6 6

#define VCU_DCU_ID7 0x0C19F6A7
#define VCU_DCU_7 7

#define VCU_DCU_ID8 0x0C19F7A7
#define VCU_DCU_8 8

//Receive IDs
#define DCU1_VCU_Info1 0x0C08A7F0
#define DCU2_VCU_Info1 0x0C08A7F1
#define DCU3_VCU_Info1 0x0C08A7F2
#define DCU4_VCU_Info1 0x0C08A7F3
#define DCU5_VCU_Info1 0x0C08A7F4
#define DCU6_VCU_Info1 0x0C08A7F5
#define DCU7_VCU_Info1 0x0C08A7F6
#define DCU8_VCU_Info1 0x0C08A7F7

#define DCU1_VCU_Info2 0x0C09A7F0
#define DCU2_VCU_Info2 0x0C09A7F1
#define DCU3_VCU_Info2 0x0C09A7F2
#define DCU4_VCU_Info2 0x0C09A7F3
#define DCU5_VCU_Info2 0x0C09A7F4
#define DCU6_VCU_Info2 0x0C09A7F5
#define DCU7_VCU_Info2 0x0C09A7F6
#define DCU8_VCU_Info2 0x0C09A7F7



/******************** CAN2 MACRO  **********************************/
//Send IDs
#define VCU_ACU_ID 0x0c070101
#define VCU_ACU 1

//Recv IDs
#define ACU_VCU_DCDC_1 0x0c010101
#define ACU_VCU_DCAC_1 0x0c020101
#define ACU_VCU_DCDC_2 0x0c010102
#define ACU_VCU_DCAC_2 0x0c020102
#define ACU_VCU_DCDC_3 0x0c010103
#define ACU_VCU_DCAC_3 0x0c020103
#define ACU_VCU_DCDC_4 0x0c010104
#define ACU_VCU_DCAC_4 0x0c020104

/******************** CAN0宏定义  **********************************/
/******************** CAN0 MACRO  **********************************/
//Send IDs
#define VCU2_ID 1
#define VCU2    1

#define VCU3_ID 2
#define VCU3    2





//Recv IDs
#define VCU5_VCU_ID 3
#define VCU6_VCU_ID 4
#define VCU7_VCU_ID 5
#define VCU8_VCU_ID 6



extern Byte pageIndex;
 
void can_test(void); 
void can_test2(void);
void him_init(void);
void MY_LCD_SetValueToEdite1(byte canChannel, dword ID, word editID, byte *buf);
void MY_LCD_SetValueToEdite2(byte canChannel, dword ID, word editID, int value);
void MY_LCD_SetValueToEdite3(byte canChannel, dword ID, word editID, float value);

void MY_LCD_SetChildBarHeight2(byte canChannel, dword ID, byte pIndex, byte controlIndex, 
                            byte childIndex, word barHeight);
                            
void MY_LCD_LoadPartBmpEx2(byte canChannel, dword ID, byte controlType, word ItemIndex, word sx, word sy); 

void MY_LCD_ExecuteEvent(byte canChannel, dword ID, byte controlType, byte eventType, word editID);   

void MY_LCD_ShowStringAt(byte canChannel, dword ID, word x, word y, byte *buf, byte color);

void MY_LCD_ForwardPage(byte canChannel, dword ID, byte cPageIndex);
void Vcu_TrainSpeed_Calc(void);
