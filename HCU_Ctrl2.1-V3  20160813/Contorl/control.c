#include "control.h"


byte motorFlag = 0;

extern Byte abyVCU_CAN3_Recv_BMS1_Others[8];  //shenmin
extern Byte abyVCU_CAN3_Recv_BMS2_Others[8];  //shenmin
extern Byte abyVCU_CAN3_Recv_BMS1_MainInfo1[8];  //shenmin
extern Byte abyVCU_CAN3_Recv_BMS2_MainInfo1[8];  //shenmin
/************************************************************************
** �������ƣ�Vcu_Get_MasterSlave_State()                               **
** �������ܣ�Get the master/slave state of VCU                         **
** ��    �룺                                                          **
**                                                                     **
** ��    ����                                                          **
** ��    �ߣ�                                                          **
** ��    �ڣ�                                                          **
** �޸������---                                                       **
** ��    ע��                            **
************************************************************************/ 
void Vcu_Get_MasterSlave_State()
{
    bySelfStateTemp =  DI_Vale_TEXT[0];   //According to the definition of IO list
    
    if(MASTER_STATE == byOtherState)
    {
        bySelfState = SLAVE_STATE;
    }
    else
    {
        bySelfState = bySelfStateTemp;
    }
}

/************************************************************************
** �������ƣ�Vcu_BMS_Management()                               **
** �������ܣ�Manage the BMS                         **
** ��    �룺                                                          **
**                                                                     **
** ��    ����                                                          **
** ��    �ߣ�                                                          **
** ��    �ڣ�                                                          **
** �޸������---                                                       **
** ��    ע��                            **
************************************************************************/ 
void Vcu_BMS_Management()   
{
   Byte i;
   Byte byReq_HVBreak_FromBMS1;
   Byte byReq_HVBreak_FromBMS2;
   Byte byReady_BMS1;
   Byte byReady_BMS2;
   static Byte byReqBreakCount1 = 0;
   static Byte byReqBreakCount2 = 0;
   
   
   byReq_HVBreak_FromBMS1 = abyVCU_CAN3_Recv_BMS1_Others[0] & 0x03;
   byReq_HVBreak_FromBMS2 = abyVCU_CAN3_Recv_BMS2_Others[0] & 0x03;
   byReady_BMS1         = (abyVCU_CAN3_Recv_BMS1_MainInfo1[7]>>6) & 0x03;
   byReady_BMS2         = (abyVCU_CAN3_Recv_BMS2_MainInfo1[7]>>6) & 0x03;
   
    if(MASTER_STATE == bySelfState)
    {
        if(2 == byReady_BMS1)
        {
            byVCU_Ctrl_BMS1 = 0x0d;
        }
        
        if(2 == byReady_BMS2)
        {
            byVCU_Ctrl_BMS2 = 0x0d;
        }
        
        if(1 == byReq_HVBreak_FromBMS1)
        {
            byReqBreakCount1++;
            
            if (byReqBreakCount1 > 100)
            {
                byVCU_Ctrl_BMS1 = byVCU_Ctrl_BMS1 | 0xc0;
                for (i = 0; i < 10; i++)
                    DO_Vale_TEXT[i] = 0;    
                    
                byReqBreakCount1 = 0;    	
            }
            
  
            
        }
        else
        {
            byReqBreakCount1 = 0;				
        }
        
        if(1 == byReq_HVBreak_FromBMS2)
        {
            byReqBreakCount2++;
            
            if (byReqBreakCount2 > 100)
            {
                byVCU_Ctrl_BMS2 = byVCU_Ctrl_BMS2 | 0xc0;
                for (i = 0; i < 10; i++)
                    DO_Vale_TEXT[i] = 0; 	
                    
                byReqBreakCount2 = 0;
            }


        }
        else
        {
        		byReqBreakCount2 = 0;
        }
        
        if((byHighTemp_BMS1 == 0x02) || (byHighTemp_BMS1 == 0x03) ||
        	 (byLowTemp_BMS1  == 0x08) || (byLowTemp_BMS1  == 0x0c) ||
        	 (byOverDisCharge_BMS1 == 0x20) || (byOverDisCharge_BMS1 == 0x30) ||
        	 (byOverCharge_BMS1 == 0x80) || (byOverDisCharge_BMS1 == 0xc0) ||
        	 (byVoltConsist_BMS1 == 0x01) || (byVoltConsist_BMS1 == 0x02) ||
        	 (byCommFault_BMS1 == 0x08) || (byCommFault_BMS1 == 0x0c) ||
        	 (byInsStat_BMS1 == 0x20) || (byInsStat_BMS1 == 0x30) ||
        	 (byChgPlugin_BMS1 == 0x01) || (byChgPlugin_BMS1 == 0x04) || (byChgPlugin_BMS1 == 0x05)
        	)
        {
            byTractionBlk_BMS1 = 1;
        }
        else
        {
            byTractionBlk_BMS1 = 0;
        }
        
        if((byHighTemp_BMS2 == 0x02) || (byHighTemp_BMS2 == 0x03) ||
        	 (byLowTemp_BMS2  == 0x08) || (byLowTemp_BMS2  == 0x0c) ||
        	 (byOverDisCharge_BMS2 == 0x20) || (byOverDisCharge_BMS2 == 0x30) ||
        	 (byOverCharge_BMS2 == 0x80) || (byOverDisCharge_BMS2 == 0xc0) ||
        	 (byVoltConsist_BMS2 == 0x01) || (byVoltConsist_BMS2 == 0x02) ||
        	 (byCommFault_BMS2 == 0x08) || (byCommFault_BMS2 == 0x0c) ||
        	 (byInsStat_BMS2 == 0x20) || (byInsStat_BMS2 == 0x30) ||
        	 (byChgPlugin_BMS2 == 0x01) || (byChgPlugin_BMS2 == 0x04) || (byChgPlugin_BMS2 == 0x05)
        	)
        {
            byTractionBlk_BMS2 = 1;
        }
        else
        {
            byTractionBlk_BMS2 = 0;
        }
    }
}

