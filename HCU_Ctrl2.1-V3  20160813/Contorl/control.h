#include <hidef.h>  
#include <MC9S12XEP100.h>
#include <string.h>

#include "Data.h"





void Vcu_Control_Main(void);
void GPIODrv_GetValue(void);
void GPIODrv_SetValue(void); 
void Vcu_Get_MasterSlave_State(void);
void Vcu_BMS_Management(void);
void Vcu_ACM_Management(void);
void Vcu_Close_Contact(void);
void Vcu_Open_Contact(void);
void Vcu_Propulsion_Management(void);
void Vcu_TrRef_Calc(void);
void Vcu_BrRef_Calc(void);
void Vcu_TrTorque_Calc(void);
//void Vcu_Suspension_Management(void);   //shenmin
void Vcu_Brake_Management(void);
void Vcu_TrBlk_Chk(void);


#define START_ACM 0x55
#define STOP_ACM  0xFF