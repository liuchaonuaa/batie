#include <hidef.h>    
#include <string.h>
#include "CAN.h"
#include "EEPROM.h"
#include "SCI.h"
#include "SPI.h"
#include "Application_Funtion.h"
#include "Hardware_init.h"
#include "freemaster.h"
#include "Hardware_init.h"
#include "freemaster_tsa.h"
#include "xgate.h"


//////////////////////////////////////////////////////////////////////////
// #Define Macro
// 宏定义
/////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// #Define Macro
// 宏定义
#define MASTER_STATE 1   //VCU2/3 on active cab
#define SLAVE_STATE  0   //VCU2/3 on inactive cab
#define OPEN 0x55
#define LOCKED 0xAA
#define START 0x55
#define STOP 0xAA
#define DC_VOL_LMT   6000    //MCM DC voltage limitation, Temp 600V
#define DC_CUR_LMT   6000    //MCM DC current limitation, Temp





extern Byte SCI_COUNTER;

 //-----------------------------------TEST ONLY---------------------------------------------------
extern Word i_test;
extern Word i_test_main;
extern float i_test_float;
extern unsigned long ID_TEST;
extern unsigned long ID_TEST1;
extern Word  i_a;
extern Byte  DI_EN;






//数字量输入变量

extern Byte DI_Vale_TEXT[20];

/*
    DI_Vale_TEXT[0]  -- 司控器激活  1-激活；0-未激活
    DI_Vale_TEXT[1]  -- 前进方向    1-前进方向；0-非前进方向
    DI_Vale_TEXT[2]  -- 后退方向    1-后退方向；0-非后退方向
    DI_Vale_TEXT[3]  -- 驻车列车线  1-解除驻车；0-驻车
    DI_Vale_TEXT[4]  -- 制动反馈    1-有制动；0-无制动施加
    DI_Vale_TEXT[5]  -- 制动 U 位   
    DI_Vale_TEXT[6]  -- 制动 V 位
    DI_Vale_TEXT[7]  -- 制动 W 位
    DI_Vale_TEXT[8]  -- 牵引 A 位
    DI_Vale_TEXT[9]  -- 牵引 B 位
    DI_Vale_TEXT[10] -- 牵引 C 位
    DI_Vale_TEXT[11] -- 牵引 D 位
    DI_Vale_TEXT[10] -- 门 3 状态   1-门关好锁闭；0-门未关好锁闭
    DI_Vale_TEXT[11] -- 门 4 状态   1-门关好锁闭；0-门未关好锁闭  
 */




//模拟量输入变量  原始AD值
extern Word AI_Vale_TEXT[20];



//模拟量输出变量
extern float AO_Vale_TEXT[6];   //前两个为输出模拟量 后四个为输出频率量

extern word Fre_Vale_TEXT[6];     //设置频率

//数字量输出变量

extern Byte  DO_Vale_TEXT[20];

/*
    DO_Vale_TEXT[0]  -- 主接触器 2+
    DO_Vale_TEXT[1]  -- 预充接触器 2+
    DO_Vale_TEXT[2]  -- 主接触器 4+
    DO_Vale_TEXT[3]  -- 预充接触器 4+
    DO_Vale_TEXT[4]  -- 辅助电路接触器 3+
    DO_Vale_TEXT[5]  -- 主接触器 6+
    DO_Vale_TEXT[6]  -- 预充接触器 6+
    DO_Vale_TEXT[7]  -- 主接触器 8+
    DO_Vale_TEXT[8]  -- 预充接触器 8+     
    DO_Vale_TEXT[9]  -- 辅助电路接触器 4+
    DO_Vale_TEXT[10] -- 冷却水泵 1
    DO_Vale_TEXT[11] -- 冷却水泵 2         
 */







//---------------Global variable definition
extern Byte byPreConClsLable1;       //Pre contactor 1 close lable
extern Byte byPreConClsLable2;       //Pre contactor 2 close lable
extern Byte byPreConClsLable3;       //Pre contactor 3 close lable
extern Byte byPreConClsLable4;       //Pre contactor 4 close lable
extern Byte byBalanceLabel;          //Balancing lable
extern Byte byMotorStartLable;       //Motor start lable
extern Byte byDirection[8];             //Direction to MCM