/************************************************************************
** �������ƣ�Vcu_ACM_Management()                               **
** �������ܣ�Manage the ACM                         **
** ��    �룺                                                          **
**                                                                     **
** ��    ����                                                          **
** ��    �ߣ�                                                          **
** ��    �ڣ�                                                          **
** �޸������---                                                       **
** ��    ע��                            **
************************************************************************/ 
void Vcu_ACM_Management()
{
    if(MASTER_STATE == bySelfState)
    {
        if(byHVClsStat_BMS1 == 0x20)           //����������ѹOK
        {
            Vcu_Close_Contact();               //Ԥ��硢���Ӵ����պ�
            
            byDCDCComm_1 = START;               //����ACM
            byDCACComm_1 = START;
            byDCDCComm_3 = START;
            byDCACComm_3 = START;            
        }
        else                                   //����������ѹ��OK
        {
            Vcu_Open_Contact();                //Ԥ��硢���Ӵ����Ͽ�
            
            byDCDCComm_1 = STOP;               //ֹͣACM
            byDCACComm_1 = STOP;
            byDCDCComm_3 = STOP;
            byDCACComm_3 = STOP;
        }
        
        if(byHVClsStat_BMS2 == 0x20)
        {
            //Announce the other VCU to close contacts
            byContactCmd = 1;
            
            byDCDCComm_2 = START;               //����ACM
            byDCACComm_2 = START;
            byDCDCComm_4 = START;
            byDCACComm_4 = START;            
        }
        else
        {
            //Announce the other VCU to close contacts
            byContactCmd = 0;
            byDCDCComm_2 = STOP;               //ֹͣACM
            byDCACComm_2 = STOP;
            byDCDCComm_4 = STOP;
            byDCACComm_4 = STOP;
        }        
    }
    else   //SLAVE, execute the Contact command from the MASTER VCU via CAN
    {
        if(1 == byContactReq)
        {
            Vcu_Close_Contact();
        }
        else
        {
            Vcu_Open_Contact();
        }
    }
}

/************************************************************************
** �������ƣ�Vcu_Close_Contact()                               **
** �������ܣ�Close contacts                         **
** ��    �룺                                                          **
**                                                                     **
** ��    ����                                                          **
** ��    �ߣ�                                                          **
** ��    �ڣ�                                                          **
** �޸������---                                                       **
** ��    ע��                            **
************************************************************************/ 

