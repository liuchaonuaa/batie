#include <MC9S12XEP100.h>
#include <hidef.h>    
#include <string.h>
#include "SPI.h"
//#include "Data.h"



     #define OPEN 0x55
     #define LOCKED 0xAA
     #define analog_semaphore_mcu 0//��������������ʶ��
     #define analog_semaphore_mcu 0//��������������ʶ��
     #define dout_semaphore_mcu 1
     #define din_semaphore_mcu 2
     #define can_semaphore_mcu 3
     #define pwm_semaphore_mcu 4
     
    //12·�ߵͱ�����
    #define O_S_H1_114   1          //�߱�����1 114��
    #define O_S_H2_117   2          //�߱�����2 117��
    #define O_S_H3_116   3          //�߱�����3 116��
    #define O_S_H4_118   4          //�߱�����4 118��
    #define O_S_H5_121   5          //�߱�����5 121��
    #define O_S_H6_115   6          //�߱�����6 115��
    #define O_S_H7_96    7           //�߱�����7 96��
    #define O_S_H8_97    8           //�߱�����8 97��
    #define O_S_H9_89    9           //�߱�����9 89��
    #define O_S_H10_88   10          //�߱�����10 88��
    #define O_S_H11_119  11         //�߱�����11 119��
    #define O_S_H12_120  12         //�߱�����12 120��
    #define O_S_L1_62    13         //�ͱ�����13 62��
    #define O_S_L2_81    14         //�ͱ�����14 81��
    #define O_S_L3_61    15         //�ͱ�����15 61��
    #define O_S_MRLY_80  16         //��ʱ�ϵ�̵������� 80��
    
    void Digital_Output(Byte Channel,Byte bOpenUB);
    
    
    #define  I_A_V1_10       2  //ģ��������ɼ�1 10��
    #define  I_A_V2_9        1    //ģ��������ɼ�2 9��
    #define  I_A_V3_8        3   //ģ��������ɼ�3 8��
    #define  I_A_V4_7        4    //ģ��������ɼ�4 7��
    #define  I_A_V5_6        5   //ģ��������ɼ�5 6��
    #define  I_A_V6_25       6   //ģ��������ɼ�6 25��
    #define  I_A_V7_26       7   //ģ��������ɼ�7 26��
    #define  I_A_V8_27       8   //ģ��������ɼ�8 27��
    #define  I_A_V9_28       9   //ģ��������ɼ�9 28��
    #define  I_A_0_50mA2_69  10   //����ֵ
    #define  I_P_24V         11   //���ص�ѹ
    #define  I_A_PC50mA1_49  12  //�������� 49��
    #define  I_A_PC50mA2_68  13    //��������  68��
    #define  I_A_0_50mA1_50  14    //��������  14��

    word Analog_Input(byte Channel);
    
    
    
    #define  I_S_H1_110 1       //��Ӧ�ܽ�110�ţ��ߵ�ƽ��Ч
    #define  I_S_H2_102 2       //��Ӧ�ܽ�102�ţ��ߵ�ƽ��Ч
    #define  I_S_H3_111 3       //��Ӧ�ܽ�111�ţ��ߵ�ƽ��Ч
    #define  I_S_H4_103 4       //��Ӧ�ܽ�103�ţ��ߵ�ƽ��Ч
    #define  I_S_H5_112 5       //��Ӧ�ܽ�112�ţ��ߵ�ƽ��Ч
    #define  I_S_H6_104 6       //��Ӧ�ܽ�104�ţ��ߵ�ƽ��Ч
    #define  I_S_H7_94  7        //��Ӧ�ܽ�94�ţ��ߵ�ƽ��Ч
  
    #define  LOGIC_P_STATE 8    //�߼�������
              
    #define  I_S_HL2_84 9               //������øߵ���Ч1 84��
    #define  I_S_HL3_85 10               //������øߵ���Ч2 85��
    #define  I_S_HL1_91 11               //������øߵ���Ч3 91��
    #define  I_S_HL4_90 12                 //������øߵ���Ч4 90��
    #define  I_S_HL5_83 13                 //������øߵ���Ч5 83��
    #define  I_S_HL6_82 14                 //������øߵ���Ч6 82��
    #define  I_S_HL7_85 15                //������øߵ���Ч7 85��
    
    byte Digital_Input(byte Channel , byte HorL);   //HorLΪ�ߵ���Ч���ã�������ߵ�����Ч��0Ϊ����Ч��1Ϊ����Ч

// float analog_get_from_xgate(void) ;
 
   //-----------------------------------ģ�����������-------------------------------------------
    #define O_A_1_45    0                       // ģ�������45 ���Ƶ�ʶ�1000  ռ�ձ�0-100��Ӧ0-5V
    #define O_A_2_44    2                       // ģ�������44 ���Ƶ�ʶ�1000  ռ�ձ�0-100��Ӧ0-5V

//-------------------------------------Ƶ����������Ʊ���-----------------------------------
    #define O_F_BAK1_42  4                      // Ƶ������� ռ�ձ�0-100%   ��ӦƵ��500HZ - 5000HZ 
    #define O_F_BAK2_23  5                      // Ƶ������� ռ�ձ�0-100%   ��ӦƵ��500HZ - 5000HZ
    #define O_F_BAK3_24  6                      // Ƶ������� ռ�ձ�0-100%   ��ӦƵ��500HZ - 5000HZ
    #define O_F_BAK4_43  7                      // Ƶ������� ռ�ձ�0-100%   ��ӦƵ��500HZ - 5000HZ
 
 
 void PWM_duty_updata_8bit(Byte channel_num,float duty,word frequency);    //channel_numѡ��ͨ����dutyռ�ձ�
 
 //void PWM_duty_updata_16bit(uint8_T channel_num,float value);  //16λPWM�������ʱδ��
 
 void AcquireAccessToSharedMemory(int idx);
 void ReleaseAccessToSharedMemory(int idx);
 


extern Byte task_level_2P5ms;        //��ʱ������ MAIN�����е��� ������������ʱ��
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

//-------------------------------------Ƶ�������˿��Ʊ���-----------------------------------
extern Word I_F_1_105;            //Ƶ��������Ƶ��1��ֱ�ӵ��ô�ȫ����� 105��
extern Word I_F_2_113;            //Ƶ��������Ƶ��1��ֱ�ӵ��ô�ȫ����� 113��


