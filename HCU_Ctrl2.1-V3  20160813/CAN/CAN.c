#include "CAN.h"
#include "Data.h"
#include "Application_Funtion.h"

// liuchao start
#include"lr_lcd_api.h"
#include <math.h>
#include <stdio.h>
#include "UserFunction.h"
#include "usr_lcd_api.h"
// liuchao end





#pragma DATA_SEG SHARED_DATA
volatile extern Byte CAN1_ID_box[8][4];
volatile extern Byte CAN1_TxBuffer_box[8][8];
volatile extern Byte CAN3_ID_box[5][4];
volatile extern Byte CAN3_TxBuffer_box[5][8];
volatile extern Byte CAN2_ID_box[1][4];
volatile extern Byte CAN2_TxBuffer_box[1][8];
volatile extern Byte CAN0_ID_box[2][4];
volatile extern Byte CAN0_TxBuffer_box[2][8];


#pragma DATA_SEG DEFAULT


//CAN3 Recv
Byte abyVCU_CAN3_Recv_From_Other_VCU[8];
Byte abyVCU_CAN3_Recv_BMS1_MainInfo1[8];
Byte abyVCU_CAN3_Recv_BMS2_MainInfo1[8];
Byte abyVCU_CAN3_Recv_BMS1_MainInfo2[8];
Byte abyVCU_CAN3_Recv_BMS2_MainInfo2[8];
Byte abyVCU_CAN3_Recv_BMS1_AddInfo[8];
Byte abyVCU_CAN3_Recv_BMS2_AddInfo[8];
Byte abyVCU_CAN3_Recv_BMS1_MaxPow[8];
Byte abyVCU_CAN3_Recv_BMS2_MaxPow[8];
Byte abyVCU_CAN3_Recv_BMS1_Isolation[8];
Byte abyVCU_CAN3_Recv_BMS2_Isolation[8];
Byte abyVCU_CAN3_Recv_BMS1_Others[8];
Byte abyVCU_CAN3_Recv_BMS2_Others[8];
Byte abyVCU_CAN3_Recv_HMI1_VCU23[8];
Byte abyVCU_CAN3_Recv_HMI4_VCU23[8];

//CAN1 Recv
Byte abyVCU_CAN1_Recv_MCU_S_1_DCU1[8];
Byte abyVCU_CAN1_Recv_MCU_S_1_DCU2[8];
Byte abyVCU_CAN1_Recv_MCU_S_1_DCU3[8];
Byte abyVCU_CAN1_Recv_MCU_S_1_DCU4[8];
Byte abyVCU_CAN1_Recv_MCU_S_1_DCU5[8];
Byte abyVCU_CAN1_Recv_MCU_S_1_DCU6[8];
Byte abyVCU_CAN1_Recv_MCU_S_1_DCU7[8];
Byte abyVCU_CAN1_Recv_MCU_S_1_DCU8[8];
Byte abyVCU_CAN1_Recv_MCU_S_2_DCU1[8];
Byte abyVCU_CAN1_Recv_MCU_S_2_DCU2[8];
Byte abyVCU_CAN1_Recv_MCU_S_2_DCU3[8];
Byte abyVCU_CAN1_Recv_MCU_S_2_DCU4[8];
Byte abyVCU_CAN1_Recv_MCU_S_2_DCU5[8];
Byte abyVCU_CAN1_Recv_MCU_S_2_DCU6[8];
Byte abyVCU_CAN1_Recv_MCU_S_2_DCU7[8];
Byte abyVCU_CAN1_Recv_MCU_S_2_DCU8[8];

//CAN2 Recv
//Byte abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[8];   //shenmin
//Byte abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[8];   //shenmin
//Byte abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[8];   //shenmin
//Byte abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[8];   //shenmin
//Byte abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[8];   //shenmin
//Byte abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[8];   //shenmin
//Byte abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[8];   //shenmin
//Byte abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[8];   //shenmin

//CAN0 Recv
//Byte abyVCU_CAN0_Recv_VCU5_VCU_ID[8];   //shenmin
//Byte abyVCU_CAN0_Recv_VCU6_VCU_ID[8];   //shenmin
//Byte abyVCU_CAN0_Recv_VCU7_VCU_ID[8];   //shenmin
//Byte abyVCU_CAN0_Recv_VCU8_VCU_ID[8];   //shenmin


/***********************************************************************************************
 *                                                                                             *
 *                              MCU CAN                                              *
 *                                                                                             *
 * 函 数 名:                                                                                   *
 * 功能描述:                                                                       *
 * 全局变量:                                                                                   *
 * 输		 入:                                                                                   *
 * 输		 出:                                                                                   *
 * 编    辑：                                                                      *
 * 修 改 人：  			 						 	                                                             *
 * 修改日期：                                                                                  *
 * 函数说明:                                                                                   *
 /**********************************************************************************************/
 




byte CAN0_TxBuffer[8];     //CAN0发送缓存数组
byte CAN0_RxBuffer[8];     //CAN0接收数据缓存
byte CAN1_TxBuffer[8];     //CAN1发送数据缓存
byte CAN1_RxBuffer[8];     //CAN1接收数据缓存
byte CAN2_TxBuffer[8];     //CAN2发送数据缓存
byte CAN2_RxBuffer[8];     //CAN2接收数据缓存
byte CAN3_TxBuffer[8];     //CAN3发送数据缓存
byte CAN3_RxBuffer[8];     //CAN3接收数据缓存
byte CAN0_ID[4];           //29位ID数据缓存  分4个Byte
byte CAN1_ID[4];           //29位ID数据缓存  分4个Byte
byte CAN2_ID[4];           //29位ID数据缓存  分4个Byte
byte CAN3_ID[4];           //29位ID数据缓存  分4个Byte

 byte can0r;//CAN0中断计数
 byte can1r;//CAN1中断计数
 byte can2r;//CAN2中断计数
 byte can3r;//CAN3中断计数





 
// liuchao start
Byte CAN3RevBuf[20] = { 0 };

Byte pageIndex = 0;
Byte pageSwitch = 0;


byte MC1_A_MSG_BOX[8];

byte moterTempTmp[8] = {1, 1, 1, 1, 1, 1, 1, 1};
byte moterCtrlTempTmp[8] = {1, 1, 1, 1, 1, 1, 1, 1};
byte errorCodeTmp[8] = {1, 1, 1, 1, 1, 1, 1, 1};
float motorFrontVolTmp[8] = {700, 700, 700, 700, 700, 700, 700, 700};


word moterTempID[8] = { 
    ID_EDITE_3163, ID_EDITE_3162, ID_EDITE_3161, ID_EDITE_3160, 
    ID_EDITE_3159, ID_EDITE_3158, ID_EDITE_3157, ID_EDITE_3156
};

word moterCtrlTempID[8] = { 
    ID_EDITE_3173, ID_EDITE_3165, ID_EDITE_3175, ID_EDITE_3167, 
    ID_EDITE_3177, ID_EDITE_3169, ID_EDITE_3179, ID_EDITE_3171
};

word moterVolID[8] = { 
    ID_EDITE_3174, ID_EDITE_3166, ID_EDITE_3176, ID_EDITE_3168, 
    ID_EDITE_3178, ID_EDITE_3170, ID_EDITE_3180, ID_EDITE_3172
};





byte batStatusTmp[2] = {1, 1};
float batVolTmp[2] = {3, 3};
float batCurTmp[2] = {3, 3};       
byte batSocTmp[2] = {1, 1};




// liuchao end