void Vcu_Close_Contact()
{
    static byte count1 = 0;
    static byte count2 = 0;
    static byte count3 = 0;
    static byte count4 = 0;
    
    
    DO_Vale_TEXT[4] = 1;    //Auxiliary contactor 1 close
    DO_Vale_TEXT[9] = 1;    //Auxiliary contactor 2 close
    
    if(1 != DO_Vale_TEXT[1])   //Main contactor already closed, no need to close pre contacotr again
    {
        if(30 > byPreConClsLable1)  //Ԥ���Ӵ�����־λ�Ǵδ���10֮��㲻�ɼ����ۼӣ���������������±պ�Ԥ���Ӵ���
        {
            if(0 == byPreConClsLable1) //Ԥ���Ӵ�����־Ϊ0��ʾδ�պϣ���պϣ��ұ�־λ��ʼ�ۼӣ�ͨ��������ȱ�������ʱ
            {
                DO_Vale_TEXT[0] = 1;
                byPreConClsLable1 ++;
            }
            else
            {
                byPreConClsLable1 ++;
            }
        }
        if(30 <= byPreConClsLable1)  //Temp,�ݶ�Ԥ���Ӵ����պ�10��ѭ����ʱ��֮�󣬱պ����Ӵ���
        {
            DO_Vale_TEXT[1] = 1;
        }
    }    
    
    
    if(1 != DO_Vale_TEXT[3])   //Main contactor already closed, no need to close pre contacotr again
    {
        if(30 > byPreConClsLable2)  //Ԥ���Ӵ�����־λ�Ǵδ���10֮��㲻�ɼ����ۼӣ���������������±պ�Ԥ���Ӵ���
        {
            if(0 == byPreConClsLable2) //Ԥ���Ӵ�����־Ϊ0��ʾδ�պϣ���պϣ��ұ�־λ��ʼ�ۼӣ�ͨ��������ȱ�������ʱ
            {
                DO_Vale_TEXT[2] = 1;
                byPreConClsLable2 ++;
            }
            else
            {
                byPreConClsLable2 ++;
            }
        }
        if(30 <= byPreConClsLable2)  //Temp,�ݶ�Ԥ���Ӵ����պ�10��ѭ����ʱ��֮�󣬱պ����Ӵ���
        {
            DO_Vale_TEXT[3] = 1;
        }
    }
    
    if(1 != DO_Vale_TEXT[6])   //Main contactor already closed, no need to close pre contacotr again
    {
        if(30 > byPreConClsLable3)  //Ԥ���Ӵ�����־λ�Ǵδ���10֮��㲻�ɼ����ۼӣ���������������±պ�Ԥ���Ӵ���
        {
            if(0 == byPreConClsLable3) //Ԥ���Ӵ�����־Ϊ0��ʾδ�պϣ���պϣ��ұ�־λ��ʼ�ۼӣ�ͨ��������ȱ�������ʱ
            {
                DO_Vale_TEXT[5] = 1;
                byPreConClsLable3 ++;
            }
            else
            {
                byPreConClsLable3 ++;
            }
        }
        if(30 <= byPreConClsLable3)  //Temp,�ݶ�Ԥ���Ӵ����պ�10��ѭ����ʱ��֮�󣬱պ����Ӵ���
        {
            DO_Vale_TEXT[6] = 1;
        }
    }
    
    if(1 != DO_Vale_TEXT[8])   //Main contactor already closed, no need to close pre contacotr again
    {
        if(30 > byPreConClsLable4)  //Ԥ���Ӵ�����־λ�Ǵδ���10֮��㲻�ɼ����ۼӣ���������������±պ�Ԥ���Ӵ���
        {
            if(0 == byPreConClsLable4) //Ԥ���Ӵ�����־Ϊ0��ʾδ�պϣ���պϣ��ұ�־λ��ʼ�ۼӣ�ͨ��������ȱ�������ʱ
            {
                DO_Vale_TEXT[7] = 1;
                byPreConClsLable4 ++;
            }
            else
            {
                byPreConClsLable4 ++;
            }
        }
        if(30 <= byPreConClsLable4)  //Temp,�ݶ�Ԥ���Ӵ����պ�10��ѭ����ʱ��֮�󣬱պ����Ӵ���
        {
            DO_Vale_TEXT[8] = 1;
        }
    }
    
    DO_Vale_TEXT[10] = 1;    //Pump contactor 1 close
    DO_Vale_TEXT[11] = 1;    //Pump contactor 2 close
    
    if(DO_Vale_TEXT[1] == 1)   //If main contactor closed, open precharge contactor
    {
        if (count1++ >10) 
        {
            DO_Vale_TEXT[0] = 0;
            byPreConClsLable1 = 0;
            count1 = 0;
        }
 
    }
    
    if(DO_Vale_TEXT[3] == 1)
    {
        if (count2++ >10) 
        {
            DO_Vale_TEXT[2] = 0;
            byPreConClsLable2 = 0;
            count2 = 0;
        }  
       
     
    }
    
    if(DO_Vale_TEXT[6] == 1)
    {
        if (count3++ >10) 
        {
            DO_Vale_TEXT[5] = 0;
            byPreConClsLable3 = 0;
            count3 = 0;
        }
       
     
    }
    
    if(DO_Vale_TEXT[8] == 1)
    {
        if (count4++ >10) 
        {
            DO_Vale_TEXT[7] = 0;
            byPreConClsLable4 = 0;
            count4 = 0;
        }
       
       
    }
}




