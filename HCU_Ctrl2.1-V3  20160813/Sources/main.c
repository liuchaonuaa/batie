#include <hidef.h>      /* common defines and macros */
#include <MC9S12XEP100.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12xep100"


#include <string.h> 
#include <MATH.H>

#include "Data.h"

#include "usr_lcd_api.h"





#pragma DATA_SEG_RPAGE_SEG PAGED_RAM 
/* extern   real_T G350V_init_pwm_map2D[304];
 extern   real_T G400V_init_pwm_map2D[304];
 extern   real_T G450V_init_pwm_map2D[304];
extern   real_T controller_temper_limit_torque_map2D[144];
 extern   real_T motor_speed_torque_effection_map2D[210];
 extern   real_T motor_temper_limit_torque_map2D[144];
 extern   real_T engine_init_pedal_map2D[135]; */
#pragma DATA_SEG DEFAULT

#pragma DATA_SEG SHARED_DATA
volatile int shared_counter; /* volatile because both cores are accessing it. */
volatile word i_test_transfer;
volatile word i_test_transfer1;
volatile int i_test_word[10];


//-------------------CAN--------------------------------
volatile  Byte CAN1_ID_box[8][4];              //CAN1 ID��Ӧ4����ÿ��ͨ��4byte����װ��
volatile  Byte CAN1_TxBuffer_box[8][8];       //CAN1����4֡���ģ�ÿ֡����8���ֽ�  �������÷��ͱ��ĸ�����ÿһ����֡��Ӧ���ͺ���PFֵ
volatile  Byte CAN3_ID_box[5][4];              //CAN2 ID��Ӧ8����ÿ��ͨ��4byte����װ��
volatile  Byte CAN3_TxBuffer_box[5][8];        //CAN2����8֡���ģ�ÿ֡����8���ֽ�  �������÷��ͱ��ĸ�����
volatile  Byte CAN2_ID_box[1][4];                //CAN3 ID��Ӧ1����ÿ��ͨ��4byte����װ��
volatile  Byte CAN2_TxBuffer_box[1][8];        //CAN4����1֡���ģ�ÿ֡����8���ֽ�  �������÷��ͱ��ĸ�����
volatile  Byte CAN0_ID_box[2][4];                 //CAN4 ID��Ӧ4����ÿ��ͨ��4byte����װ��
volatile  Byte CAN0_TxBuffer_box[2][8];         //CAN4����8֡���ģ�ÿ֡����8���ֽ�  �������÷��ͱ��ĸ�����

volatile  Byte xgate_pc_2ms;
volatile  Byte xgate_pc_10ms;
volatile  Byte xgate_pc_20ms;
volatile  Byte xgate_pc_50ms;
volatile  Byte xgate_pc_100ms;
volatile  Byte xgate_pc_200ms;
volatile  Byte xgate_pc_500ms;


         
//--------------------PWM-------------------------------
volatile Byte pwm_num;
volatile Word pwm_value;




#pragma DATA_SEG DEFAULT




void FeedWatchDog(void) //ι��
{

/* if(SCI_COUNTER >=8) 
 {
   COPCTL = 0x01;        //enable watchdog
   ARMCOP = 0x00;

 } 
 else 
 { */
    ARMCOP = 0x55;
  	ARMCOP = 0xAA;
 //}
}






/***********************************************************************************************
 *                                                                                             *
 *                                        MAIN                                                 *
 *                                                                                             *
 * �� �� ��:                                                                                   *
 * ��������: ������                                                                            *
 * ȫ�ֱ���:                                                                                   *
 * ��		 ��:                                                                                   *
 * ��		 ��:                                                                                   *
 * ��    ����---                                                                  *
 * �� �� �ˣ�  			 						 	                                                             *
 * �޸����ڣ�                                                                                  *
 * ����˵��:                                                                                   *
 /**********************************************************************************************/
//-------------------------------------------------------------------------------------------
void main(void) 
{ 
    DisableInterrupts;
    Start_init(2, 2, 2, 2);
    FMSTR_Init();
    him_init();
    pageIndex = 2;

    EnableInterrupts;

    /* put your own code here */
    for(;;)  
    {      

        if (task_level_2ms==OPEN)
        {

            task_level_2ms=LOCKED;
        }      

        if (task_level_4ms==OPEN)
        {	 		   	   

            task_level_4ms=LOCKED;
        }  	   

        if (task_level_6ms==OPEN)
        {  	 		   	   
            task_level_6ms=LOCKED;
        } 

        if (task_level_10ms == OPEN)
        {	      
          
            task_level_10ms = LOCKED;
        }

        if (task_level_20ms==OPEN)
        { 

            XGSWT  = 0x0808;//xgate ��������ж�3,���ڴ���PWM���¼�ģ�������
            
            CAN1_DistillMessage();            
            CAN3_DistillMessage();

            main_controller_life++;                               //������LIFE	

            task_level_20ms=LOCKED;
        }  

        if (task_level_40ms==OPEN)
        {	     
            FeedWatchDog();                    

            task_level_40ms=LOCKED;
        }

        if (task_level_50ms == OPEN)
        {
            Vcu_Get_MasterSlave_State();
            Vcu_Control_Main();
            Vcu_ACM_Management();  
  
                    	      	  
            task_level_50ms = LOCKED; 
        }  	   

        if (task_level_60ms==OPEN)
        {

            CAN3_transfer_load(VCU2, VCU_To_All);
            
            GPIODrv_GetValue();
            GPIODrv_SetValue();

            task_level_60ms=LOCKED;
        }

        if (task_level_100ms==OPEN)
        {


            task_level_100ms=LOCKED;

            PTJ_PTJ0 = ~PTJ_PTJ0;	

        }  

        if (task_level_120ms == OPEN)
        {
            if (MASTER_STATE == bySelfState)
            {
                CAN1_transfer_load(VCU_DCU_1,VCU_DCU_ID1);
                CAN1_transfer_load(VCU_DCU_2,VCU_DCU_ID2);
                CAN1_transfer_load(VCU_DCU_3,VCU_DCU_ID3);
                CAN1_transfer_load(VCU_DCU_4,VCU_DCU_ID4);  
                CAN1_transfer_load(VCU_DCU_5,VCU_DCU_ID5);
                CAN1_transfer_load(VCU_DCU_6,VCU_DCU_ID6);
                CAN1_transfer_load(VCU_DCU_7,VCU_DCU_ID7);
                CAN1_transfer_load(VCU_DCU_8,VCU_DCU_ID8);     
                
                CAN3_transfer_load(VCU_To_BMS1, VCU_To_BMS1_ID);
                CAN3_transfer_load(VCU_To_BMS2, VCU_To_BMS2_ID);     
            }

            task_level_120ms = LOCKED; 
        } 

        if (task_level_300ms == OPEN)
        {
            Vcu_TrainSpeed_Calc(); 
           
            if (MASTER_STATE == bySelfState)
            {
                Vcu_Brake_Management();
                Vcu_BMS_Management(); 
                Vcu_Propulsion_Management();

            }



            task_level_300ms = LOCKED; 
        } 	 

        if (task_level_400ms == OPEN)
        {

            if (port_init_en)
            {

                port_init_en=0;
            }

            can_test();
            can_test2();

            task_level_400ms = LOCKED;
        }

        if (task_level_1200ms == OPEN)
        {
            task_level_1200ms = LOCKED;
        } 
    } /* wait forever */
/* please make sure that you never leave this function */
}