//CAN1 
extern Byte bySelfState;             //Master or slave state of VCU itself
extern Byte byOtherState;            //Master or slave state of the other VCU
extern Byte bySelfStateTemp;         //Master or slave state of VCU itself
extern Byte byDoor3State;            //Door3 status from other VCU
extern Byte byDoor4State;            //Door4 status from ohter VCU
extern Byte byContactCmd;            //Precharge, Main, auxiliary contact, pump request, need to send to the other VCU if this VCU is MASTER
extern Byte byContactReq;            //Precharge, Main, auxiliary contact, pump request, need to execute if this VCU is SLAVE
extern Byte byTrainSpeed;            //Train speed
extern float iMainsVoltage_BMS1;       //Mains_Voltage_Battery, BMS1
extern float iMainsVoltage_BMS2;       //Mains_Voltage_Battery, BMS2
extern float iMainsCurrent_BMS1;       //Mains_Current_Battery, BMS1
extern float iMainsCurrent_BMS2;       //Mains_Current_Battery, BMS2
extern Byte bySOC_BMS1;              //SOC,BMS1
extern Byte bySOC_BMS2;              //SOC,BMS2
extern Byte byHighTemp_BMS1;         //State_Temperature_High, BMS1, 3:invalid,>80c; 2:>65c; 1:>55c; 0:OK
extern Byte byHighTemp_BMS2;         //State_Temperature_High, BMS2, 3:invalid,>80c; 2:>65c; 1:>55c; 0:OK
extern Byte byLowTemp_BMS1;          //State_Temperature_Low, BMS1, 3:invalid,<-20c; 2:<-10c; 1:<0c; 0:OK
extern Byte byLowTemp_BMS2;          //State_Temperature_Low, BMS1, 3:invalid,<-20c; 2:<-10c; 1:<0c; 0:OK
extern Byte byOverDisCharge_BMS1;    //State_OverCharge, BMS1, 3:invalid,<2.0v; 2:<2.5v; 1:<2.8v; 0:OK
extern Byte byOverDisCharge_BMS2;    //State_OverCharge, BMS2, 3:invalid,<2.0v; 2:<2.5v; 1:<2.8v; 0:OK
extern Byte byOverCharge_BMS1;       //State_OverCharge, BMS1, 3:invalid,>4.0v; 2:>3.9v; 1:>3.65v; 0:OK
extern Byte byOverCharge_BMS2;       //State_OverCharge, BMS2, 3:invalid,>4.0v; 2:>3.9v; 1:>3.65v; 0:OK
extern Byte byVoltConsist_BMS1;      //State_VoltConsistence, BMS1, 3:invalid; 2:>150mv; 1:>100mv; 0:OK
extern Byte byVoltConsist_BMS2;      //State_VoltConsistence, BMS2, 3:invalid; 2:>150mv; 1:>100mv; 0:OK
extern Byte byCommFault_BMS1;        //State_Fault_HardwareComm_InCan, BMS1, 3:Danger; 2:Need repair at once; 1:Need maintenance; 0:OK
extern Byte byCommFault_BMS2;        //State_Fault_HardwareComm_InCan, BMS2, 3:Danger; 2:Need repair at once; 1:Need maintenance; 0:OK
extern Byte byTempControl_BMS1;      //State_temperature_control, BMS1, 3:Cooling; 2:Keep warm; 1: Heating; 0:Nothing
extern Byte byTempControl_BMS2;      //State_temperature_control, BMS2, 3:Cooling; 2:Keep warm; 1: Heating; 0:Nothing
extern Byte byChargingStat_BMS1;     //State_Charging_Battery, BMS1, 3:Reserved; 2:Finished; 1: Charging; 0:Not charging
extern Byte byChargingStat_BMS2;     //State_Charging_Battery, BMS2, 3:Reserved; 2:Finished; 1: Charging; 0:Not charging
extern Byte byBalanceStat_BMS1;      //State_Balance_Battery, BMS1, 3:Reserved; 2:Reserved; 1: Balancing; 0:Nothing
extern Byte byBalanceStat_BMS2;      //State_Balance_Battery, BMS2, 3:Reserved; 2:Reserved; 1: Balancing; 0:Nothing
extern Byte byCurStat_BMS1;          //State_Current, BMS1, 3:Reserved; 2:Charging overcurrent; 1: Discharging overcurrent; 0:OK
extern Byte byCurStat_BMS2;          //State_Current, BMS2, 3:Reserved; 2:Charging overcurrent; 1: Discharging overcurrent; 0:OK
extern Byte byInsStat_BMS1;          //State_Insulation, BMS1, 3:Very Serious; 2:Medium; 1: Slight; 0:OK
extern Byte byInsStat_BMS2;          //State_Insulation, BMS2, 3:Very Serious; 2:Medium; 1: Slight; 0:OK
//extern Byte byReady_BMS1;            //State_Ready_Battery, BMS1, 3:Charging enable; 2:Discharging enable; 1: Checking; 0:Not ready   //shenmin
//extern Byte byReady_BMS2;            //State_Ready_Battery, BMS2, 3:Charging enable; 2:Discharging enable; 1: Checking; 0:Not ready   //shenmin

extern Byte byChgPlugin_BMS1;        //DC or AC charging plug is in, BMS1, 1,4,5: plug is in; Others: plug not in 
extern Byte byChgPlugin_BMS2;        //DC or AC charging plug is in, BMS1, 1,4,5: plug is in; Others: plug not in
extern Byte byHVClsStat_BMS1;        //HV closing status, BMS1, 0:open; 1:colsed
extern Byte byHVClsStat_BMS2;        //HV closing status, BMS2, 0:open; 1:colsed

extern Byte bySOH_BMS1;              //SOH, BMS1, 1~100 = 1%~100%
extern Byte bySOH_BMS2;              //SOH, BMS2, 1~100 = 1%~100%
extern int iTotalCapacity_BMS1;      //TotalCapacity, BMS1, 10bits
extern int iTotalCapacity_BMS2;      //TotalCapacity, BMS2, 10bits

//extern Byte byReq_HVBreak_FromBMS1;  //Req_HVBreak_FromBMS1, 3:Reserved; 2:No req; 1: Break request; 0:Reserved   //shenmin
//extern Byte byReq_HVBreak_FromBMS2;  //Req_HVBreak_FromBMS2, 3:Reserved; 2:No req; 1: Break request; 0:Reserved   //shenmin

extern Byte byVCU_Ctrl_BMS1;         //VCU control byte to BMS1
extern Byte byVCU_Ctrl_BMS2;         //VCU control byte to BMS2

extern Byte byTractionBlk_BMS1;      //Traction block due to BMS1
extern Byte byTractionBlk_BMS2;      //Traction block due to BMS2

extern int  aiCurHeight[4];         //Height of suspension;

//CAN0
extern int aiMotorTorque[8];         //Torque of Motor1~8
extern int aiMotorRPM[8];            //RPM of Motor1~8
extern int aiMCMInputCur[8];         //Input current of MCM1~8
extern Byte abyMCMStat[8];           //Status of MCM1~8
extern Byte abyMCMLife[8];           //Life of MCM1~8

#if 0
extern float aiContFrontVolt[8];       //Front voltage of contact 1~8
extern Byte abyMotorTemp[8];         //Tepmerature of motor 1~8
extern Byte abyMCMTemp[8];           //Tepmerature of MCM 1~8
extern int aiMCMRectCur[8];          //MCM rectified current 1~8
extern Byte abyMCMConStat[8];        //MCM contactor status 1~8
extern Byte abyMotorErrCode[8];      //Motor error code 1~8
#endif


extern Byte byTractionComm;          //Tracion command
extern Byte byBreakComm;             //Brake command
extern Byte byForward;               //Forward.   if VCU2, forward is forward; if VCU3 forward is Backward
extern Byte byBackward;              //Backward.  if VCU2, Backward is Backward; if VCU3 Backward is forward
extern Byte byBrApplied;             //Brake is applied
//extern int iTBEffortRef;             //Traction brake efforts, reference
extern Byte byTrEffRef;              //Traction reference
extern Byte byBrEffRef;              //Brake reference
extern Byte byDoor1State;            //Door1 status from VCU2, door3 status for VCU3
extern Byte byDoor2State;            //Door2 status from VCU2,  door4 status for VCU3
extern Byte byTractionEnable;        //Default : 0, traction not enable; 1, Enable

extern int aiTargetTorque[8];        //Target torque of motor
extern int aiDCVoltLmt[8];           //DC voltage limitation
extern int aiDCCurLmt[8];            //DC current limitation
extern Byte abyMotorCtrl[8];         //Motor control mode
extern Byte abyLifesign[8];          //Lifensign