/************************************************************************
** �������ƣ�Vcu_Open_Contact()                               **
** �������ܣ�Open contact                         **
** ��    �룺                                                          **
**                                                                     **
** ��    ����                                                          **
** ��    �ߣ�                                                          **
** ��    �ڣ�                                                          **
** �޸������---                                                       **
** ��    ע��                            **
************************************************************************/ 
void Vcu_Open_Contact()
{
    Byte byLoop;
    
    for(byLoop = 0; byLoop < 12; byLoop ++)
    {
        DO_Vale_TEXT[byLoop] = 0;
    }
    byPreConClsLable1 = 0;
    byPreConClsLable2 = 0;
    byPreConClsLable3 = 0;
    byPreConClsLable4 = 0;
}

/************************************************************************
** �������ƣ�Vcu_Propulsion_Management()                               **
** �������ܣ�Manage the propulsion                         **
** ��    �룺                                                          **
**                                                                     **
** ��    ����                                                          **
** ��    �ߣ�                                                          **
** ��    �ڣ�                                                          **
** �޸������---                                                       **
** ��    ע��                            **
************************************************************************/ 
void Vcu_Propulsion_Management()
{
    Byte bLoop;
    static Word count = 0; 
 

    Vcu_TrRef_Calc();
    

    //Vcu_TrTorque_Calc();
    if((byForward == 1) && (byBackward == 0))
    {
        for (bLoop = 0; bLoop < 8; ) 
        {
            byDirection[bLoop] = 0x08;
            byDirection[bLoop+1] = 0x10;
            bLoop = bLoop + 2;
        }
    }
    else if((byForward == 0) && (byBackward == 1))
    {
        for (bLoop = 0; bLoop < 8; ) 
        {
            byDirection[bLoop] = 0x10;
            byDirection[bLoop+1] = 0x08;
            bLoop = bLoop + 2;
        }  
    }
    else
    {
        for (bLoop = 0; bLoop < 8; bLoop++) 
        {
            byDirection[bLoop] = 0;
        } 
    }
    
    Vcu_TrBlk_Chk();
    
    

    for(bLoop = 0; bLoop < 8; bLoop ++)
    {
        aiTargetTorque[bLoop] = (unsigned int)byTrEffRef * 16 + 32000;           //1600 is the maximun torque from one motor on normal mode at 120RPM
        aiDCVoltLmt[bLoop] = 17000;                                        //1600��Ҫ���ֳ�����
        aiDCCurLmt[bLoop] = 10800;
        if(byTrEffRef > 0)
        {
            abyMotorCtrl[bLoop] = 0x02 | byDirection[bLoop];
            byBreakComm = 0;
        }
        else
        {
            abyMotorCtrl[bLoop] = 0x00 | byDirection[bLoop];
        }
        
    }
    
    
   
}

/************************************************************************
** �������ƣ�Vcu_TrRef_Calc()                               **
** �������ܣ�Calculate the traction reference                         **
** ��    �룺                                                          **
**                                                                     **
** ��    ����                                                          **
** ��    �ߣ�                                                          **
** ��    �ڣ�                                                          **
** �޸������---                                                       **
** ��    ע��                            **
************************************************************************/ 
void Vcu_TrRef_Calc()
{    
    if(1 == byTractionEnable)
    {
        if((1 == DI_Vale_TEXT[11]) && (1 == DI_Vale_TEXT[10]) && (1 == DI_Vale_TEXT[9]) && (1 == DI_Vale_TEXT[8]))
        {
            byTrEffRef = 100;
            byTractionComm = 1;
        }
        else if((1 == DI_Vale_TEXT[10]) && (1 == DI_Vale_TEXT[9]) && (1 == DI_Vale_TEXT[8]))
        {
            byTrEffRef = 75;
            byTractionComm = 1;
        }
        else if((1 == DI_Vale_TEXT[9]) && (1 == DI_Vale_TEXT[8]))
        {
            byTrEffRef = 50;
            byTractionComm = 1;
        }
        else if(1 == DI_Vale_TEXT[8])
        {
            byTrEffRef = 25;
            byTractionComm = 1;
        }
        else
        {
            byTrEffRef = 0;
        }
    }
    else
    {
        byTrEffRef = 0;
    }
}