//---------------------------------CAN1发送函数---------------------------------------//
void CAN1_transfer_load(byte num,unsigned long ID) 
{
 unsigned long ID_temp;
 byte pf;
 Word temp;
 ID_temp=ID;
 pf=(num-1);
 AcquireAccessToSharedMemory(can_semaphore_mcu);//锁定
 switch(num)
 {
   
    
     case VCU_DCU_1:            
     {     
         CAN1_TxBuffer_box[0][0]=(byte)(aiTargetTorque[0] & 0x00FF);
         CAN1_TxBuffer_box[0][1]=(byte)((aiTargetTorque[0] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[0][2]=(byte)(aiDCVoltLmt[0] & 0x00FF);
         CAN1_TxBuffer_box[0][3]=(byte)((aiDCVoltLmt[0] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[0][4]=(byte)(aiDCCurLmt[0] & 0x00FF);
         CAN1_TxBuffer_box[0][5]=(byte)((aiDCCurLmt[0] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[0][6]=(byte)abyMotorCtrl[0];
         CAN1_TxBuffer_box[0][7]=(byte)abyLifesign[0]++;
         
         Set_CAN_ID(ID_temp,1,pf);         //设置ID
         CAN1_transfer_start(pf, 1);
         break;
     }
     
     case VCU_DCU_2:            
     { 
         CAN1_TxBuffer_box[1][0]=(byte)(aiTargetTorque[1] & 0x00FF);
         CAN1_TxBuffer_box[1][1]=(byte)((aiTargetTorque[1] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[1][2]=(byte)(aiDCVoltLmt[1] & 0x00FF);
         CAN1_TxBuffer_box[1][3]=(byte)((aiDCVoltLmt[1] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[1][4]=(byte)(aiDCCurLmt[1] & 0x00FF);
         CAN1_TxBuffer_box[1][5]=(byte)((aiDCCurLmt[1] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[1][6]=(byte)abyMotorCtrl[1];
         CAN1_TxBuffer_box[1][7]=(byte)abyLifesign[1]++;
         
         Set_CAN_ID(ID_temp,1,pf);         //设置ID
         CAN1_transfer_start(pf, 1);
         break;
     }
     
     case VCU_DCU_3:            
     { 
         CAN1_TxBuffer_box[2][0]=(byte)(aiTargetTorque[2] & 0x00FF);
         CAN1_TxBuffer_box[2][1]=(byte)((aiTargetTorque[2] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[2][2]=(byte)(aiDCVoltLmt[2] & 0x00FF);
         CAN1_TxBuffer_box[2][3]=(byte)((aiDCVoltLmt[2] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[2][4]=(byte)(aiDCCurLmt[2] & 0x00FF);
         CAN1_TxBuffer_box[2][5]=(byte)((aiDCCurLmt[2] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[2][6]=(byte)abyMotorCtrl[2];
         CAN1_TxBuffer_box[2][7]=(byte)abyLifesign[2]++;
         
         Set_CAN_ID(ID_temp,1,pf);         //设置ID
         CAN1_transfer_start(pf, 1);
         break;
     }
     
     case VCU_DCU_4:            
     { 
         CAN1_TxBuffer_box[3][0]=(byte)(aiTargetTorque[3] & 0x00FF);
         CAN1_TxBuffer_box[3][1]=(byte)((aiTargetTorque[3] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[3][2]=(byte)(aiDCVoltLmt[3] & 0x00FF);
         CAN1_TxBuffer_box[3][3]=(byte)((aiDCVoltLmt[3] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[3][4]=(byte)(aiDCCurLmt[3] & 0x00FF);
         CAN1_TxBuffer_box[3][5]=(byte)((aiDCCurLmt[3] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[3][6]=(byte)abyMotorCtrl[3];
         CAN1_TxBuffer_box[3][7]=(byte)abyLifesign[3]++;
         
         Set_CAN_ID(ID_temp,1,pf);         //设置ID
         CAN1_transfer_start(pf, 1);
         break;
     }
    
     
     
     
     
     case VCU_DCU_5:            
     { 
         CAN1_TxBuffer_box[4][0]=(byte)(aiTargetTorque[4] & 0x00FF);
         CAN1_TxBuffer_box[4][1]=(byte)((aiTargetTorque[4] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[4][2]=(byte)(aiDCVoltLmt[4] & 0x00FF);
         CAN1_TxBuffer_box[4][3]=(byte)((aiDCVoltLmt[4] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[4][4]=(byte)(aiDCCurLmt[4] & 0x00FF);
         CAN1_TxBuffer_box[4][5]=(byte)((aiDCCurLmt[4] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[4][6]=(byte)abyMotorCtrl[4];
         CAN1_TxBuffer_box[4][7]=(byte)abyLifesign[4]++;
         
         Set_CAN_ID(ID_temp,1,pf);         //设置ID
         CAN1_transfer_start(pf, 1);
         break;
     }
     
     
     
     case VCU_DCU_6:            
     { 
         CAN1_TxBuffer_box[5][0]=(byte)(aiTargetTorque[5] & 0x00FF);
         CAN1_TxBuffer_box[5][1]=(byte)((aiTargetTorque[5] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[5][2]=(byte)(aiDCVoltLmt[5] & 0x00FF);
         CAN1_TxBuffer_box[5][3]=(byte)((aiDCVoltLmt[5] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[5][4]=(byte)(aiDCCurLmt[5] & 0x00FF);
         CAN1_TxBuffer_box[5][5]=(byte)((aiDCCurLmt[5] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[5][6]=(byte)abyMotorCtrl[5];
         CAN1_TxBuffer_box[5][7]=(byte)abyLifesign[5]++;
         
         Set_CAN_ID(ID_temp,1,pf);         //设置ID
         CAN1_transfer_start(pf, 1);
         break;
     }
     
     case VCU_DCU_7:            
     { 
         CAN1_TxBuffer_box[6][0]=(byte)(aiTargetTorque[6] & 0x00FF);
         CAN1_TxBuffer_box[6][1]=(byte)((aiTargetTorque[6] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[6][2]=(byte)(aiDCVoltLmt[6] & 0x00FF);
         CAN1_TxBuffer_box[6][3]=(byte)((aiDCVoltLmt[6] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[6][4]=(byte)(aiDCCurLmt[6] & 0x00FF);
         CAN1_TxBuffer_box[6][5]=(byte)((aiDCCurLmt[6] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[6][6]=(byte)abyMotorCtrl[6];
         CAN1_TxBuffer_box[6][7]=(byte)abyLifesign[6]++;
         
         Set_CAN_ID(ID_temp,1,pf);         //设置ID
         CAN1_transfer_start(pf, 1);
         break;
     }
     
     case VCU_DCU_8:            
     { 
         CAN1_TxBuffer_box[7][0]=(byte)(aiTargetTorque[7] & 0x00FF);
         CAN1_TxBuffer_box[7][1]=(byte)((aiTargetTorque[7] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[7][2]=(byte)(aiDCVoltLmt[7] & 0x00FF);
         CAN1_TxBuffer_box[7][3]=(byte)((aiDCVoltLmt[7] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[7][4]=(byte)(aiDCCurLmt[7] & 0x00FF);
         CAN1_TxBuffer_box[7][5]=(byte)((aiDCCurLmt[7] & 0xFF00) >> 8);
         CAN1_TxBuffer_box[7][6]=(byte)abyMotorCtrl[7];
         CAN1_TxBuffer_box[7][7]=(byte)abyLifesign[7]++;
         
         Set_CAN_ID(ID_temp,1,pf);         //设置ID
         CAN1_transfer_start(pf, 1);
         break;
     }
     
     
     
     default: break; 
 }

ReleaseAccessToSharedMemory(can_semaphore_mcu);//解锁
}


//CAN发送函数
int CAN1_transfer_start(byte pf,byte Ext) 
{
  byte can1tx;
  byte i;
  int cnt=0;
  i=pf;
  if (!CAN1TFLG) return IS_ERR;            //查询发送buffer是否为空       
  CAN1TBSEL = CAN1TFLG;                    //选择最低位空的buffer作为发送寄存器
  can1tx    = CAN1TBSEL;                   //备份选择的发送缓存
  if(1==Ext) 
  {  
    CAN1TXIDR0 =CAN1_ID_box[i][0];
    CAN1TXIDR1 =CAN1_ID_box[i][1]; 
    CAN1TXIDR2 =CAN1_ID_box[i][2]; 
    CAN1TXIDR3 =CAN1_ID_box[i][3]; 
  } 
  else 
  {
    CAN1TXIDR0 =  ((CAN1_ID_box[i][2]&0x0F)<<4)|((CAN1_ID_box[i][3]&0xF0)>>4);
    CAN1TXIDR1 = (CAN1_ID_box[i][3]&0x0E)<<4;
  }
  CAN1TXDLR = 8;                       //指定数据长度
  CAN1TXTBPR= 1;                       //设置发送优先级
  CAN1TXDSR0 = CAN1_TxBuffer_box[i][0];              //写入发送内容
  CAN1TXDSR1 = CAN1_TxBuffer_box[i][1];
  CAN1TXDSR2 = CAN1_TxBuffer_box[i][2];
  CAN1TXDSR3 = CAN1_TxBuffer_box[i][3];
  CAN1TXDSR4 = CAN1_TxBuffer_box[i][4];
  CAN1TXDSR5 = CAN1_TxBuffer_box[i][5];
  CAN1TXDSR6 = CAN1_TxBuffer_box[i][6];
  CAN1TXDSR7 = CAN1_TxBuffer_box[i][7];

  CAN1TFLG = can1tx;                             //开始传送；
  
  while ((CAN1TFLG & can1tx) != can1tx)
  if(++cnt>10000) return IS_ERR; 
  return NO_ERR; 
}

//----------------------------------------CAN0接收----------------------------------------------------------

void CAN1receive(void)    //CAN0数据接收
{
    unsigned long ID=0;
    
  ID=GET_ID(CAN1);          //获取CAN0上报文
  switch(ID)                     //对ID进行判断
  {
          
      case DCU1_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_1_DCU1[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_1_DCU1[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_1_DCU1[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_1_DCU1[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_1_DCU1[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_1_DCU1[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_1_DCU1[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_1_DCU1[7]=CAN1RXDSR7;
          break;        
      }
      
      case DCU2_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_1_DCU2[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_1_DCU2[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_1_DCU2[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_1_DCU2[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_1_DCU2[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_1_DCU2[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_1_DCU2[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_1_DCU2[7]=CAN1RXDSR7;
          break;        
      }
      
      case DCU3_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_1_DCU3[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_1_DCU3[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_1_DCU3[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_1_DCU3[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_1_DCU3[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_1_DCU3[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_1_DCU3[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_1_DCU3[7]=CAN1RXDSR7;
          break;        
      }
      
      case DCU4_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_1_DCU4[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_1_DCU4[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_1_DCU4[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_1_DCU4[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_1_DCU4[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_1_DCU4[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_1_DCU4[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_1_DCU4[7]=CAN1RXDSR7;
          break;        
      }
      
      case DCU5_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_1_DCU5[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_1_DCU5[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_1_DCU5[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_1_DCU5[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_1_DCU5[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_1_DCU5[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_1_DCU5[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_1_DCU5[7]=CAN1RXDSR7;
          break;        
      }
      
      case DCU6_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_1_DCU6[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_1_DCU6[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_1_DCU6[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_1_DCU6[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_1_DCU6[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_1_DCU6[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_1_DCU6[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_1_DCU6[7]=CAN1RXDSR7;
          break;        
      }
      
      case DCU7_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_1_DCU7[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_1_DCU7[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_1_DCU7[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_1_DCU7[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_1_DCU7[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_1_DCU7[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_1_DCU7[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_1_DCU7[7]=CAN1RXDSR7;
          break;        
      }
      
      case DCU8_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_1_DCU8[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_1_DCU8[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_1_DCU8[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_1_DCU8[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_1_DCU8[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_1_DCU8[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_1_DCU8[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_1_DCU8[7]=CAN1RXDSR7;
          break;        
      }
  
     
      
      case DCU1_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_2_DCU1[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_2_DCU1[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_2_DCU1[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_2_DCU1[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_2_DCU1[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_2_DCU1[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_2_DCU1[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_2_DCU1[7]=CAN1RXDSR7;
          break;        
      }
      
      case DCU2_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_2_DCU2[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_2_DCU2[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_2_DCU2[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_2_DCU2[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_2_DCU2[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_2_DCU2[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_2_DCU2[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_2_DCU2[7]=CAN1RXDSR7;
          break;        
      }
      
      case DCU3_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_2_DCU3[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_2_DCU3[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_2_DCU3[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_2_DCU3[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_2_DCU3[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_2_DCU3[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_2_DCU3[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_2_DCU3[7]=CAN1RXDSR7;
          break;        
      }
      
      case DCU4_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_2_DCU4[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_2_DCU4[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_2_DCU4[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_2_DCU4[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_2_DCU4[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_2_DCU4[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_2_DCU4[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_2_DCU4[7]=CAN1RXDSR7;
          break;        
      }
      
      case DCU5_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_2_DCU5[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_2_DCU5[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_2_DCU5[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_2_DCU5[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_2_DCU5[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_2_DCU5[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_2_DCU5[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_2_DCU5[7]=CAN1RXDSR7;
          break;        
      }
      
      case DCU6_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_2_DCU6[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_2_DCU6[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_2_DCU6[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_2_DCU6[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_2_DCU6[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_2_DCU6[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_2_DCU6[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_2_DCU6[7]=CAN1RXDSR7;
          break;        
      }
      
      case DCU7_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_2_DCU7[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_2_DCU7[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_2_DCU7[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_2_DCU7[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_2_DCU7[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_2_DCU7[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_2_DCU7[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_2_DCU7[7]=CAN1RXDSR7;
          break;        
      }
      
      case DCU8_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
      {
          abyVCU_CAN1_Recv_MCU_S_2_DCU8[0]=CAN1RXDSR0;
          abyVCU_CAN1_Recv_MCU_S_2_DCU8[1]=CAN1RXDSR1;
          abyVCU_CAN1_Recv_MCU_S_2_DCU8[2]=CAN1RXDSR2;
          abyVCU_CAN1_Recv_MCU_S_2_DCU8[3]=CAN1RXDSR3;
          abyVCU_CAN1_Recv_MCU_S_2_DCU8[4]=CAN1RXDSR4;
          abyVCU_CAN1_Recv_MCU_S_2_DCU8[5]=CAN1RXDSR5;
          abyVCU_CAN1_Recv_MCU_S_2_DCU8[6]=CAN1RXDSR6;
          abyVCU_CAN1_Recv_MCU_S_2_DCU8[7]=CAN1RXDSR7;
          break;        
      }
      
      default: break;
  }   

}

/************************************************************************
** 函数名称：CAN1_DistillMessage()                                    **
** 函数功能：CAN1_DistillMessage                                      **
                                                  
** 备    注：对CAN1接受报文数据解码，并赋值给相应变量，本地函数       **
************************************************************************/ 
void CAN1_DistillMessage()
{
    unsigned long ID=0;
    
    ID=GET_ID(CAN1);          //获取CAN0上报文
    switch(ID)                     //对ID进行判断
    {
             
        case DCU1_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            aiMotorTorque[0] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU1[1]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU1[0];
            aiMotorRPM[0]    = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU1[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU1[2];
            aiMCMInputCur[0] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU1[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU1[4];
            abyMCMStat[0]    = abyVCU_CAN1_Recv_MCU_S_1_DCU1[6];
            abyMCMLife[0]    = abyVCU_CAN1_Recv_MCU_S_1_DCU1[7];
            break;        
        }
        
        case DCU2_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            aiMotorTorque[1] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU2[1]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU2[0];
            aiMotorRPM[1]    = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU2[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU2[2];
            aiMCMInputCur[1] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU2[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU2[4];
            abyMCMStat[1]    = abyVCU_CAN1_Recv_MCU_S_1_DCU2[6];
            abyMCMLife[1]    = abyVCU_CAN1_Recv_MCU_S_1_DCU2[7];
            break;        
        }
        
        case DCU3_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            aiMotorTorque[2] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU3[1]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU3[0];
            aiMotorRPM[2]    = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU3[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU3[2];
            aiMCMInputCur[2] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU3[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU3[4];
            abyMCMStat[2]    = abyVCU_CAN1_Recv_MCU_S_1_DCU3[6];
            abyMCMLife[2]    = abyVCU_CAN1_Recv_MCU_S_1_DCU3[7];
            break;        
        }
        
        case DCU4_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            aiMotorTorque[3] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU4[1]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU4[0];
            aiMotorRPM[3]    = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU4[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU4[2];
            aiMCMInputCur[3] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU4[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU4[4];
            abyMCMStat[3]    = abyVCU_CAN1_Recv_MCU_S_1_DCU4[6];
            abyMCMLife[3]    = abyVCU_CAN1_Recv_MCU_S_1_DCU4[7];
            break;        
        }
        
        case DCU5_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            aiMotorTorque[4] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU5[1]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU5[0];
            aiMotorRPM[4]    = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU5[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU5[2];
            aiMCMInputCur[4] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU5[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU5[4];
            abyMCMStat[4]    = abyVCU_CAN1_Recv_MCU_S_1_DCU5[6];
            abyMCMLife[4]    = abyVCU_CAN1_Recv_MCU_S_1_DCU5[7];
            break;        
        }
        
        case DCU6_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            aiMotorTorque[5] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU6[1]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU6[0];
            aiMotorRPM[5]    = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU6[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU6[2];
            aiMCMInputCur[5] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU6[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU6[4];
            abyMCMStat[5]    = abyVCU_CAN1_Recv_MCU_S_1_DCU6[6];
            abyMCMLife[5]    = abyVCU_CAN1_Recv_MCU_S_1_DCU6[7];
            break;        
        }
        
        case DCU7_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            aiMotorTorque[6] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU7[1]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU7[0];
            aiMotorRPM[6]    = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU7[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU7[2];
            aiMCMInputCur[6] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU7[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU7[4];
            abyMCMStat[6]    = abyVCU_CAN1_Recv_MCU_S_1_DCU7[6];
            abyMCMLife[6]    = abyVCU_CAN1_Recv_MCU_S_1_DCU7[7];
            break;        
        }
        
        case DCU8_VCU_Info1:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            aiMotorTorque[7] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU8[1]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU8[0];
            aiMotorRPM[7]    = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU8[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU8[2];
            aiMCMInputCur[7] = ((int)(abyVCU_CAN1_Recv_MCU_S_1_DCU8[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU8[4];
            abyMCMStat[7]    = abyVCU_CAN1_Recv_MCU_S_1_DCU8[6];
            abyMCMLife[7]    = abyVCU_CAN1_Recv_MCU_S_1_DCU8[7];
            break;        
        }
        
          
        
        
        
        case DCU1_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            //aiContFrontVolt[0] = (((abyVCU_CAN1_Recv_MCU_S_2_DCU1[1] << 8) + abyVCU_CAN1_Recv_MCU_S_2_DCU1[0]) - 10000) * 0.1;
            //abyMotorTemp[0]    = abyVCU_CAN1_Recv_MCU_S_2_DCU1[2] - 40;
            //abyMCMTemp[0]      = abyVCU_CAN1_Recv_MCU_S_2_DCU1[3] - 40;
            //aiMCMRectCur[0]    = ((int)(abyVCU_CAN1_Recv_MCU_S_2_DCU1[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_2_DCU1[4];
            //abyMCMConStat[0]   = abyVCU_CAN1_Recv_MCU_S_2_DCU1[6];
            //abyMotorErrCode[0] = abyVCU_CAN1_Recv_MCU_S_2_DCU1[7];
            break;        
        }
        
        case DCU2_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            //aiContFrontVolt[1] = (((abyVCU_CAN1_Recv_MCU_S_2_DCU2[1] << 8) + abyVCU_CAN1_Recv_MCU_S_2_DCU2[0]) - 10000) * 0.1;
            //abyMotorTemp[1]    = abyVCU_CAN1_Recv_MCU_S_2_DCU2[2] - 40;
            //abyMCMTemp[1]      = abyVCU_CAN1_Recv_MCU_S_2_DCU2[3] - 40;
            //aiMCMRectCur[1]    = ((int)(abyVCU_CAN1_Recv_MCU_S_2_DCU2[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_2_DCU2[4];
           // abyMCMConStat[1]   = abyVCU_CAN1_Recv_MCU_S_2_DCU2[6];
            //abyMotorErrCode[1] = abyVCU_CAN1_Recv_MCU_S_2_DCU2[7];
            break;        
        }
        
        case DCU3_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            //aiContFrontVolt[2] = (((abyVCU_CAN1_Recv_MCU_S_2_DCU3[1] << 8) + abyVCU_CAN1_Recv_MCU_S_2_DCU3[0]) - 10000) * 0.1;
            //abyMotorTemp[2]    = abyVCU_CAN1_Recv_MCU_S_2_DCU3[2] - 40;
            //abyMCMTemp[2]      = abyVCU_CAN1_Recv_MCU_S_2_DCU3[3] - 40;
           // aiMCMRectCur[2]    = ((int)(abyVCU_CAN1_Recv_MCU_S_2_DCU3[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_2_DCU3[4];
            //abyMCMConStat[2]   = abyVCU_CAN1_Recv_MCU_S_2_DCU3[6];
            //abyMotorErrCode[2] = abyVCU_CAN1_Recv_MCU_S_2_DCU3[7];
            break;        
        }
        
        case DCU4_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            //aiContFrontVolt[3] = ((((int)(abyVCU_CAN1_Recv_MCU_S_2_DCU4[1]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_2_DCU4[0]) - 10000) * 0.1;
            //abyMotorTemp[3]    = abyVCU_CAN1_Recv_MCU_S_2_DCU4[2] - 40;
            //abyMCMTemp[3]      = abyVCU_CAN1_Recv_MCU_S_2_DCU4[3] - 40;
            //aiMCMRectCur[3]    = ((int)(abyVCU_CAN1_Recv_MCU_S_2_DCU4[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_2_DCU4[4];
            //abyMCMConStat[3]   = abyVCU_CAN1_Recv_MCU_S_2_DCU4[6];
            //abyMotorErrCode[3] = abyVCU_CAN1_Recv_MCU_S_2_DCU4[7];
            break;        
        }
        
        
        
       
               
        case DCU5_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            //aiContFrontVolt[4] = ((((int)abyVCU_CAN1_Recv_MCU_S_2_DCU5[1] << 8) + (int)abyVCU_CAN1_Recv_MCU_S_2_DCU5[0]) - 10000) * 0.1;
            //abyMotorTemp[4]    = abyVCU_CAN1_Recv_MCU_S_2_DCU5[2] - 40;
            //abyMCMTemp[4]      = abyVCU_CAN1_Recv_MCU_S_2_DCU5[3] - 40;
            //aiMCMRectCur[4]    = ((int)(abyVCU_CAN1_Recv_MCU_S_2_DCU5[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_2_DCU5[4];
            //abyMCMConStat[4]   = abyVCU_CAN1_Recv_MCU_S_2_DCU5[6];
            //abyMotorErrCode[4] = abyVCU_CAN1_Recv_MCU_S_2_DCU5[7];
            break;        
        }
       

        
        case DCU6_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            //aiContFrontVolt[5] = (((abyVCU_CAN1_Recv_MCU_S_2_DCU6[1] << 8) + abyVCU_CAN1_Recv_MCU_S_2_DCU6[0]) - 10000) * 0.1;
            //abyMotorTemp[5]    = abyVCU_CAN1_Recv_MCU_S_2_DCU6[2] - 40;                                          
            //abyMCMTemp[5]      = abyVCU_CAN1_Recv_MCU_S_2_DCU6[3] - 40;
            //aiMCMRectCur[5]    = ((int)(abyVCU_CAN1_Recv_MCU_S_2_DCU6[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_2_DCU6[4];
            //abyMCMConStat[5]   = abyVCU_CAN1_Recv_MCU_S_2_DCU6[6];
            //abyMotorErrCode[5] = abyVCU_CAN1_Recv_MCU_S_2_DCU6[7];
            break;        
        }
        
        case DCU7_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            //aiContFrontVolt[6] = (((abyVCU_CAN1_Recv_MCU_S_2_DCU7[1] << 8) + abyVCU_CAN1_Recv_MCU_S_2_DCU7[0]) - 10000) * 0.1;
            //abyMotorTemp[6]    = abyVCU_CAN1_Recv_MCU_S_2_DCU7[2] - 40;
            //abyMCMTemp[6]      = abyVCU_CAN1_Recv_MCU_S_2_DCU7[3] - 40;
            //aiMCMRectCur[6]    = ((int)(abyVCU_CAN1_Recv_MCU_S_2_DCU7[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_2_DCU7[4];
            //abyMCMConStat[6]   = abyVCU_CAN1_Recv_MCU_S_2_DCU7[6];
            //abyMotorErrCode[6] = abyVCU_CAN1_Recv_MCU_S_2_DCU7[7];
            break;        
        }
        
        case DCU8_VCU_Info2:                    //RECORD_B_MSG_BOX[8]数组装载报文
        {
            //aiContFrontVolt[7] = (((abyVCU_CAN1_Recv_MCU_S_2_DCU8[1] << 8) + abyVCU_CAN1_Recv_MCU_S_2_DCU8[0]) - 10000) * 0.1;
            //abyMotorTemp[7]    = abyVCU_CAN1_Recv_MCU_S_2_DCU8[2] - 40;
            //abyMCMTemp[7]      = abyVCU_CAN1_Recv_MCU_S_2_DCU8[3] - 40;
            //aiMCMRectCur[7]    = ((int)(abyVCU_CAN1_Recv_MCU_S_2_DCU8[5]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_2_DCU8[4];
            //abyMCMConStat[7]   = abyVCU_CAN1_Recv_MCU_S_2_DCU8[6];
            //abyMotorErrCode[7] = abyVCU_CAN1_Recv_MCU_S_2_DCU8[7];
            break;        
        }        
        
        
        


       
       
       
       
       
       
       
        
        default: break;
    }   
}


//-----------------------------------------CAN3  发送 函数-------------------------------------------
void CAN3_transfer_load(byte num,unsigned long ID)      //设置发送报文编号和ID
{unsigned long ID_temp;
 byte pf;
 Word temp;
 ID_temp=ID;
 pf=(num-1);
 AcquireAccessToSharedMemory(can_semaphore_mcu);//锁定
 switch(num)
 {
     case VCU2:            //装载报文3
     { 
         CAN3_TxBuffer_box[0][0]=(byte)bySelfState;
         CAN3_TxBuffer_box[0][1]=(byte)(((byDoor4State << 6) & 0x40) + ((byDoor3State << 4) & 0x10) + (byContactCmd & 0x01));
         CAN3_TxBuffer_box[0][2]=(byte)byTrainSpeed;
         CAN3_TxBuffer_box[0][3]=(byte)0;
         CAN3_TxBuffer_box[0][4]=(byte)(aiCurHeight[0] & 0x00FF);
         CAN3_TxBuffer_box[0][5]=(byte)((aiCurHeight[0] & 0xFF00) >> 8);
         CAN3_TxBuffer_box[0][6]=(byte)(aiCurHeight[1] & 0x00FF);
         CAN3_TxBuffer_box[0][7]=(byte)((aiCurHeight[1] & 0xFF00) >> 8);
         
         Set_CAN_ID(ID_temp,3,pf);         //设置ID
      CAN3_transfer_start(pf,1);
  break;
  }
     case VCU_To_BMS1:     //装载报文2
     {
         CAN3_TxBuffer_box[1][0]=(byte)byVCU_Ctrl_BMS1;      
         CAN3_TxBuffer_box[1][1]=0;     
         CAN3_TxBuffer_box[1][2]=0;      
         CAN3_TxBuffer_box[1][3]=0;     
         CAN3_TxBuffer_box[1][4]=0;  
         CAN3_TxBuffer_box[1][5]=0;                          
         CAN3_TxBuffer_box[1][6]=0;  
         CAN3_TxBuffer_box[1][7]=0;          
         
         Set_CAN_ID(ID_temp,3,pf);         //设置ID
      CAN3_transfer_start(pf,1);
  break;
  }
     case VCU_To_BMS2:     //装载报文2
     {
         CAN3_TxBuffer_box[2][0]=(byte)byVCU_Ctrl_BMS2;      
         CAN3_TxBuffer_box[2][1]=0;     
         CAN3_TxBuffer_box[2][2]=0;      
         CAN3_TxBuffer_box[2][3]=0;     
         CAN3_TxBuffer_box[2][4]=0;  
         CAN3_TxBuffer_box[2][5]=0;                          
         CAN3_TxBuffer_box[2][6]=0;  
         CAN3_TxBuffer_box[2][7]=0;          
         
         Set_CAN_ID(ID_temp,3,pf);         //设置ID
      CAN3_transfer_start(pf,1);
  break;
  }
     
  
     case VCU3_To_HMI14:   //装载报文3
     {
         //CAN1_TxBuffer_box[2][0]=(byte)(0xFF); 
         //CAN1_TxBuffer_box[2][1]=(byte)(0xFF); 
         //CAN1_TxBuffer_box[2][2]=(byte)(0xFF);  
         //CAN1_TxBuffer_box[2][3]=(byte)(0xFF);    
         //CAN1_TxBuffer_box[2][4]=(byte)(0xFF);      
         //CAN1_TxBuffer_box[2][5]=(byte)(0xFF);   
         //CAN1_TxBuffer_box[2][6]=(byte)(0xFF);        
         //CAN1_TxBuffer_box[2][7]=(byte)(0xFF);     
         
         //Set_CAN_ID(ID_temp,1,pf);         //设置ID
      //CAN1_transfer_start(pf,1);
  break;
  }
  
  
     case VCU3_To_HMI23:            // 装载报文4
     {
        
         //CAN1_TxBuffer_box[3][0]=(byte)(0xFF); 
         //CAN1_TxBuffer_box[3][1]=(byte)(0xFF); 
         //CAN1_TxBuffer_box[3][2]=(byte)(0xFF); 
                                                                         
        // CAN1_TxBuffer_box[3][3]=(byte)(0xFF); 
        // CAN1_TxBuffer_box[3][4]=(byte)(0xFF); 
        // CAN1_TxBuffer_box[3][5]=(byte)(0xFF);      
        // CAN1_TxBuffer_box[3][6]=(byte)(0xFF);         
        // CAN1_TxBuffer_box[3][7]=(byte)(0xFF);       
         
        // Set_CAN_ID(ID_temp,1,pf);         //设置ID
        // CAN1_transfer_start(pf, 1);
        // break;
  }
  

  default: break;
 
 }

 ReleaseAccessToSharedMemory(can_semaphore_mcu);//解锁



}


int CAN3_transfer_start(byte pf,byte Ext) 
{
  byte can3tx;
  int cnt=0;
  byte i;
  i = pf;
  if (!CAN3TFLG) return IS_ERR;            //查询发送buffer是否为空       
  CAN3TBSEL = CAN3TFLG;                    //选择最低位空的buffer作为发送寄存器
  can3tx    = CAN3TBSEL;                   //备份选择的发送缓存
  if(1==Ext) 
  {  
    CAN3TXIDR0 =CAN3_ID_box[i][0];
    CAN3TXIDR1 =CAN3_ID_box[i][1]; 
    CAN3TXIDR2 =CAN3_ID_box[i][2]; 
    CAN3TXIDR3 =CAN3_ID_box[i][3]; 
  } 
  else 
  {
    CAN3TXIDR0 =  ((CAN3_ID_box[i][2]&0x0F)<<4)|((CAN3_ID_box[i][3]&0xF0)>>4);
    CAN3TXIDR1 = (CAN3_ID_box[i][3]&0x0E)<<4;
  }
  CAN3TXDLR = 8;                       //指定数据长度
  CAN3TXTBPR= 1;                       //设置发送优先级
  CAN3TXDSR0 = CAN3_TxBuffer_box[i][0];              //写入发送内容
  CAN3TXDSR1 = CAN3_TxBuffer_box[i][1];
  CAN3TXDSR2 = CAN3_TxBuffer_box[i][2];
  CAN3TXDSR3 = CAN3_TxBuffer_box[i][3];
  CAN3TXDSR4 = CAN3_TxBuffer_box[i][4];
  CAN3TXDSR5 = CAN3_TxBuffer_box[i][5];
  CAN3TXDSR6 = CAN3_TxBuffer_box[i][6];
  CAN3TXDSR7 = CAN3_TxBuffer_box[i][7];

  CAN3TFLG = can3tx;                             //开始传送；
  
  while ((CAN3TFLG & can3tx) != can3tx)
  if(++cnt>10000) return IS_ERR; 
  return NO_ERR; 
}



//----------------------------------------CAN3接收----------------------------------------------------------

void CAN3receive(void)
{
    unsigned long ID=0;
    
    // liuchao start
    static Byte flag = 0;
    static Byte getEditContentFlag = 0;
    Byte i = 0;
    // liuchao end	
    
    
    
    
    ID=GET_ID(CAN3);    //获取ID
    switch(ID) 
    {
        case From_Other_VCU:               //如果ID为所需ID  则装载ID对应的报文值
        {
            abyVCU_CAN3_Recv_From_Other_VCU[0]=CAN3RXDSR0;
            abyVCU_CAN3_Recv_From_Other_VCU[1]=CAN3RXDSR1;
            abyVCU_CAN3_Recv_From_Other_VCU[2]=CAN3RXDSR2;
            abyVCU_CAN3_Recv_From_Other_VCU[3]=CAN3RXDSR3;
            abyVCU_CAN3_Recv_From_Other_VCU[4]=CAN3RXDSR4;
            abyVCU_CAN3_Recv_From_Other_VCU[5]=CAN3RXDSR5;
            abyVCU_CAN3_Recv_From_Other_VCU[6]=CAN3RXDSR6;
            abyVCU_CAN3_Recv_From_Other_VCU[7]=CAN3RXDSR7;
            break;
        }
        
        case BMS1_MainInfo1:
        {
            abyVCU_CAN3_Recv_BMS1_MainInfo1[0]=CAN3RXDSR0;
            abyVCU_CAN3_Recv_BMS1_MainInfo1[1]=CAN3RXDSR1;
            abyVCU_CAN3_Recv_BMS1_MainInfo1[2]=CAN3RXDSR2;
            abyVCU_CAN3_Recv_BMS1_MainInfo1[3]=CAN3RXDSR3;
            abyVCU_CAN3_Recv_BMS1_MainInfo1[4]=CAN3RXDSR4;
            abyVCU_CAN3_Recv_BMS1_MainInfo1[5]=CAN3RXDSR5;
            abyVCU_CAN3_Recv_BMS1_MainInfo1[6]=CAN3RXDSR6;
            abyVCU_CAN3_Recv_BMS1_MainInfo1[7]=CAN3RXDSR7;
            break;
        }
        
        case BMS2_MainInfo1:
        {
            abyVCU_CAN3_Recv_BMS2_MainInfo1[0]=CAN3RXDSR0;
            abyVCU_CAN3_Recv_BMS2_MainInfo1[1]=CAN3RXDSR1;
            abyVCU_CAN3_Recv_BMS2_MainInfo1[2]=CAN3RXDSR2;
            abyVCU_CAN3_Recv_BMS2_MainInfo1[3]=CAN3RXDSR3;
            abyVCU_CAN3_Recv_BMS2_MainInfo1[4]=CAN3RXDSR4;
            abyVCU_CAN3_Recv_BMS2_MainInfo1[5]=CAN3RXDSR5;
            abyVCU_CAN3_Recv_BMS2_MainInfo1[6]=CAN3RXDSR6;
            abyVCU_CAN3_Recv_BMS2_MainInfo1[7]=CAN3RXDSR7;
            break;
        }
        
        case BMS1_MainInfo2:
        {
            abyVCU_CAN3_Recv_BMS1_MainInfo2[0]=CAN3RXDSR0;
            abyVCU_CAN3_Recv_BMS1_MainInfo2[1]=CAN3RXDSR1;
            abyVCU_CAN3_Recv_BMS1_MainInfo2[2]=CAN3RXDSR2;
            abyVCU_CAN3_Recv_BMS1_MainInfo2[3]=CAN3RXDSR3;
            abyVCU_CAN3_Recv_BMS1_MainInfo2[4]=CAN3RXDSR4;
            abyVCU_CAN3_Recv_BMS1_MainInfo2[5]=CAN3RXDSR5;
            abyVCU_CAN3_Recv_BMS1_MainInfo2[6]=CAN3RXDSR6;
            abyVCU_CAN3_Recv_BMS1_MainInfo2[7]=CAN3RXDSR7;
            break;
        }
        
        case BMS2_MainInfo2:
        {
            abyVCU_CAN3_Recv_BMS2_MainInfo2[0]=CAN3RXDSR0;
            abyVCU_CAN3_Recv_BMS2_MainInfo2[1]=CAN3RXDSR1;
            abyVCU_CAN3_Recv_BMS2_MainInfo2[2]=CAN3RXDSR2;
            abyVCU_CAN3_Recv_BMS2_MainInfo2[3]=CAN3RXDSR3;
            abyVCU_CAN3_Recv_BMS2_MainInfo2[4]=CAN3RXDSR4;
            abyVCU_CAN3_Recv_BMS2_MainInfo2[5]=CAN3RXDSR5;
            abyVCU_CAN3_Recv_BMS2_MainInfo2[6]=CAN3RXDSR6;
            abyVCU_CAN3_Recv_BMS2_MainInfo2[7]=CAN3RXDSR7;
            break;
        }
        
        case BMS1_AddInfo:
        {
            abyVCU_CAN3_Recv_BMS1_AddInfo[0]=CAN3RXDSR0;
            abyVCU_CAN3_Recv_BMS1_AddInfo[1]=CAN3RXDSR1;
            abyVCU_CAN3_Recv_BMS1_AddInfo[2]=CAN3RXDSR2;
            abyVCU_CAN3_Recv_BMS1_AddInfo[3]=CAN3RXDSR3;
            abyVCU_CAN3_Recv_BMS1_AddInfo[4]=CAN3RXDSR4;
            abyVCU_CAN3_Recv_BMS1_AddInfo[5]=CAN3RXDSR5;
            abyVCU_CAN3_Recv_BMS1_AddInfo[6]=CAN3RXDSR6;
            abyVCU_CAN3_Recv_BMS1_AddInfo[7]=CAN3RXDSR7;
            break;
        }
        
        case BMS2_AddInfo:
        {
            abyVCU_CAN3_Recv_BMS2_AddInfo[0]=CAN3RXDSR0;
            abyVCU_CAN3_Recv_BMS2_AddInfo[1]=CAN3RXDSR1;
            abyVCU_CAN3_Recv_BMS2_AddInfo[2]=CAN3RXDSR2;
            abyVCU_CAN3_Recv_BMS2_AddInfo[3]=CAN3RXDSR3;
            abyVCU_CAN3_Recv_BMS2_AddInfo[4]=CAN3RXDSR4;
            abyVCU_CAN3_Recv_BMS2_AddInfo[5]=CAN3RXDSR5;
            abyVCU_CAN3_Recv_BMS2_AddInfo[6]=CAN3RXDSR6;
            abyVCU_CAN3_Recv_BMS2_AddInfo[7]=CAN3RXDSR7;
            break;
        }
        
        case BMS1_MaxPow:
        {
            abyVCU_CAN3_Recv_BMS1_MaxPow[0]=CAN3RXDSR0;
            abyVCU_CAN3_Recv_BMS1_MaxPow[1]=CAN3RXDSR1;
            abyVCU_CAN3_Recv_BMS1_MaxPow[2]=CAN3RXDSR2;
            abyVCU_CAN3_Recv_BMS1_MaxPow[3]=CAN3RXDSR3;
            abyVCU_CAN3_Recv_BMS1_MaxPow[4]=CAN3RXDSR4;
            abyVCU_CAN3_Recv_BMS1_MaxPow[5]=CAN3RXDSR5;
            abyVCU_CAN3_Recv_BMS1_MaxPow[6]=CAN3RXDSR6;
            abyVCU_CAN3_Recv_BMS1_MaxPow[7]=CAN3RXDSR7;
            break;
        }
        
        case BMS2_MaxPow:
        {
            abyVCU_CAN3_Recv_BMS2_MaxPow[0]=CAN3RXDSR0;
            abyVCU_CAN3_Recv_BMS2_MaxPow[1]=CAN3RXDSR1;
            abyVCU_CAN3_Recv_BMS2_MaxPow[2]=CAN3RXDSR2;
            abyVCU_CAN3_Recv_BMS2_MaxPow[3]=CAN3RXDSR3;
            abyVCU_CAN3_Recv_BMS2_MaxPow[4]=CAN3RXDSR4;
            abyVCU_CAN3_Recv_BMS2_MaxPow[5]=CAN3RXDSR5;
            abyVCU_CAN3_Recv_BMS2_MaxPow[6]=CAN3RXDSR6;
            abyVCU_CAN3_Recv_BMS2_MaxPow[7]=CAN3RXDSR7;
            break;
        }
        
        case BMS1_Isolation:
        {
            abyVCU_CAN3_Recv_BMS1_Isolation[0]=CAN3RXDSR0;
            abyVCU_CAN3_Recv_BMS1_Isolation[1]=CAN3RXDSR1;
            abyVCU_CAN3_Recv_BMS1_Isolation[2]=CAN3RXDSR2;
            abyVCU_CAN3_Recv_BMS1_Isolation[3]=CAN3RXDSR3;
            abyVCU_CAN3_Recv_BMS1_Isolation[4]=CAN3RXDSR4;
            abyVCU_CAN3_Recv_BMS1_Isolation[5]=CAN3RXDSR5;
            abyVCU_CAN3_Recv_BMS1_Isolation[6]=CAN3RXDSR6;
            abyVCU_CAN3_Recv_BMS1_Isolation[7]=CAN3RXDSR7;
            break;
        }
        
        case BMS2_Isolation:
        {
            abyVCU_CAN3_Recv_BMS2_Isolation[0]=CAN3RXDSR0;
            abyVCU_CAN3_Recv_BMS2_Isolation[1]=CAN3RXDSR1;
            abyVCU_CAN3_Recv_BMS2_Isolation[2]=CAN3RXDSR2;
            abyVCU_CAN3_Recv_BMS2_Isolation[3]=CAN3RXDSR3;
            abyVCU_CAN3_Recv_BMS2_Isolation[4]=CAN3RXDSR4;
            abyVCU_CAN3_Recv_BMS2_Isolation[5]=CAN3RXDSR5;
            abyVCU_CAN3_Recv_BMS2_Isolation[6]=CAN3RXDSR6;
            abyVCU_CAN3_Recv_BMS2_Isolation[7]=CAN3RXDSR7;
            break;
        }
        
        case BMS1_Others:
        {
            abyVCU_CAN3_Recv_BMS1_Others[0]=CAN3RXDSR0;
            abyVCU_CAN3_Recv_BMS1_Others[1]=CAN3RXDSR1;
            abyVCU_CAN3_Recv_BMS1_Others[2]=CAN3RXDSR2;
            abyVCU_CAN3_Recv_BMS1_Others[3]=CAN3RXDSR3;
            abyVCU_CAN3_Recv_BMS1_Others[4]=CAN3RXDSR4;
            abyVCU_CAN3_Recv_BMS1_Others[5]=CAN3RXDSR5;
            abyVCU_CAN3_Recv_BMS1_Others[6]=CAN3RXDSR6;
            abyVCU_CAN3_Recv_BMS1_Others[7]=CAN3RXDSR7;
            break;
        }
        
        case BMS2_Others:
        {
            abyVCU_CAN3_Recv_BMS2_Others[0]=CAN3RXDSR0;
            abyVCU_CAN3_Recv_BMS2_Others[1]=CAN3RXDSR1;
            abyVCU_CAN3_Recv_BMS2_Others[2]=CAN3RXDSR2;
            abyVCU_CAN3_Recv_BMS2_Others[3]=CAN3RXDSR3;
            abyVCU_CAN3_Recv_BMS2_Others[4]=CAN3RXDSR4;
            abyVCU_CAN3_Recv_BMS2_Others[5]=CAN3RXDSR5;
            abyVCU_CAN3_Recv_BMS2_Others[6]=CAN3RXDSR6;
            abyVCU_CAN3_Recv_BMS2_Others[7]=CAN3RXDSR7;
            break;
        }
        
        
        default:break;
    }
  
}

/************************************************************************
** 函数名称：CAN3_DistillMessage()                                    **
** 函数功能：CAN3_DistillMessage                                      **
                                                  
** 备    注：对CAN3接受报文数据解码，并赋值给相应变量，本地函数       **
************************************************************************/ 

void CAN3_DistillMessage()
{	
    unsigned long ID=0;
    
    ID=GET_ID(CAN3);          //获取CAN0上报文
    
    switch (ID) 
    {
       case From_Other_VCU:               //如果ID为所需ID  则装载ID对应的报文值
       {
           byOtherState   = abyVCU_CAN3_Recv_From_Other_VCU[0];
           byDoor2State   = (Byte)((abyVCU_CAN3_Recv_From_Other_VCU[1] & 0x40) >> 6);
           byDoor1State   = (Byte)((abyVCU_CAN3_Recv_From_Other_VCU[1] & 0x10) >> 4);
           byContactReq   = (Byte)(abyVCU_CAN3_Recv_From_Other_VCU[1] & 0x01);
           aiCurHeight[2] = ((int)(abyVCU_CAN3_Recv_From_Other_VCU[5]) << 8) + (int)abyVCU_CAN3_Recv_From_Other_VCU[4];
           aiCurHeight[3] = ((int)(abyVCU_CAN3_Recv_From_Other_VCU[7]) << 8) + (int)abyVCU_CAN3_Recv_From_Other_VCU[6];
           break;
       }
       case BMS1_MainInfo1:
       {
           iMainsVoltage_BMS1   = ((abyVCU_CAN3_Recv_BMS1_MainInfo1[1] << 8) + abyVCU_CAN3_Recv_BMS1_MainInfo1[0]) * 0.1;
           iMainsCurrent_BMS1   = (((abyVCU_CAN3_Recv_BMS1_MainInfo1[3] << 8) + abyVCU_CAN3_Recv_BMS1_MainInfo1[2]) - 32000) * 0.1;
           bySOC_BMS1           = (byte)(abyVCU_CAN3_Recv_BMS1_MainInfo1[4] * 0.4);
           byHighTemp_BMS1      = abyVCU_CAN3_Recv_BMS1_MainInfo1[5] & 0x030;
           byLowTemp_BMS1       = abyVCU_CAN3_Recv_BMS1_MainInfo1[5] & 0x0C;
           byOverDisCharge_BMS1 = abyVCU_CAN3_Recv_BMS1_MainInfo1[5] & 0x30;
           byOverCharge_BMS1    = abyVCU_CAN3_Recv_BMS1_MainInfo1[5] & 0xC0;
           byVoltConsist_BMS1   = abyVCU_CAN3_Recv_BMS1_MainInfo1[6] & 0x03;
           byCommFault_BMS1     = abyVCU_CAN3_Recv_BMS1_MainInfo1[6] & 0x0C;
           byTempControl_BMS1   = abyVCU_CAN3_Recv_BMS1_MainInfo1[6] & 0x30;
           byChargingStat_BMS1  = abyVCU_CAN3_Recv_BMS1_MainInfo1[6] & 0xC0;
           byBalanceStat_BMS1   = abyVCU_CAN3_Recv_BMS1_MainInfo1[7] & 0x03;
           byCurStat_BMS1       = abyVCU_CAN3_Recv_BMS1_MainInfo1[7] & 0x0C;
           byInsStat_BMS1       = abyVCU_CAN3_Recv_BMS1_MainInfo1[7] & 0x30;
           //byReady_BMS1         = (abyVCU_CAN3_Recv_BMS1_MainInfo1[7]>>6) & 0x03;   //shenmin
           break;
       }
       case BMS2_MainInfo1:
       {
           iMainsVoltage_BMS2   = ((abyVCU_CAN3_Recv_BMS2_MainInfo1[1] << 8) + (int)abyVCU_CAN3_Recv_BMS2_MainInfo1[0]) * 0.1;
           iMainsCurrent_BMS2   = (((abyVCU_CAN3_Recv_BMS2_MainInfo1[3] << 8) + abyVCU_CAN3_Recv_BMS2_MainInfo1[2]) - 32000) * 0.1;
           bySOC_BMS2           = (byte)(abyVCU_CAN3_Recv_BMS2_MainInfo1[4] * 0.4);
           byHighTemp_BMS2      = abyVCU_CAN3_Recv_BMS2_MainInfo1[5] & 0x03;
           byLowTemp_BMS2       = abyVCU_CAN3_Recv_BMS2_MainInfo1[5] & 0x0C;
           byOverDisCharge_BMS2 = abyVCU_CAN3_Recv_BMS2_MainInfo1[5] & 0x30;
           byOverCharge_BMS2    = abyVCU_CAN3_Recv_BMS2_MainInfo1[5] & 0xC0;
           byVoltConsist_BMS2   = abyVCU_CAN3_Recv_BMS2_MainInfo1[6] & 0x03;
           byCommFault_BMS2     = abyVCU_CAN3_Recv_BMS2_MainInfo1[6] & 0x0C;
           byTempControl_BMS2   = abyVCU_CAN3_Recv_BMS2_MainInfo1[6] & 0x30;
           byChargingStat_BMS2  = abyVCU_CAN3_Recv_BMS2_MainInfo1[6] & 0xC0;
           byBalanceStat_BMS2   = abyVCU_CAN3_Recv_BMS2_MainInfo1[7] & 0x03;
           byCurStat_BMS2       = abyVCU_CAN3_Recv_BMS2_MainInfo1[7] & 0x0C;
           byInsStat_BMS2       = abyVCU_CAN3_Recv_BMS2_MainInfo1[7] & 0x30;
           //byReady_BMS2         = (abyVCU_CAN3_Recv_BMS2_MainInfo1[7]>>6) & 0x03;    //shenmin
           break;
       }
       case BMS1_MainInfo2:
       {
           byChgPlugin_BMS1 = abyVCU_CAN3_Recv_BMS1_MainInfo2[0] & 0x05;
           byHVClsStat_BMS1 = abyVCU_CAN3_Recv_BMS1_MainInfo2[0] & 0x20;
           break;
       }
      
       case BMS2_MainInfo2:
       {
           byChgPlugin_BMS2 = abyVCU_CAN3_Recv_BMS2_MainInfo2[0] & 0x05;
           byHVClsStat_BMS2 = abyVCU_CAN3_Recv_BMS2_MainInfo2[0] & 0x20;
           break;
       }
       
       case BMS1_AddInfo:
       {
           bySOH_BMS1          = abyVCU_CAN3_Recv_BMS1_AddInfo[0];
           iTotalCapacity_BMS1 = ((int)(abyVCU_CAN3_Recv_BMS1_AddInfo[2]) << 8) + (int)abyVCU_CAN3_Recv_BMS1_AddInfo[1];
           break;
       }
      
       case BMS2_AddInfo:
       {
           bySOH_BMS2          = abyVCU_CAN3_Recv_BMS2_AddInfo[0];
           iTotalCapacity_BMS2 = ((int)(abyVCU_CAN3_Recv_BMS2_AddInfo[2]) << 8) + (int)abyVCU_CAN3_Recv_BMS2_AddInfo[1];
           break;
       }
       
       case BMS1_MaxPow:
       {
           
           break;
       }
      
       case BMS2_MaxPow:
       {
           
           break;
       }
       
       case BMS1_Isolation:
       {
           
           break;
       }
      
       case BMS2_Isolation:
       {
           
           break;
       }
       
       case BMS1_Others:
       {
           //byReq_HVBreak_FromBMS1 = abyVCU_CAN3_Recv_BMS1_Others[0] & 0x03;  //shenmin
           break;
       }
      
       case BMS2_Others:
       {
           //byReq_HVBreak_FromBMS2 = abyVCU_CAN3_Recv_BMS2_Others[0] & 0x03;    //shenmin
           break;
       }
       
       case HMI1_VCU23:
       {
           //abyVCU_CAN0_Recv_HMI1_VCU23[0]=CAN0RXDSR0;
           //abyVCU_CAN0_Recv_HMI1_VCU23[1]=CAN0RXDSR1;
           //abyVCU_CAN0_Recv_HMI1_VCU23[2]=CAN0RXDSR2;
           //abyVCU_CAN0_Recv_HMI1_VCU23[3]=CAN0RXDSR3;
           //abyVCU_CAN0_Recv_HMI1_VCU23[4]=CAN0RXDSR4;
           //abyVCU_CAN0_Recv_HMI1_VCU23[5]=CAN0RXDSR5;
           //abyVCU_CAN0_Recv_HMI1_VCU23[6]=CAN0RXDSR6;
           //abyVCU_CAN0_Recv_HMI1_VCU23[7]=CAN0RXDSR7;
           break;
       }
       case HMI4_VCU23:
       {
           //abyVCU_CAN0_Recv_HMI4_VCU23[0]=CAN0RXDSR0;
           //abyVCU_CAN0_Recv_HMI4_VCU23[1]=CAN0RXDSR1;
           //abyVCU_CAN0_Recv_HMI4_VCU23[2]=CAN0RXDSR2;
           //abyVCU_CAN0_Recv_HMI4_VCU23[3]=CAN0RXDSR3;
           //abyVCU_CAN0_Recv_HMI4_VCU23[4]=CAN0RXDSR4;
           //abyVCU_CAN0_Recv_HMI4_VCU23[5]=CAN0RXDSR5;
           //abyVCU_CAN0_Recv_HMI4_VCU23[6]=CAN0RXDSR6;
           //abyVCU_CAN0_Recv_HMI4_VCU23[7]=CAN0RXDSR7;
           break;
       }  
    
    
    }
     
     
     
     
     
     
     
}
	

//-----------------------------------------CAN2  发送 函数-------------------------------------------
void CAN2_transfer_load(byte num,unsigned long ID) 
{
   unsigned long ID_temp;
   byte pf;
   Word temp;
   ID_temp=ID;
   pf=(num-1);
   AcquireAccessToSharedMemory(can_semaphore_mcu);//锁定
   switch(num)
   {
       case VCU_ACU: 
       {    
           CAN2_TxBuffer_box[0][0]=(byte)byDCDCComm_1;
           CAN2_TxBuffer_box[0][1]=(byte)byDCACComm_1;
           CAN2_TxBuffer_box[0][2]=(byte)byDCDCComm_2;
           CAN2_TxBuffer_box[0][3]=(byte)byDCACComm_2;
           CAN2_TxBuffer_box[0][4]=(byte)byDCDCComm_3;
           CAN2_TxBuffer_box[0][5]=(byte)byDCACComm_3;
           CAN2_TxBuffer_box[0][6]=(byte)byDCDCComm_4;
           CAN2_TxBuffer_box[0][7]=(byte)byDCACComm_4;

       Set_CAN_ID(ID_temp,2,pf);         //设置ID
       CAN2_transfer_start(pf,1);
    break;
    }
  
    default: break;
   
   }
   ReleaseAccessToSharedMemory(can_semaphore_mcu);//解锁



}

int CAN2_transfer_start(byte pf,byte Ext) 
{
  byte can2tx;
  int cnt=0;
  byte i;
  i = pf;
  if (!CAN2TFLG) return IS_ERR;            //查询发送buffer是否为空       
  CAN2TBSEL = CAN2TFLG;                    //选择最低位空的buffer作为发送寄存器
  can2tx    = CAN2TBSEL;                   //备份选择的发送缓存
  if(1==Ext) 
  {  
    CAN2TXIDR0 =CAN2_ID_box[i][0];
    CAN2TXIDR1 =CAN2_ID_box[i][1]; 
    CAN2TXIDR2 =CAN2_ID_box[i][2]; 
    CAN2TXIDR3 =CAN2_ID_box[i][3]; 
  } 
  else 
  {
    CAN2TXIDR0 =  ((CAN2_ID_box[i][2]&0x0F)<<4)|((CAN2_ID_box[i][3]&0xF0)>>4);
    CAN2TXIDR1 = (CAN2_ID_box[i][3]&0x0E)<<4;
  }
  CAN2TXDLR = 8;                       //指定数据长度
  CAN2TXTBPR= 1;                       //设置发送优先级
  CAN2TXDSR0 = CAN2_TxBuffer_box[i][0];              //写入发送内容
  CAN2TXDSR1 = CAN2_TxBuffer_box[i][1];
  CAN2TXDSR2 = CAN2_TxBuffer_box[i][2];
  CAN2TXDSR3 = CAN2_TxBuffer_box[i][3];
  CAN2TXDSR4 = CAN2_TxBuffer_box[i][4];
  CAN2TXDSR5 = CAN2_TxBuffer_box[i][5];
  CAN2TXDSR6 = CAN2_TxBuffer_box[i][6];
  CAN2TXDSR7 = CAN2_TxBuffer_box[i][7];

  CAN2TFLG = can2tx;                             //开始传送；
  
  while ((CAN2TFLG & can2tx) != can2tx)
  if(++cnt>10000) return IS_ERR; 
  return NO_ERR; 
}



//----------------------------------------CAN2接收----------------------------------------------------------

void CAN2receive(void)
{   
	  unsigned long ID=0;
#if 0                       //shenmin
    ID=GET_ID(CAN2);        //获取ID
    switch(ID)
    {
        case ACU_VCU_DCDC_1: 
        {
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[0]=CAN2RXDSR0;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[1]=CAN2RXDSR1;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[2]=CAN2RXDSR2;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[3]=CAN2RXDSR3;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[4]=CAN2RXDSR4;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[5]=CAN2RXDSR5;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[6]=CAN2RXDSR6;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[7]=CAN2RXDSR7;
            break;
        }
        
        case ACU_VCU_DCAC_1: 
        {
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[0]=CAN2RXDSR0;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[1]=CAN2RXDSR1;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[2]=CAN2RXDSR2;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[3]=CAN2RXDSR3;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[4]=CAN2RXDSR4;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[5]=CAN2RXDSR5;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[6]=CAN2RXDSR6;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[7]=CAN2RXDSR7;
            break;
        }
        
        case ACU_VCU_DCDC_2: 
        {
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[0]=CAN2RXDSR0;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[1]=CAN2RXDSR1;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[2]=CAN2RXDSR2;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[3]=CAN2RXDSR3;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[4]=CAN2RXDSR4;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[5]=CAN2RXDSR5;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[6]=CAN2RXDSR6;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[7]=CAN2RXDSR7;
            break;
        }
        
        case ACU_VCU_DCAC_2: 
        {
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[0]=CAN2RXDSR0;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[1]=CAN2RXDSR1;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[2]=CAN2RXDSR2;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[3]=CAN2RXDSR3;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[4]=CAN2RXDSR4;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[5]=CAN2RXDSR5;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[6]=CAN2RXDSR6;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[7]=CAN2RXDSR7;
            break;
        }
        
        case ACU_VCU_DCDC_3: 
        {
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[0]=CAN2RXDSR0;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[1]=CAN2RXDSR1;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[2]=CAN2RXDSR2;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[3]=CAN2RXDSR3;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[4]=CAN2RXDSR4;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[5]=CAN2RXDSR5;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[6]=CAN2RXDSR6;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[7]=CAN2RXDSR7;
            break;
        }
        
        case ACU_VCU_DCAC_3: 
        {
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[0]=CAN2RXDSR0;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[1]=CAN2RXDSR1;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[2]=CAN2RXDSR2;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[3]=CAN2RXDSR3;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[4]=CAN2RXDSR4;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[5]=CAN2RXDSR5;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[6]=CAN2RXDSR6;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[7]=CAN2RXDSR7;
            break;
        }
        
        case ACU_VCU_DCDC_4: 
        {
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[0]=CAN2RXDSR0;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[1]=CAN2RXDSR1;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[2]=CAN2RXDSR2;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[3]=CAN2RXDSR3;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[4]=CAN2RXDSR4;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[5]=CAN2RXDSR5;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[6]=CAN2RXDSR6;
            abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[7]=CAN2RXDSR7;
            break;
        }
        
        case ACU_VCU_DCAC_4: 
        {
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[0]=CAN2RXDSR0;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[1]=CAN2RXDSR1;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[2]=CAN2RXDSR2;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[3]=CAN2RXDSR3;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[4]=CAN2RXDSR4;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[5]=CAN2RXDSR5;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[6]=CAN2RXDSR6;
            abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[7]=CAN2RXDSR7;
            break;
        }
      
      default:break;
    
    }
#endif     //shenmin
}


void CAN2_DistillMessage()   //解析CAN2采集到的报文数据
{
    unsigned long ID=0;
#if 0   //shenmin
    ID=GET_ID(CAN2);        //获取ID
    switch(ID)
    {
        case ACU_VCU_DCDC_1: 
        {
            iDCDC_Output_Volt_1  = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[1]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[0];
            iDCDC_Output_Cur_1   = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[3]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[2];
            iDCDC_Input_Volt_1   = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[5]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[4];
            byDCDC_Temperature_1 = abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[6];
            byDCDC_ErrCode_1     = abyVCU_CAN2_Recv_ACU_VCU_DCDC_1[7];
            break;
        }
        
        case ACU_VCU_DCAC_1: 
        {
            iDCAC_Output_Volt_1  = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[1]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[0];
            iDCAC_Output_Cur_1   = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[3]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[2];
            byDCAC_Temperature_1 = abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[6];
            byDCAC_ErrCode_1     = abyVCU_CAN2_Recv_ACU_VCU_DCAC_1[7];
            break;
        }
        
        case ACU_VCU_DCDC_2: 
        {
            iDCDC_Output_Volt_2  = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[1]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[0];
            iDCDC_Output_Cur_2   = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[3]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[2];
            iDCDC_Input_Volt_2   = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[5]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[4];
            byDCDC_Temperature_2 = abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[6];
            byDCDC_ErrCode_2     = abyVCU_CAN2_Recv_ACU_VCU_DCDC_2[7];
            break;
        }
        
        case ACU_VCU_DCAC_2: 
        {
            iDCAC_Output_Volt_2  = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[1]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[0];
            iDCAC_Output_Cur_2   = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[3]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[2];
            byDCAC_Temperature_2 = abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[6];
            byDCAC_ErrCode_2     = abyVCU_CAN2_Recv_ACU_VCU_DCAC_2[7];
            break;
        }
        
        case ACU_VCU_DCDC_3: 
        {
            iDCDC_Output_Volt_3  = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[1]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[0];
            iDCDC_Output_Cur_3   = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[3]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[2];
            iDCDC_Input_Volt_3   = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[5]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[4];
            byDCDC_Temperature_3 = abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[6];
            byDCDC_ErrCode_3     = abyVCU_CAN2_Recv_ACU_VCU_DCDC_3[7];
            break;
        }
        
        case ACU_VCU_DCAC_3: 
        {
            iDCAC_Output_Volt_3  = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[1]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[0];
            iDCAC_Output_Cur_3   = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[3]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[2];
            byDCAC_Temperature_3 = abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[6];
            byDCAC_ErrCode_3     = abyVCU_CAN2_Recv_ACU_VCU_DCAC_3[7];
            break;
        }
        
        case ACU_VCU_DCDC_4: 
        {
            iDCDC_Output_Volt_4  = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[1]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[0];
            iDCDC_Output_Cur_4   = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[3]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[2];
            iDCDC_Input_Volt_4   = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[5]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[4];
            byDCDC_Temperature_4 = abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[6];
            byDCDC_ErrCode_4     = abyVCU_CAN2_Recv_ACU_VCU_DCDC_4[7];
            break;
        }
        
        case ACU_VCU_DCAC_4: 
        {
            iDCAC_Output_Volt_4  = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[1]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[0];
            iDCAC_Output_Cur_4   = ((int)(abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[3]) << 8) + (int)abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[2];
            byDCAC_Temperature_4 = abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[6];
            byDCAC_ErrCode_4     = abyVCU_CAN2_Recv_ACU_VCU_DCAC_4[7];
            break;
        }
      
        default:break;
    
    }
#endif //shenmin
}


//-----------------------------------------CAN0  发送 函数-------------------------------------------
void CAN0_transfer_load(byte num,unsigned long ID)
{
   
#if 0   //shenmin   
   unsigned long ID_temp;
   byte pf;
   Word temp;
   ID_temp=ID;
   pf=(num-1);
   AcquireAccessToSharedMemory(can_semaphore_mcu);//锁定
   switch(num)
   {
       case VCU2_ID: 
       {    
           CAN0_TxBuffer_box[0][0]=(byte)byCommand1;
           CAN0_TxBuffer_box[0][1]=(byte)byCommand2;
           CAN0_TxBuffer_box[0][2]=(byte)(iDestHeight & 0x00FF);
           CAN0_TxBuffer_box[0][3]=(byte)((iDestHeight & 0xFF00) >> 8);
           CAN0_TxBuffer_box[0][4]=(byte)byBrEffRef;
           CAN0_TxBuffer_box[0][5]=0;
           CAN0_TxBuffer_box[0][6]=0;
           CAN0_TxBuffer_box[0][7]=0;
           
           Set_CAN_ID(ID_temp,0,pf);         //设置ID aiCurHeight
           CAN0_transfer_start(pf, 1);
           break;
       }
       
       case VCU3_ID: 
       {    
           CAN0_TxBuffer_box[1][0]=(byte)(aiCurHeight[0] & 0x00FF);
           CAN0_TxBuffer_box[1][1]=(byte)((aiCurHeight[0] & 0xFF00) >> 8);
           CAN0_TxBuffer_box[1][2]=(byte)(aiCurHeight[1] & 0x00FF);
           CAN0_TxBuffer_box[1][3]=(byte)((aiCurHeight[1] & 0xFF00) >> 8);
           CAN0_TxBuffer_box[1][4]=(byte)(aiCurHeight[2] & 0x00FF);
           CAN0_TxBuffer_box[1][5]=(byte)((aiCurHeight[2] & 0xFF00) >> 8);
           CAN0_TxBuffer_box[1][6]=(byte)(aiCurHeight[3] & 0x00FF);
           CAN0_TxBuffer_box[1][7]=(byte)((aiCurHeight[3] & 0xFF00) >> 8);
           
           Set_CAN_ID(ID_temp,0,pf);         //设置ID
           CAN0_transfer_start(pf, 1);
           break;
       }
    
       default: break;   
   }
   ReleaseAccessToSharedMemory(can_semaphore_mcu);//解锁
#endif  //shenmin 
}

int CAN0_transfer_start(byte pf,byte Ext)  //Ext为1时为扩展帧 0时为标准帧 
{
  byte can0tx;
  int cnt=0;
  byte i;
  i = pf;
  if (!CAN0TFLG) return IS_ERR;            //查询发送buffer是否为空       
  CAN0TBSEL = CAN0TFLG;                    //选择最低位空的buffer作为发送寄存器
  can0tx    = CAN0TBSEL;                   //备份选择的发送缓存
  if(1==Ext) 
  {  
    CAN0TXIDR0 =CAN0_ID_box[i][0];
    CAN0TXIDR1 =CAN0_ID_box[i][1]; 
    CAN0TXIDR2 =CAN0_ID_box[i][2]; 
    CAN0TXIDR3 =CAN0_ID_box[i][3]; 
  } 
  else 
  {
    CAN0TXIDR0 =  ((CAN0_ID_box[i][2]&0x0F)<<4)|((CAN0_ID_box[i][3]&0xF0)>>4);
    CAN0TXIDR1 = (CAN0_ID_box[i][3]&0x0E)<<4;
   
  }
  CAN0TXDLR = 8;                       //指定数据长度
  CAN0TXTBPR= 1;                       //设置发送优先级
  CAN0TXDSR0 = CAN0_TxBuffer_box[i][0];              //写入发送内容
  CAN0TXDSR1 = CAN0_TxBuffer_box[i][1];
  CAN0TXDSR2 = CAN0_TxBuffer_box[i][2];
  CAN0TXDSR3 = CAN0_TxBuffer_box[i][3];
  CAN0TXDSR4 = CAN0_TxBuffer_box[i][4];
  CAN0TXDSR5 = CAN0_TxBuffer_box[i][5];
  CAN0TXDSR6 = CAN0_TxBuffer_box[i][6];
  CAN0TXDSR7 = CAN0_TxBuffer_box[i][7];

  CAN0TFLG = can0tx;                             //开始传送；
  
  while ((CAN0TFLG & can0tx) != can0tx)
  if(++cnt>10000) return IS_ERR; 
  return NO_ERR; 
}

//----------------------------------------CAN2接收----------------------------------------------------------

void CAN0receive(void)
{

     unsigned long ID=0;

    ID=GET_ID(CAN0);
#if 0    //shenmin
    switch(ID)
    {
        case VCU5_VCU_ID: 
        {
            abyVCU_CAN0_Recv_VCU5_VCU_ID[0]=CAN0RXDSR0;
            abyVCU_CAN0_Recv_VCU5_VCU_ID[1]=CAN0RXDSR1;
            abyVCU_CAN0_Recv_VCU5_VCU_ID[2]=CAN0RXDSR2;
            abyVCU_CAN0_Recv_VCU5_VCU_ID[3]=CAN0RXDSR3;
            abyVCU_CAN0_Recv_VCU5_VCU_ID[4]=CAN0RXDSR4;
            abyVCU_CAN0_Recv_VCU5_VCU_ID[5]=CAN0RXDSR5;
            abyVCU_CAN0_Recv_VCU5_VCU_ID[6]=CAN0RXDSR6;
            abyVCU_CAN0_Recv_VCU5_VCU_ID[7]=CAN0RXDSR7;
            break;
        }
        
        case VCU6_VCU_ID: 
        {
            abyVCU_CAN0_Recv_VCU6_VCU_ID[0]=CAN0RXDSR0;
            abyVCU_CAN0_Recv_VCU6_VCU_ID[1]=CAN0RXDSR1;
            abyVCU_CAN0_Recv_VCU6_VCU_ID[2]=CAN0RXDSR2;
            abyVCU_CAN0_Recv_VCU6_VCU_ID[3]=CAN0RXDSR3;
            abyVCU_CAN0_Recv_VCU6_VCU_ID[4]=CAN0RXDSR4;
            abyVCU_CAN0_Recv_VCU6_VCU_ID[5]=CAN0RXDSR5;
            abyVCU_CAN0_Recv_VCU6_VCU_ID[6]=CAN0RXDSR6;
            abyVCU_CAN0_Recv_VCU6_VCU_ID[7]=CAN0RXDSR7;
            break;
        }
        
        case VCU7_VCU_ID: 
        {
            abyVCU_CAN0_Recv_VCU7_VCU_ID[0]=CAN0RXDSR0;
            abyVCU_CAN0_Recv_VCU7_VCU_ID[1]=CAN0RXDSR1;
            abyVCU_CAN0_Recv_VCU7_VCU_ID[2]=CAN0RXDSR2;
            abyVCU_CAN0_Recv_VCU7_VCU_ID[3]=CAN0RXDSR3;
            abyVCU_CAN0_Recv_VCU7_VCU_ID[4]=CAN0RXDSR4;
            abyVCU_CAN0_Recv_VCU7_VCU_ID[5]=CAN0RXDSR5;
            abyVCU_CAN0_Recv_VCU7_VCU_ID[6]=CAN0RXDSR6;
            abyVCU_CAN0_Recv_VCU7_VCU_ID[7]=CAN0RXDSR7;
            break;
        }
        
        case VCU8_VCU_ID: 
        {
            abyVCU_CAN0_Recv_VCU8_VCU_ID[0]=CAN0RXDSR0;
            abyVCU_CAN0_Recv_VCU8_VCU_ID[1]=CAN0RXDSR1;
            abyVCU_CAN0_Recv_VCU8_VCU_ID[2]=CAN0RXDSR2;
            abyVCU_CAN0_Recv_VCU8_VCU_ID[3]=CAN0RXDSR3;
            abyVCU_CAN0_Recv_VCU8_VCU_ID[4]=CAN0RXDSR4;
            abyVCU_CAN0_Recv_VCU8_VCU_ID[5]=CAN0RXDSR5;
            abyVCU_CAN0_Recv_VCU8_VCU_ID[6]=CAN0RXDSR6;
            abyVCU_CAN0_Recv_VCU8_VCU_ID[7]=CAN0RXDSR7;
            break;
        }
        
        default:break;
    
    }
    //-----------------------------根据获取的ID号，在下面添加报文解析------------------------------
#endif      //shenmin
}

void CAN0_DistillMessage()   //解析CAN3采集到的报文数据
{
    unsigned long ID=0;
#if 0    //shenmin
    ID=GET_ID(CAN0);        //获取ID
    switch(ID)
    {
        case VCU5_VCU_ID: 
        {
            iPump_Pressure_VCU5     = ((int)(abyVCU_CAN0_Recv_VCU5_VCU_ID[1]) << 8) + (int)abyVCU_CAN0_Recv_VCU5_VCU_ID[0];
            iCylinder_Pressure_VCU5 = ((int)(abyVCU_CAN0_Recv_VCU5_VCU_ID[3]) << 8) + (int)abyVCU_CAN0_Recv_VCU5_VCU_ID[2];
            iEnergy_Saving_VCU5     = ((int)(abyVCU_CAN0_Recv_VCU5_VCU_ID[5]) << 8) + (int)abyVCU_CAN0_Recv_VCU5_VCU_ID[4];
            iBrakeEffort_VCU5       = ((int)(abyVCU_CAN0_Recv_VCU5_VCU_ID[7]) << 8) + (int)abyVCU_CAN0_Recv_VCU5_VCU_ID[6];
            break;
        }
        
        case VCU6_VCU_ID: 
        {
            iPump_Pressure_VCU6     = ((int)(abyVCU_CAN0_Recv_VCU6_VCU_ID[1]) << 8) + (int)abyVCU_CAN0_Recv_VCU6_VCU_ID[0];
            iCylinder_Pressure_VCU6 = ((int)(abyVCU_CAN0_Recv_VCU6_VCU_ID[3]) << 8) + (int)abyVCU_CAN0_Recv_VCU6_VCU_ID[2];
            iEnergy_Saving_VCU6     = ((int)(abyVCU_CAN0_Recv_VCU6_VCU_ID[5]) << 8) + (int)abyVCU_CAN0_Recv_VCU6_VCU_ID[4];
            iBrakeEffort_VCU6       = ((int)(abyVCU_CAN0_Recv_VCU6_VCU_ID[7]) << 8) + (int)abyVCU_CAN0_Recv_VCU6_VCU_ID[6];
            break;
        }
        
        case VCU7_VCU_ID: 
        {
            iPump_Pressure_VCU7     = ((int)(abyVCU_CAN0_Recv_VCU7_VCU_ID[1]) << 8) + (int)abyVCU_CAN0_Recv_VCU7_VCU_ID[0];
            iCylinder_Pressure_VCU7 = ((int)(abyVCU_CAN0_Recv_VCU7_VCU_ID[3]) << 8) + (int)abyVCU_CAN0_Recv_VCU7_VCU_ID[2];
            iEnergy_Saving_VCU7     = ((int)(abyVCU_CAN0_Recv_VCU7_VCU_ID[5]) << 8) + (int)abyVCU_CAN0_Recv_VCU7_VCU_ID[4];
            iBrakeEffort_VCU7       = ((int)(abyVCU_CAN0_Recv_VCU7_VCU_ID[7]) << 8) + (int)abyVCU_CAN0_Recv_VCU7_VCU_ID[6];
            break;
        }
        
        case VCU8_VCU_ID: 
        {
            iPump_Pressure_VCU8     = ((int)(abyVCU_CAN0_Recv_VCU8_VCU_ID[1]) << 8) + (int)abyVCU_CAN0_Recv_VCU8_VCU_ID[0];
            iCylinder_Pressure_VCU8 = ((int)(abyVCU_CAN0_Recv_VCU8_VCU_ID[3]) << 8) + (int)abyVCU_CAN0_Recv_VCU8_VCU_ID[2];
            iEnergy_Saving_VCU8     = ((int)(abyVCU_CAN0_Recv_VCU8_VCU_ID[5]) << 8) + (int)abyVCU_CAN0_Recv_VCU8_VCU_ID[4];
            iBrakeEffort_VCU8       = ((int)(abyVCU_CAN0_Recv_VCU8_VCU_ID[7]) << 8) + (int)abyVCU_CAN0_Recv_VCU8_VCU_ID[6];
            break;
        }
        
        default:break;
    
    }
#endif   //shenmin
}
//-------------------------CAN0中断---------------------------------------------------------------
 
#pragma CODE_SEG NON_BANKED 
interrupt  VectorNumber_Vcan0rx  void CAN0receive_isr()                   //
{  
    byte  i = 0 ;

    i = CAN0RFLG_RSTAT; 
    can0r++;
   

    CAN0receive();
    CAN0RFLG_RXF = 1;//清除接收缓存存满中断标志位
} 
 
#pragma CODE_SEG DEFAULT 
 
 
//-------------------------CAN1中断---------------------------------------------------------------
 
#pragma CODE_SEG NON_BANKED 
interrupt  VectorNumber_Vcan1rx  void CAN1receive_isr()                   //
{ 
    byte  i = 0 ;

    i = CAN1RFLG_RSTAT; 
    can1r++;

    CAN1receive();
    CAN1RFLG_RXF = 1;//清除接收缓存存满中断标志位

} 
 
#pragma CODE_SEG DEFAULT  
 
//-------------------------CAN2中断---------------------------------------------------------------
 
#pragma CODE_SEG NON_BANKED 
interrupt  VectorNumber_Vcan2rx  void CAN2receive_isr()                   //
{  
    byte  i = 0 ;

    i = CAN2RFLG_RSTAT; 
    can2r++;


    CAN2receive();
    CAN2RFLG_RXF = 1;//清除接收缓存存满中断标志位  
} 
 
#pragma CODE_SEG DEFAULT  
 
 
 
//-------------------------CAN3中断---------------------------------------------------------------
 
#pragma CODE_SEG NON_BANKED 
interrupt  VectorNumber_Vcan3rx  void CAN3receive_isr()                   //
{  
    byte  i = 0 ;

    i = CAN3RFLG_RSTAT;
    can3r++; 

    CAN3receive();
    CAN3RFLG_RXF = 1;//清除接收缓存存满中断标志位  
} 
 
#pragma CODE_SEG DEFAULT  
  
 
 


void Set_CAN_ID (unsigned long ID,int CAN_NUM,byte pf)   //设置CAN总线ID  ID为所需设置ID   CAN_NUM为所需设置CAN网络通道 从0-3  pf为区分同一总线上不同的ID值
{  unsigned long ID_temp;
   byte pf_temp;
   pf_temp=pf;  
   switch(CAN_NUM)
    {
   case 0:
     ID_temp= ConvertIDTOMSCAN_ID(ID);    // 设置发送ID号
     CAN0_ID[0]= (byte)((ID_temp&0xff000000)>>24);
     CAN0_ID[1]= (byte)((ID_temp&0xff0000)>>16);
     CAN0_ID[2]= (byte)((ID_temp&0xff00)>>8);
     CAN0_ID[3]= (byte)(ID_temp&0xff);
     CAN0_ID_box[pf_temp][0]= CAN0_ID[0];
     CAN0_ID_box[pf_temp][1]= CAN0_ID[1];
     CAN0_ID_box[pf_temp][2]= CAN0_ID[2];
     CAN0_ID_box[pf_temp][3]= CAN0_ID[3];
     break;
     
   case 1:
     ID_temp= ConvertIDTOMSCAN_ID(ID);    // 设置发送ID号
     CAN1_ID[0]= (byte)((ID_temp&0xff000000)>>24);
     CAN1_ID[1]= (byte)((ID_temp&0xff0000)>>16);
     CAN1_ID[2]= (byte)((ID_temp&0xff00)>>8);
     CAN1_ID[3]= (byte)(ID_temp&0xff);
     CAN1_ID_box[pf_temp][0]= CAN1_ID[0];
     CAN1_ID_box[pf_temp][1]= CAN1_ID[1];
     CAN1_ID_box[pf_temp][2]= CAN1_ID[2];
     CAN1_ID_box[pf_temp][3]= CAN1_ID[3];
     break;
     
   case 2:
     ID_temp= ConvertIDTOMSCAN_ID(ID);    // 设置发送ID号
     CAN2_ID[0]= (byte)((ID_temp&0xff000000)>>24);
     CAN2_ID[1]= (byte)((ID_temp&0xff0000)>>16);
     CAN2_ID[2]= (byte)((ID_temp&0xff00)>>8);
     CAN2_ID[3]= (byte)(ID_temp&0xff);
     CAN2_ID_box[pf_temp][0]= CAN2_ID[0];
     CAN2_ID_box[pf_temp][1]= CAN2_ID[1];
     CAN2_ID_box[pf_temp][2]= CAN2_ID[2];
     CAN2_ID_box[pf_temp][3]= CAN2_ID[3];
     break; 
     
   case 3:
     ID_temp= ConvertIDTOMSCAN_ID(ID);    // 设置发送ID号
     CAN3_ID[0]= (byte)((ID_temp&0xff000000)>>24);
     CAN3_ID[1]= (byte)((ID_temp&0xff0000)>>16);
     CAN3_ID[2]= (byte)((ID_temp&0xff00)>>8);
     CAN3_ID[3]= (byte)(ID_temp&0xff);
     CAN3_ID_box[pf_temp][0]= CAN3_ID[0];
     CAN3_ID_box[pf_temp][1]= CAN3_ID[1];
     CAN3_ID_box[pf_temp][2]= CAN3_ID[2];
     CAN3_ID_box[pf_temp][3]= CAN3_ID[3];
     break;  
    default:break; 
      
    }
}

//--------------------------------------------------------------------------------------------------
unsigned long GET_ID(int i)  //获取当前中断通道的ID号    i为对应的CAN通道，0-3通道
{ 
unsigned long ID=0;
unsigned long ID0=0;
unsigned long ID1=0;
unsigned long ID2=0;
unsigned long ID3=0;


switch(i) 
{
  case 0: 
  {
    
        ID0=CAN0RXIDR0;
        ID1=CAN0RXIDR1;
        ID2=CAN0RXIDR2;
        ID3=CAN0RXIDR3;
        if(0!=(ID1&0x08)) 
        {
          ID=((ID0<<24)|(ID1<<16)|(ID2<<8)|ID3);
          ID=((ID&0xFFE00000)>>3|(ID&0x7FFFE)>>1 );
          return ID;
        } 
        else if(0==(ID1&0x08))         //标准帧ID格式
        {
          ID = (((ID0<<8)&0xFF00)|(ID1&0xE0))>>5;
          return ID;
        }
        break;
  }
  case 1: 
  {
    
        ID0=CAN1RXIDR0;
        ID1=CAN1RXIDR1;
        ID2=CAN1RXIDR2;
        ID3=CAN1RXIDR3;
        if(0!=(ID1&0x08)) 
        {
          ID=((ID0<<24)|(ID1<<16)|(ID2<<8)|ID3);
          ID=((ID&0xFFE00000)>>3|(ID&0x7FFFE)>>1 );
          return ID;
        } 
        else if(0==(ID1&0x08))           //标准帧ID格式
        {
          ID = (((ID0<<8)&0xFF00)|(ID1&0xE0))>>5;
          return ID;
        }
        break;
  }

  
  case 2: 
  {
    
        ID0=CAN2RXIDR0;
        ID1=CAN2RXIDR1;
        ID2=CAN2RXIDR2;
        ID3=CAN2RXIDR3;
        if(0!=(ID1&0x08)) 
        {
          ID=((ID0<<24)|(ID1<<16)|(ID2<<8)|ID3);
          ID=((ID&0xFFE00000)>>3|(ID&0x7FFFE)>>1 );
          return ID;
        } 
        else if(0==(ID1&0x08))           //标准帧ID格式
        {
          ID = (((ID0<<8)&0xFF00)|(ID1&0xE0))>>5;
          return ID;
        }
        break;
  }
        
  case 3: 
  {
    
        ID0=CAN3RXIDR0;
        ID1=CAN3RXIDR1;
        ID2=CAN3RXIDR2;
        ID3=CAN3RXIDR3;
        if(0!=(ID1&0x08)) 
        {
          ID=((ID0<<24)|(ID1<<16)|(ID2<<8)|ID3);
          ID=((ID&0xFFE00000)>>3|(ID&0x7FFFE)>>1 );
          return ID;
        } 
        else if(0==(ID1&0x08))            //标准帧ID格式
        {
          ID = (((ID0<<8)&0xFF00)|(ID1&0xE0))>>5;
          return ID;
        }
        break;
  }
  default: 
  return 0;
  break;
  
  
  

}
}






//  liuchao start 
int can0_send(dword ID, byte *buf, int len) 
{
    int cnt = 0;
    byte can0tx;    
    
    Set_CAN_ID(ID, 0, 0);         //设置ID
    
    if (!CAN0TFLG) 
        return IS_ERR;            //查询发送buffer是否为空       
   
    CAN0TBSEL  = CAN0TFLG;                    //选择最低位空的buffer作为发送寄存器
    can0tx     = CAN0TBSEL;                   //备份选择的发送缓存
    CAN0TXIDR0 = CAN0_ID_box[0][0];
    CAN0TXIDR1 = CAN0_ID_box[0][1]; 
    CAN0TXIDR2 = CAN0_ID_box[0][2]; 
    CAN0TXIDR3 = CAN0_ID_box[0][3]; 
    CAN0TXDLR  = len;                       //指定数据长度
    CAN0TXTBPR = 1;                       //设置发送优先级
    
    
    memcpy(CAN0_TxBuffer_box[0], buf, 8);
    
    
    CAN0TXDSR0 = CAN0_TxBuffer_box[0][0];              //写入发送内容
    CAN0TXDSR1 = CAN0_TxBuffer_box[0][1];
    CAN0TXDSR2 = CAN0_TxBuffer_box[0][2];
    CAN0TXDSR3 = CAN0_TxBuffer_box[0][3];
    CAN0TXDSR4 = CAN0_TxBuffer_box[0][4];
    CAN0TXDSR5 = CAN0_TxBuffer_box[0][5];
    CAN0TXDSR6 = CAN0_TxBuffer_box[0][6];
    CAN0TXDSR7 = CAN0_TxBuffer_box[0][7];

    CAN0TFLG = can0tx;                             //开始传送；

    while ((CAN0TFLG & can0tx) != can0tx)
    {
        if (++cnt > 10000) 
            return IS_ERR; 
    }
    
    return NO_ERR;   
  
}



int can0_sendEx(dword ID, byte *buf, int len) 
{
    int j = len;
    
    while (j > 8) 
    { 
        can0_send(ID, buf, 8);
        buf += 8;
        j -= 8;
    }
        
    if (j > 0)
        can0_send(ID, buf, j);    
}





int can1_send(dword ID, byte *buf, int len) 
{
    int cnt = 0;
    byte can1tx;    
    
    Set_CAN_ID(ID, 1, 0);         //设置ID
    
    if (!CAN1TFLG) 
        return IS_ERR;            //查询发送buffer是否为空       
   
    CAN1TBSEL  = CAN1TFLG;                    //选择最低位空的buffer作为发送寄存器
    can1tx     = CAN1TBSEL;                   //备份选择的发送缓存
    CAN1TXIDR0 = CAN1_ID_box[0][0];
    CAN1TXIDR1 = CAN1_ID_box[0][1]; 
    CAN1TXIDR2 = CAN1_ID_box[0][2]; 
    CAN1TXIDR3 = CAN1_ID_box[0][3]; 
    CAN1TXDLR  = len;                       //指定数据长度
    CAN1TXTBPR = 1;                       //设置发送优先级
    
    
    memcpy(CAN1_TxBuffer_box[0], buf, 8);
    
    
    CAN1TXDSR0 = CAN1_TxBuffer_box[0][0];              //写入发送内容
    CAN1TXDSR1 = CAN1_TxBuffer_box[0][1];
    CAN1TXDSR2 = CAN1_TxBuffer_box[0][2];
    CAN1TXDSR3 = CAN1_TxBuffer_box[0][3];
    CAN1TXDSR4 = CAN1_TxBuffer_box[0][4];
    CAN1TXDSR5 = CAN1_TxBuffer_box[0][5];
    CAN1TXDSR6 = CAN1_TxBuffer_box[0][6];
    CAN1TXDSR7 = CAN1_TxBuffer_box[0][7];

    CAN1TFLG = can1tx;                             //开始传送；

    while ((CAN1TFLG & can1tx) != can1tx)
    {
        if (++cnt > 10000) 
            return IS_ERR; 
    }
    
    return NO_ERR;   
  
}



int can1_sendEx(dword ID, byte *buf, int len) 
{
    int j = len;
    
    while (j > 8) 
    { 
        can1_send(ID, buf, 8);
        buf += 8;
        j -= 8;
    }
        
    if (j > 0)
        can1_send(ID, buf, j);    
}


int can3_send(dword ID, byte *buf, int len) 
{
    int cnt = 0;
    byte can3tx;    
    
    Set_CAN_ID(ID, 3, 0);         //设置ID
    
    if (!CAN1TFLG) 
        return IS_ERR;            //查询发送buffer是否为空       
   
    CAN3TBSEL  = CAN3TFLG;                    //选择最低位空的buffer作为发送寄存器
    can3tx     = CAN3TBSEL;                   //备份选择的发送缓存
    CAN3TXIDR0 = CAN3_ID_box[0][0];
    CAN3TXIDR1 = CAN3_ID_box[0][1]; 
    CAN3TXIDR2 = CAN3_ID_box[0][2]; 
    CAN3TXIDR3 = CAN3_ID_box[0][3]; 
    CAN3TXDLR  = len;                       //指定数据长度
    CAN3TXTBPR = 1;                       //设置发送优先级
    
    
    memcpy(CAN3_TxBuffer_box[0], buf, 8);
    
    
    CAN3TXDSR0 = CAN3_TxBuffer_box[0][0];              //写入发送内容
    CAN3TXDSR1 = CAN3_TxBuffer_box[0][1];
    CAN3TXDSR2 = CAN3_TxBuffer_box[0][2];
    CAN3TXDSR3 = CAN3_TxBuffer_box[0][3];
    CAN3TXDSR4 = CAN3_TxBuffer_box[0][4];
    CAN3TXDSR5 = CAN3_TxBuffer_box[0][5];
    CAN3TXDSR6 = CAN3_TxBuffer_box[0][6];
    CAN3TXDSR7 = CAN3_TxBuffer_box[0][7];

    CAN3TFLG = can3tx;                             //开始传送；

    while ((CAN3TFLG & can3tx) != can3tx)
    {
        if (++cnt > 10000) 
            return IS_ERR; 
    }
    
    return NO_ERR;   
  
}



int can3_sendEx(dword ID, byte *buf, int len) 
{
    int j = len;
    
    while (j > 8) 
    { 
        can3_send(ID, buf, 8);
        buf += 8;
        j -= 8;
    }
        
    if (j > 0)
        can3_send(ID, buf, j);    
}


int can_sendEx(dword ID, byte *buf, int len, byte canChannel) 
{
    switch (canChannel) 
    {   
        case CAN0:
            can0_sendEx(ID, buf, len);
            break;
            
        case CAN1:
            can1_sendEx(ID, buf, len); 
            break;  

        case CAN3:
            can3_sendEx(ID, buf, len);
            break; 
            
        default:
            break;
        
    }

}












/*===============================================
函数功能：设置指定文本框的值,用户接口函数参考LR_LCD_SetValueToEditeEx
参数列表： pIndex: 页面索引
           controlIndex: 控件的索引
		   buf:	存放要发送的字符缓冲区，要以0结尾
特别注意，buf的最后要有一个0——就是说多添加一个0,字符长度最大值为50，超出50的部分不处理
=================================================*/
void MY_LCD_SetValueToEdite1(byte canChannel, dword ID, word editID, byte *buf)
{
    word sum;
    byte i = 0;
    byte j = 0;
    byte clong = 0;
    byte tempBuf[30];
    byte *sendBuf = tempBuf; 
    byte pIndex = (byte)(editID >> 8); 
    byte controlIndex = (byte)(editID & 0xff);    
    
    
	tempBuf[0] = 0x1b;
	tempBuf[1] = 0x2f; 
	
	sum =  0x1b + 0x2F + EDITE_ITEM + DATA_TRAN + pIndex + controlIndex;  
    
    while (*buf)
    {
        tempBuf[i+7] = *buf;
        sum += *buf;       
        buf++;
        i++;

    }   
    
    
    clong = i + 4;  
    
    sum += clong;
    
  	tempBuf[2] = clong;  
  	tempBuf[3] = EDITE_ITEM; 
    tempBuf[4] = DATA_TRAN;
  	tempBuf[5] = pIndex; 
    tempBuf[6] = controlIndex; 
    
    i = i + 7;
    
    tempBuf[i] = (byte)(sum>>8);
    tempBuf[i+1] = (byte)(sum & 0xff);
        
    i = i + 2;
    
    j = i;
    

    can_sendEx(ID, sendBuf, j, canChannel);
}




/*===============================================
函数功能：设置文字颜色
参数列表：
		  clr:	 文字颜色
=================================================*/
void MY_LCD_SetFClr(byte canChannel, dword ID, byte clr)
{	
    word sum;
    byte tempBuf[8];
    
    tempBuf[0] = (0x1b);
    tempBuf[1] = (0x43);
    tempBuf[2] = (0x1);
    sum = 0x1b+0x43+1+clr;
    tempBuf[3] = (clr);
    tempBuf[4] = ((byte)(sum>>8));
    tempBuf[5] = ((byte)sum);
    
    
    can_sendEx(ID, tempBuf, 6, canChannel);    
}






/*===============================================
函数功能：设置指定文本框的值,用户接口函数参考LR_LCD_SetValueToEditeEx
参数列表： pIndex: 页面索引
           controlIndex: 控件的索引
		   value:	文本框要显示的小数（1位小数）
特别注意，buf的最后要有一个0——就是说多添加一个0,字符长度最大值为50，超出50的部分不处理
=================================================*/
void MY_LCD_SetValueToEdite2(byte canChannel, dword ID, word editID, int value)
{
    word sum;
    byte i = 0;
    byte j = 0;
    byte clong = 0;
    byte tempBuf[30] = {0};
    byte *sendBuf = tempBuf; 
    byte dataBuf[30] = {0};
    byte *buf = dataBuf;
    byte pIndex = (byte)(editID >> 8); 
    byte controlIndex = (byte)(editID & 0xff);
    
    
    
    sprintf(dataBuf, "%d", value); 
   
    
	tempBuf[0] = 0x1b;
	tempBuf[1] = 0x2f; 
	
	sum =  0x1b + 0x2F + EDITE_ITEM + DATA_TRAN + pIndex + controlIndex;  
    
    while (*buf)
    {
        tempBuf[i+7] = *buf;
        sum += *buf;       
        buf++;
        i++;
    }   
    
    
    clong = i + 4;  
    
    sum += clong;
    
  	tempBuf[2] = clong;  
  	tempBuf[3] = EDITE_ITEM; 
    tempBuf[4] = DATA_TRAN;
  	tempBuf[5] = pIndex; 
    tempBuf[6] = controlIndex; 
    
    i = i + 7;
    
    tempBuf[i] = (byte)(sum>>8);
    tempBuf[i+1] = (byte)(sum & 0xff);
        
    i = i + 2;
    
    j = i;


    can_sendEx(ID, sendBuf, j, canChannel); 
}










/*===============================================
函数功能：设置指定文本框的值,用户接口函数参考LR_LCD_SetValueToEditeEx
参数列表： pIndex: 页面索引
           controlIndex: 控件的索引
		   value:	文本框要显示的小数（1位小数）
特别注意，buf的最后要有一个0——就是说多添加一个0,字符长度最大值为50，超出50的部分不处理
=================================================*/
void MY_LCD_SetValueToEdite3(byte canChannel, dword ID, word editID, float value)
{
    word sum;
    byte i = 0;
    byte j = 0;
    byte clong = 0;
    byte tempBuf[30] = {0};
    byte *sendBuf = tempBuf; 
    byte dataBuf[30] = {0};
    byte *buf = dataBuf;
    byte pIndex = (byte)(editID >> 8); 
    byte controlIndex = (byte)(editID & 0xff);
    
    
    
    sprintf(dataBuf, "%.0f", value); 
   
    
	tempBuf[0] = 0x1b;
	tempBuf[1] = 0x2f; 
	
	sum =  0x1b + 0x2F + EDITE_ITEM + DATA_TRAN + pIndex + controlIndex;  
    
    while (*buf)
    {
        tempBuf[i+7] = *buf;
        sum += *buf;       
        buf++;
        i++;
    }   
    
    
    clong = i + 4;  
    
    sum += clong;
    
  	tempBuf[2] = clong;  
  	tempBuf[3] = EDITE_ITEM; 
    tempBuf[4] = DATA_TRAN;
  	tempBuf[5] = pIndex; 
    tempBuf[6] = controlIndex; 
    
    i = i + 7;
    
    tempBuf[i] = (byte)(sum>>8);
    tempBuf[i+1] = (byte)(sum & 0xff);
        
    i = i + 2;
    
    j = i;


    can_sendEx(ID, sendBuf, j, canChannel); 
}







/*===============================================
函数功能：设置柱状图的高度,用户接口函数参考LR_LCD_SetChildBarHeightEx
参数列表： pIndex: 页面索引
           controlIndex: 柱状图的索引
		   childIndex：子柱状图的索引
		   barHeight：子柱状图的高度
=================================================*/
void MY_LCD_SetChildBarHeight2(byte canChannel, dword ID, byte pIndex, byte controlIndex, 
                            byte childIndex, word barHeight)
{
    word sum;
	byte i = 0;
	byte clong = 7;
    byte tempBuf[20];	
	
	tempBuf[0] = 0x1b;
	tempBuf[1] = 0x2f;	
	
	
  	sum = 0x1b + 0x2F + clong + BAR_ITEM + BAR_HEIGHT + pIndex + 
	        controlIndex + childIndex + (byte)(barHeight>>8) + (byte)barHeight;


  	tempBuf[2] = (clong);
	tempBuf[3] = (BAR_ITEM);
	tempBuf[4] = (BAR_HEIGHT);
	tempBuf[5] = (pIndex);
	tempBuf[6] = (controlIndex);
	tempBuf[7] = (childIndex);
	tempBuf[8] = ((byte)(barHeight>>8));
	tempBuf[9] = ((byte)barHeight);	
	tempBuf[10] = ((byte)(sum>>8));
	tempBuf[11] = ((byte)sum);	
	

    can_sendEx(ID, tempBuf, 12, canChannel); 	
}



/*===============================================
函数功能：调用局部位图增强型
参数列表：
		   ItemIndex:	 局部位图ID
		     sx:	局部位图显示的时候左上角在屏上的x坐标
			 sy:	局部位图显示的时候左上角在屏上的y坐标
=================================================*/

void MY_LCD_LoadPartBmpEx2(byte canChannel, dword ID, byte controlType, word ItemIndex, word sx, word sy) 
{

	word sum;
	byte tempBuf[20];
	
	
	tempBuf[0] = 0x1b;
	tempBuf[1] = 0x2f;	
	tempBuf[2] = 7;		 
	tempBuf[3] = controlType;		 
	tempBuf[4] = (byte)(ItemIndex>>8);	
	tempBuf[5] = (byte)(ItemIndex & 0xff);
	tempBuf[6] = (byte)(sx&0xff);
	tempBuf[7] = (byte)(sx>>8);
			 
	tempBuf[8] = (byte)(sy&0xff);		 
	tempBuf[9] = (byte)(sy>>8);

	sum = ESC + 0X2F + 7 + controlType + (byte)(ItemIndex>>8) + 
	        (byte)ItemIndex + (byte)sx + (byte)(sx>>8) + (byte)sy + (byte)(sy>>8);	
		 
	tempBuf[10] = (byte)(sum>>8);
	tempBuf[11] = (byte)(sum&0xff);	
 
    
    can_sendEx(ID, tempBuf, 12, canChannel);  		
}



/*===============================================
函数功能：用串口发送程序激发控件事件，如点击等,用户接口函数参考LR_LCD_ExecuteEventEx
参数列表： controlType: 控件类型
		   eventType：事件类型
		   pIndex：页面索引
           controlIndex: 控件的索引
=================================================*/
// 控件类型button  事件类型click  页号page   索引index
void MY_LCD_ExecuteEvent(byte canChannel, dword ID, byte controlType, byte eventType, word editID)
{
	word sum;
	byte tempBuf[20];
	byte pIndex =  editID >> 8;
	byte controlIndex = editID & 0xff;
	
	
	tempBuf[0] = 0x1b;
	tempBuf[1] = 0x2f;	
	tempBuf[2] = 4;		 
	tempBuf[3] = controlType;	 
	tempBuf[4] = eventType;	
	tempBuf[5] = pIndex;
	tempBuf[6] = controlIndex;

	sum = 0x1b + 0x2F + 0x4 + controlType + eventType + pIndex+controlIndex;	
		 
	tempBuf[7] = (byte)(sum>>8);
	tempBuf[8] = (byte)(sum&0xff);
	
	
	can_sendEx(ID, tempBuf, 9, canChannel);	
}




//函数功能：光标以像素为单位直接定位
//参数列表：
//		 x: 光标的水平坐标 单位为像素
//		 y: 光标的竖直坐标 单位为像素
void MY_LCD_CurserMove(byte canChannel, dword ID, word x, word y)
{
	word sum;
	byte tempBuf[10] = { 0 };


	tempBuf[0] = 0x1b;
	tempBuf[1] = 0x48;	
	tempBuf[2] = 4;		 
	tempBuf[3] = (byte)(x & 0xff);	 
	tempBuf[4] = (byte)(x>>8);	
	tempBuf[5] = (byte)(y & 0xff);
	tempBuf[6] = (byte)(y>>8);

	sum = ESC + 0X48 + 4 + (x&0xff) + (x>>8) + (y&0xff) + (y>>8);	
		 
	tempBuf[7] = (byte)(sum>>8);
	tempBuf[8] = (byte)(sum&0xff);
	
	
    can_sendEx(ID, tempBuf, 9, canChannel);	 
}







/*===============================================
函数功能：自动判断、显示字符
参数列表：
		   buf:	存放要显示的字符缓冲区，要以0结尾
特别注意，buf的最后要有一个0——就是说多添加一个0
=================================================*/
void MY_LCD_ShowString(byte canChannel, dword ID, byte *buf)
{
	word sum = 0;   
	byte tempBuf[50] = {0}; 
    byte *sendBuf = tempBuf; 
	byte i = 0; 
	byte j; 
   
	tempBuf[0] = 0x1b;
	tempBuf[1] = 0x25; 
	
    sum = 0x1b + 0x25 + 0;

    while (*buf)
    {
        tempBuf[i+3] = *buf;
        sum += *buf;       
        buf++;
        i++;
    }   
   
    sum += i;
    tempBuf[2] = i;
    
    i = i + 3;

    tempBuf[i] = (byte)(sum>>8);
    tempBuf[i+1] = (byte)(sum & 0xff);   
    
    i = i + 2;
   
    j = i;
    


    can_sendEx(ID, sendBuf, j, canChannel);
   
	//////////////////////////////////////////////////////////////////////////
}




/*===============================================
函数功能：自动判断、显示字符
参数列表：
		   x:要显示的位置的x坐标
		   y:要显示的位置的y坐标
		   buf:	存放要显示的字符缓冲区，要以0结尾
特别注意，buf的最后要有一个0——就是说多添加一个0
=================================================*/
void MY_LCD_ShowStringAt(byte canChannel, dword ID, word x, word y, byte *buf, byte color)
{
    MY_LCD_SetFClr(canChannel, ID, color);
	MY_LCD_CurserMove(canChannel, ID, x, y);
	MY_LCD_ShowString(canChannel, ID, buf);
}




/*===============================================
函数功能：用串口发送程序转发到指定的页面
参数列表： cPageIndex: 页面索引
=================================================*/
void MY_LCD_ForwardPage(byte canChannel, dword ID, byte cPageIndex)
{
	word sum = 0;   
	byte tempBuf[10] = {0}; 

	tempBuf[0] = (0x1b);
	tempBuf[1] = (0x2F);
	tempBuf[2] = (0x3);
	tempBuf[3] = (PAGE_ITEM);
	tempBuf[4] = (INIT_PAGE_INDEX);
	tempBuf[5] = (cPageIndex);
	sum= 0x1b+0x2F+0x3+PAGE_ITEM+INIT_PAGE_INDEX+cPageIndex;
	tempBuf[6] = ((UCHAR)(sum>>8));
	tempBuf[7] = ((UCHAR)sum); 


    can_sendEx(ID, tempBuf, 8, canChannel);
}





// 显示 8 个 电机的温度
void showMortorTemp(void) 
{
    byte i;
    dword ID = HIM2_SEND_ID;
    byte  moterTemp[8];
    
    moterTemp[0] = abyVCU_CAN1_Recv_MCU_S_2_DCU1[2] - 40;
    moterTemp[1] = abyVCU_CAN1_Recv_MCU_S_2_DCU2[2] - 40;    
    moterTemp[2] = abyVCU_CAN1_Recv_MCU_S_2_DCU3[2] - 40;    
    moterTemp[3] = abyVCU_CAN1_Recv_MCU_S_2_DCU4[2] - 40;   
    moterTemp[4] = abyVCU_CAN1_Recv_MCU_S_2_DCU5[2] - 40;    
    moterTemp[5] = abyVCU_CAN1_Recv_MCU_S_2_DCU6[2] - 40;
    moterTemp[6] = abyVCU_CAN1_Recv_MCU_S_2_DCU7[2] - 40;    
    moterTemp[7] = abyVCU_CAN1_Recv_MCU_S_2_DCU8[2] - 40;    
        
    
    
    for (i = 0; i < 8; i++) 
    {
        if (moterTempTmp[i] != moterTemp[i]) 
        {
            moterTempTmp[i] = moterTemp[i];
            MY_LCD_SetValueToEdite3(CAB_CAN, ID, moterTempID[i], moterTemp[i]);
        }
    }

}



// 显示 8 个 电机控制器的温度
void showMortorCtrlTemp(void) 
{
    byte i;
    dword ID = HIM2_SEND_ID;
    byte  moterCtrlTemp[8];
    
    moterCtrlTemp[0] = abyVCU_CAN1_Recv_MCU_S_2_DCU1[3] - 40;
    moterCtrlTemp[1] = abyVCU_CAN1_Recv_MCU_S_2_DCU2[3] - 40;    
    moterCtrlTemp[2] = abyVCU_CAN1_Recv_MCU_S_2_DCU3[3] - 40;    
    moterCtrlTemp[3] = abyVCU_CAN1_Recv_MCU_S_2_DCU4[3] - 40;   
    moterCtrlTemp[4] = abyVCU_CAN1_Recv_MCU_S_2_DCU5[3] - 40;    
    moterCtrlTemp[5] = abyVCU_CAN1_Recv_MCU_S_2_DCU6[3] - 40;
    moterCtrlTemp[6] = abyVCU_CAN1_Recv_MCU_S_2_DCU7[3] - 40;    
    moterCtrlTemp[7] = abyVCU_CAN1_Recv_MCU_S_2_DCU8[3] - 40;     
    
        
    for (i = 0; i < 8; i++) 
    {
        if (moterCtrlTempTmp[i] != moterCtrlTemp[i]) 
        {
            moterCtrlTempTmp[i] = moterCtrlTemp[i];
            MY_LCD_SetValueToEdite3(CAB_CAN, ID, moterCtrlTempID[i], moterCtrlTemp[i]);
        }
    }

}


float absCmp(float a, float b) 
{
    if (a > b)
        return (a - b);
    else
        return (b - a);


}



// 显示 8 个 电机的前向电压
void showMortorFrontVol(void) 
{
    byte i;
    dword ID = HIM2_SEND_ID;
    float  frontVol[8];
    
    frontVol[0] = (((abyVCU_CAN1_Recv_MCU_S_2_DCU1[1] << 8) + abyVCU_CAN1_Recv_MCU_S_2_DCU1[0]) - 10000) * 0.1;
    frontVol[1] = (((abyVCU_CAN1_Recv_MCU_S_2_DCU2[1] << 8) + abyVCU_CAN1_Recv_MCU_S_2_DCU2[0]) - 10000) * 0.1;    
    frontVol[2] = (((abyVCU_CAN1_Recv_MCU_S_2_DCU3[1] << 8) + abyVCU_CAN1_Recv_MCU_S_2_DCU3[0]) - 10000) * 0.1;
    frontVol[3] = (((abyVCU_CAN1_Recv_MCU_S_2_DCU4[1] << 8) + abyVCU_CAN1_Recv_MCU_S_2_DCU4[0]) - 10000) * 0.1;    
    frontVol[4] = (((abyVCU_CAN1_Recv_MCU_S_2_DCU5[1] << 8) + abyVCU_CAN1_Recv_MCU_S_2_DCU5[0]) - 10000) * 0.1;
    frontVol[5] = (((abyVCU_CAN1_Recv_MCU_S_2_DCU6[1] << 8) + abyVCU_CAN1_Recv_MCU_S_2_DCU6[0]) - 10000) * 0.1;    
    frontVol[6] = (((abyVCU_CAN1_Recv_MCU_S_2_DCU7[1] << 8) + abyVCU_CAN1_Recv_MCU_S_2_DCU7[0]) - 10000) * 0.1;
    frontVol[7] = (((abyVCU_CAN1_Recv_MCU_S_2_DCU8[1] << 8) + abyVCU_CAN1_Recv_MCU_S_2_DCU8[0]) - 10000) * 0.1;    
        
 
    for (i = 0; i < 8; i++) 
    {
        if (absCmp(motorFrontVolTmp[i], frontVol[i]) > 2) 
        {
            motorFrontVolTmp[i] = frontVol[i];
            MY_LCD_SetValueToEdite3(CAB_CAN, ID, moterVolID[i], frontVol[i]);
        }
    }

}

void showOtherInfo(void) 
{
    dword ID = HIM2_SEND_ID;

    MY_LCD_SetValueToEdite3(CAB_CAN, ID, ID_EDITE_3183, aiTargetTorque[0]-32000);
    
    if (byTractionEnable == 1) 
    {
        MY_LCD_SetValueToEdite1(CAB_CAN, ID, ID_EDITE_3181, "牵引使能");
    } 
    else  if (byTractionEnable == 0) 
    {
        MY_LCD_SetValueToEdite1(CAB_CAN, ID, ID_EDITE_3181, "牵引封锁");
    }
    
   
}




void can_test(void) 
{
    static byte count1 = 0;
    static byte count2 = 0;
    static byte count3 = 0;
    static byte count4 = 0;    
    static byte count5 = 0;
     
    dword ID = HIM2_SEND_ID;
    
    byte  errorCode[8];
    
    errorCode[0] = abyVCU_CAN1_Recv_MCU_S_2_DCU1[7];
    errorCode[1] = abyVCU_CAN1_Recv_MCU_S_2_DCU2[7];
    errorCode[2] = abyVCU_CAN1_Recv_MCU_S_2_DCU3[7];
    errorCode[3] = abyVCU_CAN1_Recv_MCU_S_2_DCU4[7];
    errorCode[4] = abyVCU_CAN1_Recv_MCU_S_2_DCU5[7];
    errorCode[5] = abyVCU_CAN1_Recv_MCU_S_2_DCU6[7];
    errorCode[6] = abyVCU_CAN1_Recv_MCU_S_2_DCU7[7];
    errorCode[7] = abyVCU_CAN1_Recv_MCU_S_2_DCU8[7];

    count2++;
    if ( count2 % 4 == 0) 
    {
    
        showSpeedValue2(ID, byTrainSpeed);
        

        if (bySelfState == MASTER_STATE) 
        {
            setCab22Status(ID, CAB_ACTIVE);    
        } 
        else 
        {
            setCab22Status(ID, CAB_INACTIVE); 
        }
  
    
        if (byOtherState == MASTER_STATE) 
        {
            setCab11Status(ID, CAB_ACTIVE);    
        }
        else 
        {
            setCab11Status(ID, CAB_INACTIVE); 
        }

    }  
    if (count2 % 4 == 1) 
    {
        if (errorCodeTmp[0] != errorCode[0]) 
        {
            errorCodeTmp[0] = errorCode[0];
            
            if (errorCode[0] > 0)
                setMotor1Status(ID, STATUS_ALARM); 
            else
                setMotor1Status(ID, STATUS_WORKING);      
        }

        
        if (errorCodeTmp[1] != errorCode[1]) 
        {
            errorCodeTmp[1] = errorCode[1];
            

            if (errorCode[1] > 0)
                setMotor2Status(ID, STATUS_ALARM); 
            else
                setMotor2Status(ID, STATUS_WORKING);
            
        }  
        
        if (errorCodeTmp[2] != errorCode[2]) 
        {
            errorCodeTmp[2] = errorCode[2];
            
        
            if (errorCode[2] > 0)
                setMotor3Status(ID, STATUS_ALARM); 
            else
                setMotor3Status(ID, STATUS_WORKING);                
            
        }
        
        
        if (errorCodeTmp[3] != errorCode[3]) 
        {
            errorCodeTmp[3] = errorCode[3];
            
            if (errorCode[3] > 0)
                setMotor4Status(ID, STATUS_ALARM); 
            else
                setMotor4Status(ID, STATUS_WORKING);                    
        }
        
        
        
        if (errorCodeTmp[4] != errorCode[4]) 
        {
            errorCodeTmp[4] = errorCode[4];
            
            if (errorCode[4] > 0)
                setMotor5Status(ID, STATUS_ALARM); 
            else
                setMotor5Status(ID, STATUS_WORKING);                  
        }
        
         
        if (errorCodeTmp[5] != errorCode[5]) 
        {
            errorCodeTmp[5] = errorCode[5];
            
            if (errorCode[5] > 0)
                setMotor6Status(ID, STATUS_ALARM); 
            else
                setMotor6Status(ID, STATUS_WORKING);                  
        } 
         
        
        if (errorCodeTmp[6] != errorCode[6]) 
        {
            errorCodeTmp[6] = errorCode[6];
            
            if (errorCode[6] > 0)
                setMotor7Status(ID, STATUS_ALARM); 
            else
                setMotor7Status(ID, STATUS_WORKING);                  
        }
        
         
            
        if (errorCodeTmp[7] != errorCode[7]) 
        {
            errorCodeTmp[7] = errorCode[7];
            
            if (errorCode[7] > 0)
                setMotor8Status(ID, STATUS_ALARM); 
            else
                setMotor8Status(ID, STATUS_WORKING);                     
        } 
    } 
    if (count2 % 4 == 2) 
    {
        showMortorTemp();
        showMortorCtrlTemp();
    }
    if (count2 % 4 == 3) 
    {
        showMortorFrontVol();
        showOtherInfo();
    }      

     
 
}


void him_init(void) 
{
    dword ID1 = HIM2_SEND_ID;
    dword ID2 = HIM4_SEND_ID;    
    
    setBianliu1Status(ID1, STATUS_WORKING); 
    setBianliu2Status(ID1, STATUS_WORKING); 
    setBianliu3Status(ID1, STATUS_WORKING); 
    setBianliu4Status(ID1, STATUS_WORKING); 
    setBianliu5Status(ID1, STATUS_WORKING); 
    setBianliu6Status(ID1, STATUS_WORKING); 
    setBianliu7Status(ID1, STATUS_WORKING);
    setBianliu8Status(ID1, STATUS_WORKING);    
    
    setBat1TotalVol(ID2, 0);
}







 



void can_test2(void) 
{
    static byte count = 0;
    byte i; 
    byte batStatus[2];
    byte batSoc[2];
    dword ID = HIM4_SEND_ID;
   
  
   float totalVol1 = ((abyVCU_CAN3_Recv_BMS1_MainInfo1[1] << 8) + abyVCU_CAN3_Recv_BMS1_MainInfo1[0]) * 0.1;
    float totalVol2 = ((abyVCU_CAN3_Recv_BMS2_MainInfo1[1] << 8) + abyVCU_CAN3_Recv_BMS2_MainInfo1[0]) * 0.1;    
  
    
    float totalCur1 = (((abyVCU_CAN3_Recv_BMS1_MainInfo1[3] << 8) + abyVCU_CAN3_Recv_BMS1_MainInfo1[2]) - 32000) * 0.1;
    float totalCur2 = (((abyVCU_CAN3_Recv_BMS2_MainInfo1[3] << 8) + abyVCU_CAN3_Recv_BMS2_MainInfo1[2]) - 32000) * 0.1;
    
    
    Byte socBms1 =  (byte)(abyVCU_CAN3_Recv_BMS1_MainInfo1[4]* 0.4);
    Byte socBms2 =  (byte)(abyVCU_CAN3_Recv_BMS2_MainInfo1[4]* 0.4);      
    
    

    batStatus[0] = socBms1/10;
    batStatus[1] = socBms2/10;


    count++;
    
    if (count % 2 == 0) 
    {

        if (batStatus[0] != batStatusTmp[0]) 
        {
            batStatusTmp[0] = batStatus[0];
            setBat1Status(ID, batStatus[0]+11);
            
        }

        if (batStatus[1] != batStatusTmp[1]) 
        {
            batStatusTmp[1] = batStatus[1];
            setBat2Status(ID, batStatus[1]+11);
            
        }   
    
    } 
    else if (count % 2 == 1) 
    {
        if (absCmp(totalVol1, batVolTmp[0]) > 2) 
        {
            batVolTmp[0] = totalVol1;
            setBat1TotalVol(ID, totalVol1);
        
        }
      
        if (absCmp(totalVol2, batVolTmp[1]) > 2) 
        {
            batVolTmp[1] = totalVol2;
            setBat2TotalVol(ID, totalVol2);
        }

 
        if (absCmp(totalCur1, batCurTmp[0]) > 0) 
        {
            batCurTmp[0] = totalCur1;
            setBat1TotalCurrent(ID, totalCur1);
        }
      
        if (absCmp(totalCur2, batCurTmp[1]) > 0) 
        {
            batCurTmp[1] = totalCur2;
            setBat2TotalCurrent(ID, totalCur2);
        }
 

        if (socBms1 != batSocTmp[0]) 
        {
            batSocTmp[0] = socBms1;
            setBat1SOC(ID, socBms1); 
        }
    
        if (socBms2 != batSocTmp[1]) 
        {
            batSocTmp[1] = socBms2;
            setBat2SOC(ID, socBms2); 
        }
 
    }


}







/************************************************************************
** 函数名称：Vcu_TrainSpeed_Calc()                               **
** 函数功能：Calsulate the train speed                         **
** 输    入：                                                          **
**                                                                     **
** 输    出：                                                          **
** 作    者：                                                          **
** 日    期：                                                          **
** 修改情况：---                                                       **
** 备    注：                            **
************************************************************************/ 
void Vcu_TrainSpeed_Calc(void)
{
    //Train speed calculation
#if 0      //shenmin    
    
    Byte byLoop;
    Byte byLoop1;
    int iTemp;
    int iSum = 0;
    int aiMotorRPMTemp[8];
    memcpy(aiMotorRPMTemp, aiMotorRPM, sizeof(aiMotorRPMTemp));
    for(byLoop = 0; byLoop < 7; byLoop ++)
    {
        for(byLoop1 = byLoop; byLoop1 < 7; byLoop1 ++)
        {
            if(aiMotorRPMTemp[byLoop1] < aiMotorRPMTemp[byLoop1+1])
            {
                iTemp                     = aiMotorRPMTemp[byLoop1];
                aiMotorRPMTemp[byLoop1]   = aiMotorRPMTemp[byLoop1+1];
                aiMotorRPMTemp[byLoop1+1] = iTemp;
            }
        }
    }
    
    for(byLoop = 1; byLoop < 7; byLoop ++) //The max and min value of the RPMs are excluded to pretend some error value
    {
        iSum += aiMotorRPMTemp[byLoop];
    }
    
    byTrainSpeed = (Byte)(((float)iSum) / 3 * 0.172);  //Calculate the km/h from 0.5RPM/bit
#endif    //shenmin
    
    Byte byLoop;
    word speed[8];
    int iSum = 0; 
      
    speed[0] = ((abyVCU_CAN1_Recv_MCU_S_1_DCU1[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU1[2];
    speed[1] = ((abyVCU_CAN1_Recv_MCU_S_1_DCU2[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU2[2];    
    speed[2] = ((abyVCU_CAN1_Recv_MCU_S_1_DCU3[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU3[2];
    speed[3] = ((abyVCU_CAN1_Recv_MCU_S_1_DCU4[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU4[2];    
    speed[4] = ((abyVCU_CAN1_Recv_MCU_S_1_DCU5[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU5[2];    
    speed[5] = ((abyVCU_CAN1_Recv_MCU_S_1_DCU6[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU6[2]; 
    speed[6] = ((abyVCU_CAN1_Recv_MCU_S_1_DCU7[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU7[2]; 
    speed[7] = ((abyVCU_CAN1_Recv_MCU_S_1_DCU8[3]) << 8) + (int)abyVCU_CAN1_Recv_MCU_S_1_DCU8[2];
 

    for(byLoop = 0; byLoop < 8; byLoop ++) //The max and min value of the RPMs are excluded to pretend some error value
    {
        iSum += speed[byLoop];
    }
    
    byTrainSpeed = (Byte)(((float)iSum) / 16 * 0.172);  //Calculate the km/h from 0.5RPM/bit
    
}







// liuchao end














