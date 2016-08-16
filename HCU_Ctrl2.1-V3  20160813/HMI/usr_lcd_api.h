#ifndef  __USR_LCD_API_H__
#define  __USR_LCD_API_H__

#include "UserFunction.h"



#define CAB_CAN  CAN0



// page 1
#define  CAB_ACTIVE    0
#define  CAB_INACTIVE  1

// page 2
#define  STATUS_NOMAL    0
#define  STATUS_WORKING  1
#define  STATUS_ALARM    2




// page 2

#define CAB11_X  12
#define CAB11_Y  236    

#define CAB11_GREEN_ID   ID_LBMP_3159
#define CAB11_RED_ID     ID_LBMP_3157

#define CAB22_X  688
#define CAB22_Y  236

#define CAB22_GREEN_ID   ID_LBMP_3160
#define CAB22_RED_ID     ID_LBMP_3158






#define MOTOR1_X    71
#define MOTOR1_Y    299
#define BIANLIU1_X  71
#define BIANLIU1_Y  352

#define MOTOR1_NORMAL_ID    ID_LBMP_2825 
#define MOTOR1_WORKING_ID   ID_LBMP_2858 
#define MOTOR1_ALARM_ID     ID_LBMP_2859 

#define BIANLIU1_NORMAL_ID    ID_LBMP_2821 
#define BIANLIU1_WORKING_ID   ID_LBMP_2850 
#define BIANLIU1_ALARM_ID     ID_LBMP_2851 
 

#define MOTOR2_X    71
#define MOTOR2_Y    157
#define BIANLIU2_X  71
#define BIANLIU2_Y  116 

#define MOTOR2_NORMAL_ID    ID_LBMP_2817 
#define MOTOR2_WORKING_ID   ID_LBMP_2841 
#define MOTOR2_ALARM_ID     ID_LBMP_2842 

#define BIANLIU2_NORMAL_ID    ID_LBMP_2813 
#define BIANLIU2_WORKING_ID   ID_LBMP_2833 
#define BIANLIU2_ALARM_ID     ID_LBMP_2834 



#define MOTOR3_X    247
#define MOTOR3_Y    299
#define BIANLIU3_X  247
#define BIANLIU3_Y  352



#define MOTOR3_NORMAL_ID    ID_LBMP_2826 
#define MOTOR3_WORKING_ID   ID_LBMP_2860 
#define MOTOR3_ALARM_ID     ID_LBMP_2861 

#define BIANLIU3_NORMAL_ID    ID_LBMP_2822 
#define BIANLIU3_WORKING_ID   ID_LBMP_2852 
#define BIANLIU3_ALARM_ID     ID_LBMP_2853 



#define MOTOR4_X    247
#define MOTOR4_Y    157
#define BIANLIU4_X  247
#define BIANLIU4_Y  116


#define MOTOR4_NORMAL_ID    ID_LBMP_2818 
#define MOTOR4_WORKING_ID   ID_LBMP_2843 
#define MOTOR4_ALARM_ID     ID_LBMP_2844

#define BIANLIU4_NORMAL_ID    ID_LBMP_2814 
#define BIANLIU4_WORKING_ID   ID_LBMP_2835 
#define BIANLIU4_ALARM_ID     ID_LBMP_2836 



#define MOTOR5_X    441
#define MOTOR5_Y    299
#define BIANLIU5_X  441
#define BIANLIU5_Y  352 



#define MOTOR5_NORMAL_ID    ID_LBMP_2827 
#define MOTOR5_WORKING_ID   ID_LBMP_2862 
#define MOTOR5_ALARM_ID     ID_LBMP_2863 

#define BIANLIU5_NORMAL_ID    ID_LBMP_2823 
#define BIANLIU5_WORKING_ID   ID_LBMP_2854 
#define BIANLIU5_ALARM_ID     ID_LBMP_2855 




#define MOTOR6_X    441
#define MOTOR6_Y    157
#define BIANLIU6_X  441
#define BIANLIU6_Y  116 



#define MOTOR6_NORMAL_ID    ID_LBMP_2819 
#define MOTOR6_WORKING_ID   ID_LBMP_2845 
#define MOTOR6_ALARM_ID     ID_LBMP_2846 

#define BIANLIU6_NORMAL_ID    ID_LBMP_2816 
#define BIANLIU6_WORKING_ID   ID_LBMP_2837 
#define BIANLIU6_ALARM_ID     ID_LBMP_2838 

#define MOTOR7_X    618
#define MOTOR7_Y    299
#define BIANLIU7_X  618
#define BIANLIU7_Y  352


#define MOTOR7_NORMAL_ID    ID_LBMP_2828 
#define MOTOR7_WORKING_ID   ID_LBMP_2864 
#define MOTOR7_ALARM_ID     ID_LBMP_2865 