/************************************************************************
** �������ƣ�Vcu_TrBlk_Chk()                               **
** �������ܣ�Check the traction block                         **
** ��    �룺                                                          **
**                                                                     **
** ��    ����                                                          **
** ��    �ߣ�                                                          **
** ��    �ڣ�                                                          **
** �޸������---                                                       **
** ��    ע��                            **
************************************************************************/ 
void Vcu_TrBlk_Chk()
{   
    if ((byParking == 1) ||
    	 (byForward == byBackward) ||
    	 (byBrApplied == 1) ||
    	 (byBrEffRef > 0))
    {
        byTractionEnable = 0;
    }
    else
    {
        byTractionEnable = 1;
    }
  
  
    
}

/************************************************************************
** �������ƣ�Vcu_TrTorque_Calc()                               **
** �������ܣ�Calsulate the traction torque                         **
** ��    �룺                                                          **
**                                                                     **
** ��    ����                                                          **
** ��    �ߣ�                                                          **
** ��    �ڣ�                                                          **
** �޸������---                                                       **
** ��    ע��                            **
************************************************************************/ 
void Vcu_TrTorque_Calc()
{
    //Traction block checking
    
}

#if 0     //shenmin
/************************************************************************
** �������ƣ�Vcu_Suspension_Management()                               **
** �������ܣ�Manage the suspension system                              **
** ��    �룺                                                          **
**                                                                     **
** ��    ����                                                          **
** ��    �ߣ�                                                          **
** ��    �ڣ�                                                          **
** �޸������---                                                       **
** ��    ע��                            **
************************************************************************/ 
void Vcu_Suspension_Management()
{
    if(MASTER_STATE == bySelfState)
    {
        if(byBrakeTest == 1)
        {
            byCommand1 = 1;
            byCommand2 = byCommand2 | 0x01;
        }
        
        if((byCamera > 0) && (byCamera <= 4))
        {
            byCommand2 = byCommand2 | (1 << byCamera);
        }
        
        if(bySuspensionTest == 1)
        {
            byCommand1 = 0x81;
        }
        
        if((byBalanceTemp == 1) && (byBalance == 0))   //New trig
        {
            byBalance = byBalanceTemp;
            byCommand1 = 0x03;
            byBalanceLabel ++; 
        }
        else if(byBalance == 1)
        {
            if(byBalanceLabel <= 4)
            {
                byCommand1 = 0x03;
                byBalanceLabel ++;
            }
            else
            {
                byBalanceTemp = 0;
                byBalance = 0;
                byBalanceLabel = 0;
            }            
        }
        
        /*
        if(byEnergySaving == 1)  //These two modes will be exeuted by VCU5~8 themselves
        {
            byCommand1 = 0x11��
        }
        
        if(byMotorStart == 1)
        {
            byCommand1 = 0x41��
        }*/
        
        if(byParking == 0)
        {
            byCommand1 = 0x21;
        }
        /*
        if(byBreakComm == 1)      //Brake management is moved to a single function and be executed on a faster task
        {
            byCommand1 = 0x05��
        }*/
        
        if((byTractionComm == 1)  && (byParking != 0) && (byBreakComm != 1))
        {
            byCommand1 = 0x09;
        }
    }
}
#endif   //shenmin

