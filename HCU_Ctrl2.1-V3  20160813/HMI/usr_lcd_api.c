#include"lr_lcd_api.h"
#include "can.h"
#include "UserFunction.h"
#include "usr_lcd_api.h"





// page 2
word cab11StatusID[2] = { ID_LBMP_3159, ID_LBMP_3157};
word cab22StatusID[2] = { ID_LBMP_3160, ID_LBMP_3158};


word motor1StatusID[3] = { MOTOR1_NORMAL_ID, MOTOR1_WORKING_ID, MOTOR1_ALARM_ID};
word motor2StatusID[3] = { MOTOR2_NORMAL_ID, MOTOR2_WORKING_ID, MOTOR2_ALARM_ID};
word motor3StatusID[3] = { MOTOR3_NORMAL_ID, MOTOR3_WORKING_ID, MOTOR3_ALARM_ID};
word motor4StatusID[3] = { MOTOR4_NORMAL_ID, MOTOR4_WORKING_ID, MOTOR4_ALARM_ID};
word motor5StatusID[3] = { MOTOR5_NORMAL_ID, MOTOR5_WORKING_ID, MOTOR5_ALARM_ID};
word motor6StatusID[3] = { MOTOR6_NORMAL_ID, MOTOR6_WORKING_ID, MOTOR6_ALARM_ID};
word motor7StatusID[3] = { MOTOR7_NORMAL_ID, MOTOR7_WORKING_ID, MOTOR7_ALARM_ID};
word motor8StatusID[3] = { MOTOR8_NORMAL_ID, MOTOR8_WORKING_ID, MOTOR8_ALARM_ID};

word bianliu1StatusID[3] = { BIANLIU1_NORMAL_ID, BIANLIU1_WORKING_ID, BIANLIU1_ALARM_ID};
word bianliu2StatusID[3] = { BIANLIU2_NORMAL_ID, BIANLIU2_WORKING_ID, BIANLIU2_ALARM_ID};
word bianliu3StatusID[3] = { BIANLIU3_NORMAL_ID, BIANLIU3_WORKING_ID, BIANLIU3_ALARM_ID};
word bianliu4StatusID[3] = { BIANLIU4_NORMAL_ID, BIANLIU4_WORKING_ID, BIANLIU4_ALARM_ID};
word bianliu5StatusID[3] = { BIANLIU5_NORMAL_ID, BIANLIU5_WORKING_ID, BIANLIU5_ALARM_ID};
word bianliu6StatusID[3] = { BIANLIU6_NORMAL_ID, BIANLIU6_WORKING_ID, BIANLIU6_ALARM_ID};
word bianliu7StatusID[3] = { BIANLIU7_NORMAL_ID, BIANLIU7_WORKING_ID, BIANLIU7_ALARM_ID};
word bianliu8StatusID[3] = { BIANLIU8_NORMAL_ID, BIANLIU8_WORKING_ID, BIANLIU8_ALARM_ID};






word bat1StatusID[22] = {
   IID_LBMP_2661,  IID_LBMP_2663, IID_LBMP_2665,  IID_LBMP_2667, IID_LBMP_2669, IID_LBMP_2671, IID_LBMP_2673, IID_LBMP_2675,
   IID_LBMP_2676,  IID_LBMP_2678, IID_LBMP_2681,  IID_LBMP_2683, IID_LBMP_2685, IID_LBMP_2687, IID_LBMP_2689, IID_LBMP_2690,
   IID_LBMP_2693,  IID_LBMP_2695, IID_LBMP_2697,  IID_LBMP_2699, IID_LBMP_2701, IID_LBMP_2639
};


word bat2StatusID[22] = {
   IID_LBMP_2660,  IID_LBMP_2662, IID_LBMP_2664,  IID_LBMP_2666, IID_LBMP_2668, IID_LBMP_2670, IID_LBMP_2672, IID_LBMP_2674,
   IID_LBMP_2677,  IID_LBMP_2679, IID_LBMP_2680,  IID_LBMP_2682, IID_LBMP_2684, IID_LBMP_2686, IID_LBMP_2688, IID_LBMP_2691,
   IID_LBMP_2692,  IID_LBMP_2694, IID_LBMP_2696,  IID_LBMP_2698, IID_LBMP_2700, IID_LBMP_2640
};


word bat1ErrID[8] = {
   IID_LBMP_2712,  IID_LBMP_2702, IID_LBMP_2703, IID_LBMP_2705, IID_LBMP_2704, IID_LBMP_2706, IID_LBMP_2707, 
};