#define BIANLIU7_NORMAL_ID    ID_LBMP_2824 
#define BIANLIU7_WORKING_ID   ID_LBMP_2856 
#define BIANLIU7_ALARM_ID     ID_LBMP_2857 



#define MOTOR8_X    618
#define MOTOR8_Y    157
#define BIANLIU8_X  618
#define BIANLIU8_Y  116

#define MOTOR8_NORMAL_ID    ID_LBMP_2820 
#define MOTOR8_WORKING_ID   ID_LBMP_2848 
#define MOTOR8_ALARM_ID     ID_LBMP_2849 

#define BIANLIU8_NORMAL_ID    ID_LBMP_2815 
#define BIANLIU8_WORKING_ID   ID_LBMP_2839 
#define BIANLIU8_ALARM_ID     ID_LBMP_2840 








#define BAT1STATUS_X   55  
#define BAT1STATUS_Y   132

#define BAT2STATUS_X   416  
#define BAT2STATUS_Y   132

#define BAT1ERROR_X   133
#define BAT1ERROR_Y   499

#define BAT2ERROR_X   493  
#define BAT2ERROR_Y   499

#define BAT1DELAY_X   264
#define BAT1DELAY_Y   450

#define BAT2DELAY_X   626
#define BAT2DELAY_Y   450



// 电池充放电类型
#define  BAT_0Perc_CHARGE   0
#define  BAT_10Perc_CHARGE  1 
#define  BAT_20Perc_CHARGE  2
#define  BAT_30Perc_CHARGE  3 
#define  BAT_40Perc_CHARGE  4                   
#define  BAT_50Perc_CHARGE  5 
#define  BAT_60Perc_CHARGE  6
#define  BAT_70Perc_CHARGE  7 
#define  BAT_80Perc_CHARGE  8
#define  BAT_90Perc_CHARGE  9 
#define  BAT_100Perc_CHARGE 10



#define  BAT_0Perc_DISCHARGE   11
#define  BAT_10Perc_DISCHARGE  12 
#define  BAT_20Perc_DISCHARGE  13
#define  BAT_30Perc_DISCHARGE  14 
#define  BAT_40Perc_DISCHARGE  15                   
#define  BAT_50Perc_DISCHARGE  16 
#define  BAT_60Perc_DISCHARGE  17
#define  BAT_70Perc_DISCHARGE  18 
#define  BAT_80Perc_DISCHARGE  19
#define  BAT_90Perc_DISCHARGE  20 
#define  BAT_100Perc_DISCHARGE  21


// 总正继电器状态
#define  DELAY_STATUS_ON      0
#define  DELAY_STATUS_OFF     1



// 故障类型
#define  ERROR_NONE             0
#define  ERROR_OVERLOWTEMP      1
#define  ERROR_OVERHIGHTEMP     2
#define  ERROR_OVERDISCHARGE    3
#define  ERROR_OVERCHARGE       4
#define  ERROR_COMM             5
#define  ERROR_CONSISTENCY      6  




















 // page 2 
void setCab11Status(dword ID, Byte status); 
void setCab22Status(dword ID, Byte status);
void showSpeedValue2(dword ID, float value);
 
void setMotor1Status(dword ID, Byte status); 
void setMotor2Status(dword ID, Byte status); 
void setMotor3Status(dword ID, Byte status); 
void setMotor4Status(dword ID, Byte status); 
void setMotor5Status(dword ID, Byte status); 
void setMotor6Status(dword ID, Byte status); 
void setMotor7Status(dword ID, Byte status); 
void setMotor8Status(dword ID, Byte status); 


void setBianliu1Status(dword ID, Byte status); 
void setBianliu2Status(dword ID, Byte status); 
void setBianliu3Status(dword ID, Byte status); 
void setBianliu4Status(dword ID, Byte status);
void setBianliu5Status(dword ID, Byte status); 
void setBianliu6Status(dword ID, Byte status); 
void setBianliu7Status(dword ID, Byte status); 
void setBianliu8Status(dword ID, Byte status); 







void setBat1Status(dword ID, Byte status);
void setBat2Status(dword ID, Byte status);
void setBat1ErrStatus(dword ID, Byte status); 
void setBat2ErrStatus(dword ID, Byte status); 
void setBat1DelayStatus(dword ID, Byte status);
void setBat2DelayStatus(dword ID, Byte status); 
void setBat1TotalVol(dword ID, float vol); 
void setBat2TotalVol(dword ID, float vol);
void setBat1TotalCurrent(dword ID, float current); 
void setBat2TotalCurrent(dword ID, float current); 
void setBat1SOC(dword ID, float value); 
void setBat2SOC(dword ID, float value); 
















#endif