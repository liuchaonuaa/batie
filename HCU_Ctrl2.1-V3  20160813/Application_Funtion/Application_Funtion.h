#include <MC9S12XEP100.h>
#include <hidef.h>    
#include <string.h>
#include "SPI.h"
//#include "Data.h"



     #define OPEN 0x55
     #define LOCKED 0xAA
     #define analog_semaphore_mcu 0//共享数据锁定标识符
     #define analog_semaphore_mcu 0//共享数据锁定标识符
     #define dout_semaphore_mcu 1
     #define din_semaphore_mcu 2
     #define can_semaphore_mcu 3
     #define pwm_semaphore_mcu 4
     
    //12路高低边驱动
    #define O_S_H1_114   1          //高边驱动1 114脚
    #define O_S_H2_117   2          //高边驱动2 117脚
    #define O_S_H3_116   3          //高边驱动3 116脚
    #define O_S_H4_118   4          //高边驱动4 118脚
    #define O_S_H5_121   5          //高边驱动5 121脚
    #define O_S_H6_115   6          //高边驱动6 115脚
    #define O_S_H7_96    7           //高边驱动7 96脚
    #define O_S_H8_97    8           //高边驱动8 97脚
    #define O_S_H9_89    9           //高边驱动9 89脚
    #define O_S_H10_88   10          //高边驱动10 88脚
    #define O_S_H11_119  11         //高边驱动11 119脚
    #define O_S_H12_120  12         //高边驱动12 120脚
    #define O_S_L1_62    13         //低边驱动13 62脚
    #define O_S_L2_81    14         //低边驱动14 81脚
    #define O_S_L3_61    15         //低边驱动15 61脚
    #define O_S_MRLY_80  16         //延时断电继电器控制 80脚
    
    void Digital_Output(Byte Channel,Byte bOpenUB);
    
    
    #define  I_A_V1_10       2  //模拟量输入采集1 10脚
    #define  I_A_V2_9        1    //模拟量输入采集2 9脚
    #define  I_A_V3_8        3   //模拟量输入采集3 8脚
    #define  I_A_V4_7        4    //模拟量输入采集4 7脚
    #define  I_A_V5_6        5   //模拟量输入采集5 6脚
    #define  I_A_V6_25       6   //模拟量输入采集6 25脚
    #define  I_A_V7_26       7   //模拟量输入采集7 26脚
    #define  I_A_V8_27       8   //模拟量输入采集8 27脚
    #define  I_A_V9_28       9   //模拟量输入采集9 28脚
    #define  I_A_0_50mA2_69  10   //电流值
    #define  I_P_24V         11   //蓄电池电压
    #define  I_A_PC50mA1_49  12  //电流采样 49脚
    #define  I_A_PC50mA2_68  13    //电流采样  68脚
    #define  I_A_0_50mA1_50  14    //电流采样  14脚

    word Analog_Input(byte Channel);
    
    
    
    #define  I_S_H1_110 1       //对应管脚110脚，高电平有效
    #define  I_S_H2_102 2       //对应管脚102脚，高电平有效
    #define  I_S_H3_111 3       //对应管脚111脚，高电平有效
    #define  I_S_H4_103 4       //对应管脚103脚，高电平有效
    #define  I_S_H5_112 5       //对应管脚112脚，高电平有效
    #define  I_S_H6_104 6       //对应管脚104脚，高电平有效
    #define  I_S_H7_94  7        //对应管脚94脚，高电平有效
  
    #define  LOGIC_P_STATE 8    //逻辑电输入
              
    #define  I_S_HL2_84 9               //软件配置高低有效1 84脚
    #define  I_S_HL3_85 10               //软件配置高低有效2 85脚
    #define  I_S_HL1_91 11               //软件配置高低有效3 91脚
    #define  I_S_HL4_90 12                 //软件配置高低有效4 90脚
    #define  I_S_HL5_83 13                 //软件配置高低有效5 83脚
    #define  I_S_HL6_82 14                 //软件配置高低有效6 82脚
    #define  I_S_HL7_85 15                //软件配置高低有效7 85脚
    
    byte Digital_Input(byte Channel , byte HorL);   //HorL为高低有效配置，对软件高低配有效，0为低有效，1为高有效

// float analog_get_from_xgate(void) ;
 
   //-----------------------------------模拟量输出变量-------------------------------------------
    #define O_A_1_45    0                       // 模拟量输出45 输出频率定1000  占空比0-100对应0-5V
    #define O_A_2_44    2                       // 模拟量输出44 输出频率定1000  占空比0-100对应0-5V

//-------------------------------------频率量输出控制变量-----------------------------------
    #define O_F_BAK1_42  4                      // 频率量输出 占空比0-100%   对应频率500HZ - 5000HZ 
    #define O_F_BAK2_23  5                      // 频率量输出 占空比0-100%   对应频率500HZ - 5000HZ
    #define O_F_BAK3_24  6                      // 频率量输出 占空比0-100%   对应频率500HZ - 5000HZ
    #define O_F_BAK4_43  7                      // 频率量输出 占空比0-100%   对应频率500HZ - 5000HZ
 
 
 void PWM_duty_updata_8bit(Byte channel_num,float duty,word frequency);    //channel_num选择通道，duty占空比
 
 //void PWM_duty_updata_16bit(uint8_T channel_num,float value);  //16位PWM输出，暂时未用
 
 void AcquireAccessToSharedMemory(int idx);
 void ReleaseAccessToSharedMemory(int idx);
 


extern Byte task_level_2P5ms;        //定时器变量 MAIN函数中调用 控制整个周期时序
extern Byte task_level_2ms;
extern Byte task_level_4ms;
extern Byte task_level_5ms;
extern Byte task_level_6ms;
extern Byte task_level_8ms;
extern Byte task_level_10ms;
extern Byte task_level_20ms;
extern Byte task_level_40ms;
extern Byte task_level_50ms;
extern Byte task_level_60ms;
extern Byte task_level_80ms;
extern Byte task_level_100ms;
extern Byte task_level_120ms;
extern Byte task_level_160ms;
extern Byte task_level_300ms;
extern Byte task_level_400ms;
extern Byte task_level_512ms;
extern Byte task_level_600ms;
extern Byte task_level_640ms;
extern Byte task_level_1000ms;
extern Byte task_level_1200ms;

extern Word pc_counter;
extern Byte main_controller_life;
extern Byte port_init_en;

extern float analog_channel_avr[10];

//-------------------------------------频率量输人控制变量-----------------------------------
extern Word I_F_1_105;            //频率量输入频率1，直接调用此全剧变量 105脚
extern Word I_F_2_113;            //频率量输入频率1，直接调用此全剧变量 113脚