word bat2ErrID[8] = {
   IID_LBMP_2713,  IID_LBMP_2702, IID_LBMP_2703, IID_LBMP_2705, IID_LBMP_2704, IID_LBMP_2706, IID_LBMP_2707, 
};


word bat1DelayID[2] = {
   IID_LBMP_2711,  IID_LBMP_2714 
};

word bat2DelayID[2] = {
   IID_LBMP_2710,  IID_LBMP_2714 
};



 // page 2
void showSpeedValue2(dword ID, float value) 
{
    MY_LCD_SetValueToEdite3(CAB_CAN, ID, ID_EDITE_3113, value);
}


void setCab11Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, cab11StatusID[status], CAB11_X, CAB11_Y); 
}

void setCab22Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, cab22StatusID[status], CAB22_X, CAB22_Y); 
}



void setMotor1Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, motor1StatusID[status], MOTOR1_X, MOTOR1_Y); 
}

void setMotor2Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, motor2StatusID[status], MOTOR2_X, MOTOR2_Y); 
}

void setMotor3Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, motor3StatusID[status], MOTOR3_X, MOTOR3_Y); 
}

void setMotor4Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, motor4StatusID[status], MOTOR4_X, MOTOR4_Y); 
}

void setMotor5Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, motor5StatusID[status], MOTOR5_X, MOTOR5_Y); 
}

void setMotor6Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, motor6StatusID[status], MOTOR6_X, MOTOR6_Y); 
}

void setMotor7Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, motor7StatusID[status], MOTOR7_X, MOTOR7_Y); 
}

void setMotor8Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, motor8StatusID[status], MOTOR8_X, MOTOR8_Y); 
}




void setBianliu1Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, bianliu1StatusID[status], BIANLIU1_X, BIANLIU1_Y); 
}

void setBianliu2Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, bianliu2StatusID[status], BIANLIU2_X, BIANLIU2_Y); 
}

void setBianliu3Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, bianliu3StatusID[status], BIANLIU3_X, BIANLIU3_Y); 
}

void setBianliu4Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, bianliu4StatusID[status], BIANLIU4_X, BIANLIU4_Y); 
}

void setBianliu5Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, bianliu5StatusID[status], BIANLIU5_X, BIANLIU5_Y); 
}

void setBianliu6Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, bianliu6StatusID[status], BIANLIU6_X, BIANLIU6_Y); 
}

void setBianliu7Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, bianliu7StatusID[status], BIANLIU7_X, BIANLIU7_Y); 
}

void setBianliu8Status(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, bianliu8StatusID[status], BIANLIU8_X, BIANLIU8_Y); 
}







void setBat1Status(dword ID, Byte status)
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, bat1StatusID[status], BAT1STATUS_X, BAT1STATUS_Y); 
}

void setBat2Status(dword ID, Byte status)
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, bat2StatusID[status], BAT2STATUS_X, BAT2STATUS_Y); 
}


void setBat1ErrStatus(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, bat1ErrID[status], BAT1ERROR_X, BAT1ERROR_Y); 
}

void setBat2ErrStatus(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, bat2ErrID[status], BAT2ERROR_X, BAT2ERROR_Y); 
}

void setBat1DelayStatus(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, bat1DelayID[status], BAT1DELAY_X, BAT1DELAY_Y); 
}

void setBat2DelayStatus(dword ID, Byte status) 
{
    MY_LCD_LoadPartBmpEx2(CAB_CAN, ID, LOCBMP_ITEM, bat2DelayID[status], BAT2DELAY_X, BAT2DELAY_Y); 
}



void setBat1TotalVol(dword ID, float vol) 
{
    MY_LCD_SetValueToEdite3(CAB_CAN, ID, IID_EDITE_2647, vol); 
}

void setBat2TotalVol(dword ID, float vol) 
{
    MY_LCD_SetValueToEdite3(CAB_CAN, ID, IID_EDITE_2656, vol); 
}


void setBat1TotalCurrent(dword ID, float current) 
{
    MY_LCD_SetValueToEdite3(CAB_CAN, ID, IID_EDITE_2650, current); 
}

void setBat2TotalCurrent(dword ID, float current) 
{
    MY_LCD_SetValueToEdite3(CAB_CAN, ID, IID_EDITE_2657, current); 
}


void setBat1SOC(dword ID, float value) 
{
    MY_LCD_SetValueToEdite3(CAB_CAN, ID, IID_EDITE_2653, value); 
}

void setBat2SOC(dword ID, float value) 
{
    MY_LCD_SetValueToEdite3(CAB_CAN, ID, IID_EDITE_2658, value); 
}