/************************************************************************
** �������ƣ�Vcu_BrRef_Calc()                               **
** �������ܣ�Calculate the brake reference                         **
** ��    �룺                                                          **
**                                                                     **
** ��    ����                                                          **
** ��    �ߣ�                                                          **
** ��    �ڣ�                                                          **
** �޸������---                                                       **
** ��    ע��                            **
************************************************************************/ 
void Vcu_BrRef_Calc()
{
    if((1 == DI_Vale_TEXT[7]) && (1 == DI_Vale_TEXT[6]) && (1 == DI_Vale_TEXT[5]))
    {
        byBrEffRef = 100;
        byBreakComm = 1;
    }
    else if((1 == DI_Vale_TEXT[7]) && (1 == DI_Vale_TEXT[6]) && (0 == DI_Vale_TEXT[5]))
    {
        byBrEffRef = 86;
        byBreakComm = 1;
    }
    else if((1 == DI_Vale_TEXT[7]) && (0 == DI_Vale_TEXT[6]) && (1 == DI_Vale_TEXT[5]))
    {
        byBrEffRef = 71;
        byBreakComm = 1;
    }
    else if((1 == DI_Vale_TEXT[7]) && (0 == DI_Vale_TEXT[6]) && (0 == DI_Vale_TEXT[5]))
    {
        byBrEffRef = 57;
        byBreakComm = 1;
    }
    else if((0 == DI_Vale_TEXT[7]) && (1 == DI_Vale_TEXT[6]) && (1 == DI_Vale_TEXT[5]))
    {
        byBrEffRef = 43;
        byBreakComm = 1;
    }
    else if((0 == DI_Vale_TEXT[7]) && (1 == DI_Vale_TEXT[6]) && (0 == DI_Vale_TEXT[5]))
    {
        byBrEffRef = 29;
        byBreakComm = 1;
    }
    else if((0 == DI_Vale_TEXT[7]) && (0 == DI_Vale_TEXT[6]) && (1 == DI_Vale_TEXT[5]))
    {
        byBrEffRef = 14;
        byBreakComm = 1;
    }
    else 
    {
        byBrEffRef = 0;
    }
}

/************************************************************************
** �������ƣ�Vcu_Brake_Management()                               **
** �������ܣ�Manage the Brake system                              **
** ��    �룺                                                          **
**                                                                     **
** ��    ����                                                          **
** ��    �ߣ�                                                          **
** ��    �ڣ�                                                          **
** �޸������---                                                       **
** ��    ע��                            **
************************************************************************/ 
void Vcu_Brake_Management()
{
    
    Vcu_BrRef_Calc();
    
    if((byBreakComm == 1) && (byParking != 0))
    {
        byTractionComm = 0;
        byCommand1 = 0x05;
    }
}

/************************************************************************
** �������ƣ�Vcu_Control_Main()                                        **
** �������ܣ������Ƶ���ģ��                                            **
** ��    �룺                                                          **
**                                                                     **
** ��    ����                                                          **
** ��    �ߣ�                                                          **
** ��    �ڣ�                                                          **
** �޸������---                                                    **
** ��    ע���������ڵ��ø��ֿ��ƺ��������غ���                        **
************************************************************************/ 
void Vcu_Control_Main()   //���߼����к�����20ms���������У�ÿ�����ڽ������в�ͬ��ģ��
{
    bySelfStateTemp = DI_Vale_TEXT[0];   //According to the definition of IO list
    byForward       = DI_Vale_TEXT[1];
    byBackward      = DI_Vale_TEXT[2];
    byParking       = DI_Vale_TEXT[3];
    byBrApplied     = DI_Vale_TEXT[4];
    byDoor3State    = DI_Vale_TEXT[12];
    byDoor4State    = DI_Vale_TEXT[13];
    aiCurHeight[2]  = (int)AI_Vale_TEXT[9]; 
    aiCurHeight[3]  = (int)AI_Vale_TEXT[11]; 
}		
		
//��ȡ��������Ϣ  20ms���ڸ���
void GPIODrv_GetValue()  //��ȡ�ӿ���Ϣ
{
    Byte i;
    Byte DI_Vale_TEXT_Temp[20];
    
    for(i=0;i<20;i++) 
    {
        DI_Vale_TEXT_Temp[i] = Digital_Input(i+1,1);
        AI_Vale_TEXT[i] = Analog_Input(i+1);
    }

	
	for (i = 0; i < 7; i++)
	    DI_Vale_TEXT[i] = DI_Vale_TEXT_Temp[i];
	    
	DI_Vale_TEXT[7] = DI_Vale_TEXT_Temp[10];    
	DI_Vale_TEXT[8] = DI_Vale_TEXT_Temp[8]; 	    
  	DI_Vale_TEXT[9] = DI_Vale_TEXT_Temp[9]; 
	DI_Vale_TEXT[10] = DI_Vale_TEXT_Temp[11]; 
	DI_Vale_TEXT[11] = DI_Vale_TEXT_Temp[12];    
	DI_Vale_TEXT[12] = DI_Vale_TEXT_Temp[13]; 	    
  	DI_Vale_TEXT[13] = DI_Vale_TEXT_Temp[14];

}

//�������ӿ��������  20ms���ڸ���
void GPIODrv_SetValue() 
{
    Byte i;
    
    for (i=0; i<16; i++) 
    {
        Digital_Output(i+1,DO_Vale_TEXT[i]);
    }

}