//CAN2
extern Byte byDCDCComm_1;            //DCDC1 commmamd, 0x55:Start; 0xFF:Stop
extern Byte byDCACComm_1;            //DCAC1 commmamd, 0x55:Start; 0xFF:Stop
extern Byte byDCDCComm_2;            //DCDC2 commmamd, 0x55:Start; 0xFF:Stop
extern Byte byDCACComm_2;            //DCAC2 commmamd, 0x55:Start; 0xFF:Stop
extern Byte byDCDCComm_3;            //DCDC3 commmamd, 0x55:Start; 0xFF:Stop
extern Byte byDCACComm_3;            //DCAC3 commmamd, 0x55:Start; 0xFF:Stop
extern Byte byDCDCComm_4;            //DCDC4 commmamd, 0x55:Start; 0xFF:Stop
extern Byte byDCACComm_4;            //DCAC4 commmamd, 0x55:Start; 0xFF:Stop
#if 0    //shenmin
extern int iDCDC_Output_Volt_1;      //DCDC1 output voltage
extern int iDCDC_Output_Cur_1;       //DCAC1 output current
extern int iDCDC_Input_Volt_1;       //DCDC1 input voltage
extern Byte byDCDC_Temperature_1;    //DCDC1 temperature
extern Byte byDCDC_ErrCode_1;        //DCDC1 error code

extern int iDCAC_Output_Volt_1;      //DCAC1 output voltage
extern int iDCAC_Output_Cur_1;       //DCAC1 output current
extern Byte byDCAC_Temperature_1;    //DCAC1 temperature
extern Byte byDCAC_ErrCode_1;        //DCAC1 error code

extern int iDCDC_Output_Volt_2;      //DCDC2 output voltage
extern int iDCDC_Output_Cur_2;       //DCAC2 output current
extern int iDCDC_Input_Volt_2;       //DCDC2 input voltage
extern Byte byDCDC_Temperature_2;    //DCDC2 temperature
extern Byte byDCDC_ErrCode_2;        //DCDC2 error code

extern int iDCAC_Output_Volt_2;      //DCAC1 output voltage
extern int iDCAC_Output_Cur_2;       //DCAC1 output current
extern Byte byDCAC_Temperature_2;    //DCAC1 temperature
extern Byte byDCAC_ErrCode_2;        //DCAC1 error code

extern int iDCDC_Output_Volt_3;      //DCDC3 output voltage
extern int iDCDC_Output_Cur_3;       //DCAC3 output current
extern int iDCDC_Input_Volt_3;       //DCDC3 input voltage
extern Byte byDCDC_Temperature_3;    //DCDC3 temperature
extern Byte byDCDC_ErrCode_3;        //DCDC3 error code

extern int iDCAC_Output_Volt_3;      //DCAC1 output voltage
extern int iDCAC_Output_Cur_3;       //DCAC1 output current
extern Byte byDCAC_Temperature_3;    //DCAC1 temperature
extern Byte byDCAC_ErrCode_3;        //DCAC1 error code

extern int iDCDC_Output_Volt_4;      //DCDC4 output voltage
extern int iDCDC_Output_Cur_4;       //DCAC4 output current
extern int iDCDC_Input_Volt_4;       //DCDC4 input voltage
extern Byte byDCDC_Temperature_4;    //DCDC4 temperature
extern Byte byDCDC_ErrCode_4;        //DCDC4 error code

extern int iDCAC_Output_Volt_4;      //DCAC1 output voltage
extern int iDCAC_Output_Cur_4;       //DCAC1 output current
extern Byte byDCAC_Temperature_4;    //DCAC1 temperature
extern Byte byDCAC_ErrCode_4;        //DCAC1 error code
#endif    //shenmin
//CAN3
extern Byte byCommand1;              //Commmand 1 to VCU5/6/7/8
extern Byte byCommand2;              //Commmand 2 to VCU5/6/7/8
extern int iDestHeight;              //Destinate height from VCU2/3

extern Byte byBrakeTest;             //Brake test command from HMI
extern Byte bySuspensionTest;        //Suspension test command from HMI
extern Byte byBalanceTemp;           //Balance command from HMI
extern Byte byBalance;               //Balance command to suspension
extern Byte byCamera;                //Active camera from HMI
extern Byte byEnergySaving;          //Energy saving
extern Byte byMotorStart;            //Motor Start
extern Byte byParking;               //Parking status


#if 0   //shenmin
extern int iPump_Pressure_VCU5;
extern int iCylinder_Pressure_VCU5;
extern int iEnergy_Saving_VCU5;
extern int iBrakeEffort_VCU5;

extern int iPump_Pressure_VCU6;
extern int iCylinder_Pressure_VCU6;
extern int iEnergy_Saving_VCU6;
extern int iBrakeEffort_VCU6;

extern int iPump_Pressure_VCU7;
extern int iCylinder_Pressure_VCU7;
extern int iEnergy_Saving_VCU7;
extern int iBrakeEffort_VCU7;

extern int iPump_Pressure_VCU8;
extern int iCylinder_Pressure_VCU8;
extern int iEnergy_Saving_VCU8;
extern int iBrakeEffort_VCU8;
#endif //shenmin


