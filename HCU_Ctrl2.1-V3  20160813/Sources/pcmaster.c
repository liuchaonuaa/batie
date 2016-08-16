/*******************************************************************************
*
* Motorola Inc.
* (c) Copyright 2002 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name: pcmaster.c
*
* Description: Source file for PC master communication -
*              this file contains all the functions necessary for supporting
*              the PC master communication protocol
* Modules Included:
*              pcmasterInit()
*              pcmasterGetAppCmdSts()
*              pcmasterWriteAppCmdSts()
*              cmdGetInfo()
*              cmdGetInfoBrief()
*              sendBuffer()
*              sendResponse()
*              messageDecode()
*              readRecSample()
*              pcmasterRecorder()
*              messageData()
*              pcmasterRxTxIsr()
*              pcmasterDispatcher()
*
*******************************************************************************/

/******************************************************************************/
/* INCLUDE                                                                    */
/******************************************************************************/

#include "c_types.h"
#include "periph.h"
#include "appconfig.h"
#include "arch.h"
#include "mpc500.h"
#include "qsmcm.h"
#include "pcmaster.h"
#include "mios14.h"//wangwei add
/******************************************************************************/
/* LOCAL TYPES                                                                */
/******************************************************************************/
extern void  Flash_reprogram(void);
//extern void  Flash_prog_start(UWord32 Flash_Modify_Addr_temp,UWord8  Modify_Data_temp);
//extern void  Flash_Sector_Prog(UWord32 Flash_Modify_Addr_temp,UWord8  Modify_Data_temp);
extern void Flash_Sector_Prog();
extern void SCI_SectorData_Send();
extern void Main_Program(UWord8 selectFlag);
extern void Flash_prog_start(UWord8 selectFlag);
extern void SCI_ParaData_Send();
extern void GetFramData();
extern void GetClockData();
extern void InitClockTime();
extern void ReadClockTime();
/*********************************************************************************/
/* recorder settings structure (recorder settings and 
temporary variables are stored in this structure) */
typedef struct{
	unsigned char trgMode;      /* 0x00 - manual, 0x01 - rising edge, 
                                                   0x02 - falling edge */
	unsigned int  totalSmps;    /* number of samples required */
	unsigned int  postTrigger;  /* samples after trigger */
	unsigned int  timeDiv;      /* time div */
	unsigned char *trgVarAddr;  /* address of trigger variable */
	unsigned char trgVarSize;   /* size of variable (bytes) */
	unsigned char trgVarSigned; /* 0x00 - unsigned, 0x01 - signed */
	
	union{						
	/* union is used to access various types of treshold */
		UWord8   uch;
		UWord16  uw;
		Word8    ch;
		Word16	 w;
		UWord32  udw;
		Word32   dw;
	} trgTreshold;          /* trigger treshold */
	
	unsigned char varCnt;   /* number of variables */
	struct{
		UWord8 varSize;     /* size of variable */
		UWord8 *varAddr;    /* address of variable */
	} varDef[8];
	
	/* position in recorder buffer - position of the next samples 
	(incremented with RecSetLen) */
	UWord16 recPos;		
	/* length of required set of variables (in words) */
	UWord8 recSetLen;	
	/* position to end of buffer (the variable is decremented after trigger 
	and recorder stops at 0) */
	unsigned int recToEnd;
	/* time div of Recorder */
	unsigned int recTime;

	/* recorder last value (last value the triggering variable 
	is stored after launch of Recorder routine)  */
	union{
          Word8         ch;
          UWord8        uch;
          Word16        w;
          UWord16       uw;
          Word32        dw;
          UWord32       udw;
	} recLastVal;				/* last value of synchronizing variable */
	
} sRecorder;

/********************************************************/
/* PC master communication protocol commands data types */
/********************************************************/

/* scope settings buffer (scope settings are stored in this structure) */
typedef struct{
unsigned int	varCnt;
struct{
	UWord8 varSize;		/* size of scope variable */
	UWord32 *varAddr;	/* address of scope variable */
	} varDef[8];		/* maximum number of variables is 8 */
} sScope;

/* response structure type (this structure is used to save 
	the parameters of response to be sent to PC) */
typedef struct{
	UWord8 sts;		    /* status byte of response */
	UWord8 len;		    /* length of the whole response */
} sResponse;

/* read variable */
typedef struct{
	UWord8 cmd;
	UWord8 addrByte[4];  /* address of variable */
} sReadVarEx;

/* standard commands */
/* read memory */
typedef struct{
	UWord8 cmd;
	UWord8 cmdLen;
	UWord8 size;         /* size of data block in bytes */
	UWord8 addrByte[4];  /* address of data */
} sReadMemEx;

/* write memory */
typedef struct{
	UWord8 cmd;
	UWord8 cmdLen;
	UWord8 size;         /* size of data block in bytes */
	UWord8 addrByte[4];  /* address of data */
	UWord8 data[1];      /* data */
} sWriteMemEx;

/* setup scope */
typedef struct{
	UWord8 cmd;
	UWord8 cmdLen;
	UWord8 varCnt;        /* number of variables */
	struct{
		UWord8 varSize;   /* size of variable in bytes */
		UWord8 varAddrByte[4]; /* address of variable */
	} varDef[8];
} sSetupScopeEx;

/* setup recorder */
typedef struct{
	UWord8 cmd;
	UWord8 cmdLen;
	UWord8 trgMode;
	UWord8 totalSmps;   /* UWord16 totalSmps; */
	UWord8 dummy1;
    UWord8 postTrigger; /* UWord16 postTrigger; */
    UWord8 dummy2;
	UWord8 timeDiv;     /* UWord16 timeDiv; */
	UWord8 dummy3;
	UWord8 trgVarAddrByte[4];   /*unsigned char *trgVarAddr;*/
	UWord8 trgVarSize;
	UWord8 trgVarSigned;
	
    UWord8 trgTreshold; /* trgVarSize == 1 */
    UWord8 dummy4;      /* trgVarSize == 2 */
    UWord8 dummy5;
    UWord8 dummy6;      /* trgVarSize == 4 */

	UWord8 varCnt;        /* number of variables */
	struct{
		UWord8 varSize;   /* size of variable in bytes */
		/*unsigned char *varAddr;*/           /* address of variable */
		UWord8 varAddrByte[4];
	} varDef[8];
} sSetupRecEx;

/* call user application command */
typedef struct{
	unsigned char cmd;
	unsigned char cmdLen;
	unsigned char appCmdData[1]; /* application command data */
} sCallAppCmd;

/* return any data */
typedef struct{
    char reserved;               /* status code */
    unsigned char data[1];                /* data to PC */
} sReturnData;    

/********************************************************/
/*                    CONSTANTS                         */
/********************************************************/

/* call user application command status */
/* no application command called (board after reset) */
#define PCMASTER_APPCMD_NOCMD	   (unsigned char)0xFF	
/* application command not finished */
#define PCMASTER_APPCMD_RUNNING    (unsigned char)0xFE	

/* status byte masks (used with 'status' variable) */
/* receiving started, beginning of message already detected ('+') */
#define ST_STARTED                 0x0010		
/* last received char was '+' */
#define ST_ST_CHAR_REC             0x0020		
/* received message is standard command (for length decoding) */
#define ST_STD_CMD                 0x0040		
/* recorder is running (trigger already detected) */
#define ST_RECRUNNING              0x0100		
/* recorder is activated (waiting for trigger) */
#define ST_RECACTIVATED            0x0200		
/* read pretrigger samples before waiting for trigger */
#define ST_REC_READ_PRETRIG	       0x0080		
/* response is being send to PC */
#define ST_SENDING                 0x1000		
/* last sent char was '+' */
#define ST_ST_SENT                 0x2000		
/* checksum already added to the message */
#define ST_CS_ADDED                0x4000		

#define START 	'+'                 /* start of message */
#define CMD_GET_FRAMDATA 0XCF
#define CMD_GET_CLOCKDATA 0XCC
#define CMD_GET_VARIABLE 0XCE
#define CMD_PROGRAM_RENEW 0XC7
#define CMD_CHANGEVAR 0XC8
#define CMD_COMMUNICATION_TEST 0XCD
#define RS232COM_STS_OK 0X00
#define RS232COM_STC_CMDFAILED 0X86
#define RS232COM_STC_INVCMD 0X81
#define RS232COM_STC_CMDCSERR 0X82
#define CMD_CHANGE_CLOCK 0xCA
#define CMD_READ_CLOCK_TIME	0xCB

/******************************************************************************/
/*                       STATIC VARIABLES                                     */
/******************************************************************************/

/* input/output communication buffer */
static unsigned char dataBuff[PCMASTER_BUFFER_SIZE + 1];  

#ifdef PCMASTER_INCLUDE_CMD_SCOPE
  /* scope config data */
  static sScope scope;		
#endif

#ifdef PCMASTER_INCLUDE_CMD_RECORDER
  /* recorder config and temp data */
  static sRecorder recorder;	
  /* recorder buffer */
  static UWord8 recorderBuff[PCMASTER_REC_BUFF_LEN];
#endif

#ifdef PCMASTER_INCLUDE_CMD_APPCMD
  /* application command call status */
  static volatile unsigned char appCmdSts;
  /* application command data buffer */
  extern unsigned char appCmdBuff[PCMASTER_APPCMD_BUFF_LEN];
#endif

static volatile UWord16 status;        /* status word of receiver */
static volatile UWord8  status2;       /* 2nd status word of receiver */

/* currently read input char (it contains checksum at the end of message) */
static unsigned char inChar;		
/* position in buffer (0,1,2,...) */
static unsigned char pos;		
/* length of data in a message used for receiving and transmitting 
                                   (exclude SOB, include checksum) */
static unsigned char length;		

/* variable for checksum accumulation */
static char checkSum;					

static sResponse response;		/* variable with response data */
static UWord16 recPretrigCount; /* recorder pretrigger counter */

/******************************************************************************/
/*                          MACROS                                            */
/******************************************************************************/

/* save data for response to PC */
#define respPrepare(stat, leng)	{response.sts = stat;	\
								 response.len = leng;}	

/******************************************************************************/
/*        STATIC FUNCTION DECLARATION - LOCAL FUNCTION DECLARATION            */
/******************************************************************************/

/* send one byte from output buffer */
static void sendBuffer(void);					

/* prepare data for transmitting 
(response.status -> status code, response.len -> length of data) */
static void sendResponse(sResponse *resp);

/* sample recorder data */
/* decoding of incoming message after the last byte was received */
static void messageDecode(void);

/* routine callled after filtering doubled SOM */
static void messageData(unsigned int startOfMessage);

/* recorder routine which samples the data into the internal buffer */
static UWord16 readRecSample(UWord16 position);

/* main function which receives, processes data and executes commands */
static void pcmasterRxTxIsr(void);

/******************************************************************************/
/*                          FUNCTION DEFINITIONS                              */
/******************************************************************************/

#define POINT_LEN       4
#define WORD8_LEN       1
#define WORD16_LEN      2
#define WORD32_LEN      4

static UWord16 memCopy(register volatile unsigned char * srcAddr, 
    register volatile unsigned char * destAddr, register volatile unsigned char size);

static UWord16 memCopy(register volatile unsigned char * srcAddr, 
    register volatile unsigned char * destAddr, register volatile unsigned char size)
{
    while (size > 0)
    {
        *destAddr++ = *srcAddr++;
        size--;
    }
    return(0);
}

/*******************************************************************************
*
* Module: int pcmasterInit(void)
*
* Description:
*       PC master communication initialization function which must be called
*       before start of communication. It resets the internal variables and
*       get everything ready for the communication
*
* Global Data:
*       status - status variable of the PC master receiver and transmitter
*       scope.varCnt - scope status variable (when set to zero scope is reset)
*       recorder.varCnt - recorder status variable 
*                         (when set to zero scope is reset)
*       appCmdSts - application command status variable
*
* Returns: unconditionally returns 0 (for future compatibility)
*
* Arguments: none
*
* Range Issues: none
*
* Special Issues: none
*
*******************************************************************************/

Word16 pcmasterInit(void)
{
	status = 0;                   /* reset receiver */
	status2 = 0;                  /* reset receiver */	

	#ifdef PCMASTER_INCLUDE_CMD_SCOPE
	  scope.varCnt = 0;           /* reset scope */
	#endif

	#ifdef PCMASTER_INCLUDE_CMD_RECORDER
	  recorder.varCnt = 0;        /* reset recorder */
	#endif
	
	#ifdef PCMASTER_INCLUDE_CMD_APPCMD
	  /* initialize application command status */
	  appCmdSts = PCMASTER_APPCMD_NOCMD; 
	#endif
	
	return(0);
}

/*******************************************************************************
*
* Module: unsigned char pcmasterGetAppCmdSts(void)
*
* Description:
*       Get Application Command Status - This function is used to check 
*       if an application command has been received from PC
*
* Global Data:
*       appCmdSts - application command status variable
*
* Returns: 0 if a new application command is received
*          1 otherwise
*
* Arguments: none
*
* Range Issues: none
*
* Special Issues: none
*
*******************************************************************************/

#ifdef PCMASTER_INCLUDE_CMD_APPCMD
unsigned char pcmasterGetAppCmdSts(void)
/* return state of application command call */
{
	if (appCmdSts == PCMASTER_APPCMD_RUNNING)
    {
		return(1);		/* new application command received */
	}
	else
	{
		return(0);		/* no new application command */
	}
}
#endif

/*******************************************************************************
*
* Module: char pcmasterWriteAppCmdSts(unsigned char state)
*
* Description:
*       Write Application Command Status - This function clears the flags in 
*       application command status word and it says to PC that the last 
*       application command was served and new application command from PC 
*       will be accepted
*
* Global Data:
*       appCmdSts - application command status variable
*
* Returns: unconditionally returns 0
*
* Arguments:
*       state - application command return code
*
* Range Issues: none
*
* Special Issues: none
*
*******************************************************************************/

#ifdef PCMASTER_INCLUDE_CMD_APPCMD
char pcmasterWriteAppCmdSts(unsigned char state)
{
	appCmdSts = state;
	return(0);			/* OK */
}
#endif

/*******************************************************************************
*
* Module: static void cmdGetInfo(void)
*
* Description:
*       Get information about hardware (initialization sequence before any 
*       other communication) data are transfered into the communication buffer
*
* Global Data:
*       dataBuff - PC master communication i/o buffer
*
* Returns: none
*
* Arguments: none
*
* Range Issues: none
*
* Special Issues: none
*
*******************************************************************************/


inline static void cmdGetInfo(void)
{
	UWord16 i;				/* temporary variable for string copy */
	
    /* protocol version	*/
    ((sReturnData *)dataBuff)->data[0] = PCMASTER_PROT_VER;
    /* CFG_FLAFGS */
    ((sReturnData *)dataBuff)->data[1] = PCMASTER_CFG_FLAFGS;
    /* dataBusWdt */
    ((sReturnData *)dataBuff)->data[2] = PCMASTER_DATABUSWDT;
    /* version */
    ((sReturnData *)dataBuff)->data[3] = PCMASTER_GLOB_VERSION_MAJOR;
    /* version */
    ((sReturnData *)dataBuff)->data[4] = PCMASTER_GLOB_VERSION_MINOR;
    /* size of input buffer (without CMD, LENGTH) */
    ((sReturnData *)dataBuff)->data[5] = PCMASTER_BUFFER_SIZE - 1;
    /* size of recorder buffer */
    i = PCMASTER_REC_BUFF_LEN;
    memCopy((UWord8 *)&i, &((sReturnData *)dataBuff)->data[6], WORD16_LEN);
               
    /* period of Recorder routine launch */
    i = PCMASTER_RECORDER_TIME_BASE;
    memCopy((UWord8 *)&i, &((sReturnData *)dataBuff)->data[8], WORD16_LEN);

    for (i=0 ; i < PCMASTER_IDT_STRING_LEN ; i++)
    {
         ((sReturnData *)dataBuff)->data[10+i] = (UWord8)PCMASTER_IDT_STRING[i];
    }
}

/*******************************************************************************
*
* Module: static void cmdGetInfoBrief(void)
*
* Description:
*       Get brief information about hardware (initialization sequence before any
*       other communication) data are transfered into the communication buffer
   
* Global Data:
*       dataBuff - PC master communication i/o buffer
*
* Returns: none
*
* Arguments: none
*
* Range Issues: none
*
* Special Issues: none
*
*******************************************************************************/

inline static void cmdGetInfoBrief(void)
{
     /* protocol version	*/
	((sReturnData *)dataBuff)->data[0] = PCMASTER_PROT_VER;
	/* CFG_FLAFGS */
	((sReturnData *)dataBuff)->data[1] = PCMASTER_CFG_FLAFGS;
	/* dataBusWdt */
	((sReturnData *)dataBuff)->data[2] = PCMASTER_DATABUSWDT;
	/* version */
	((sReturnData *)dataBuff)->data[3] = PCMASTER_GLOB_VERSION_MAJOR;
	/* version */
	((sReturnData *)dataBuff)->data[4] = PCMASTER_GLOB_VERSION_MINOR;
	
	/* size of input buffer	(without CMD, LENGTH) */
	((sReturnData *)dataBuff)->data[5] = PCMASTER_BUFFER_SIZE - 1;	
}

/*******************************************************************************
*
* Module: static void sendBuffer(void)
*
* Description:
*       sends SOB character, data of message and checksum on the line
*     
* Global Data:
*       pos      - position in buffer (0,1,2,...)
*       length   - length of data in a message used for receiving 
*                  and transmitting (exclude SOB, include checksum)
*       checkSum - variable for checksum accumulation
*       status   - status word of receiver
*       inChar   - currently read input char 
*                  (it contains checksum at the end of message)
*       dataBuff - PC master communication i/o buffer
*
* Returns: none
*
* Arguments: none
*
* Range Issues: none
*
* Special Issues: none
*
*******************************************************************************/

inline static void sendBuffer(void)
{
	if (pos <= length)						/* is it end of message ? */
	{
 
        ioctl(PCMASTER_COMM_MODULE, SCI_WRITE_DATA, dataBuff[pos]);  /* write data */    
    			
		if (dataBuff[pos] != '+') 		/* current character is not '+' */
		{
			checkSum += dataBuff[pos];	/* accumulate checksum */
			pos++;
		}
		else      /* current character is '+' */
		{
			if (status & ST_ST_SENT)		/* the last sent char was '+' */
			{
				periphBitClear(ST_ST_SENT, &status);
				checkSum += dataBuff[pos];	/* accumulate checksum */
				pos++;
			}
			else      /* the last sent byte was not '+' */
			{
				periphBitSet(ST_ST_SENT, &status);	
			}
		}
		
		/* the last byte before cs was sent, now add the checksum */
		if ((pos == length) && !(status & ST_CS_ADDED))
		{
			checkSum = (Word8)((-checkSum) & 0x00FF);	/* compute checksum */
			dataBuff[pos] = (UWord8)checkSum;
			periphBitSet(ST_CS_ADDED, &status);			/* set flag */
		}
	}
	else		/* end of transmitting */
	{
        ioctl(PCMASTER_COMM_MODULE, SCI_TX_EMPTY_INT, SCI_DISABLE); /* enable tx int */
        ioctl(PCMASTER_COMM_MODULE, SCI_RX_INT, SCI_ENABLE); /* enable tx int */
	
	     /* reset transmitter (switch to receiving mode) */
		periphBitClear(ST_SENDING | ST_CS_ADDED, &status);
	}
}

/*******************************************************************************
*
* Module: static void sendResponse(sResponse *resp)
*
* Description:
*       Puts return code into the PC master communication i/o buffer, 
*       transmit SOB
*     
* Global Data:
*       pos      - position in buffer (0,1,2,...)
*       length   - length of data in a message used for receiving 
*                  and transmitting (exclude SOB, include checksum)
*       checkSum - variable for checksum accumulation
*       status   - status word of receiver
*       inChar   - currently read input char 
*                  (it contains checksum at the end of message)
*       dataBuff - PC master communication i/o buffer
*
* Returns: none
*
* Arguments: structure with return code and length of the response
*
* Range Issues: none
*
* Special Issues: none
*
*******************************************************************************/

static void sendResponse(sResponse *resp) 
{
	periphBitSet(ST_SENDING, &status);      /* set flag */
	dataBuff[0] = resp->sts;                /* status of trasmitted message */
	length = resp->len;                     /* length of message */
	pos = 0;                                /* position in the message */
	
	/* send start of message */
    ioctl(PCMASTER_COMM_MODULE, SCI_WRITE_DATA, '+');  /* write SOB character */
    /* enable Tx Empty Interrupt */
    ioctl(PCMASTER_COMM_MODULE, SCI_TX_EMPTY_INT, SCI_ENABLE);

	checkSum = 0;                           /* reset checksum */
}

/*******************************************************************************
*
* Module: static void messageDecode(void)
*
* Description:
*       3rd layer of the protocol decoding. Decodes the received message, 
*       execute the related command and prepares a response to PC
*     
* Global Data:
*       length   - length of data in a message used for receiving 
*                  and transmitting (exclude SOB, include checksum)
*       checkSum - variable for checksum accumulation
*       status   - status word of receiver
*       dataBuff - PC master communication i/o buffer
*       scope    - structure with all the scope settings
*       recorder - structure with the settings and temporary 
*                  variables of recorder
*
* Returns: none
*
* Arguments: none
*
* Range Issues: none
*
* Special Issues: none
*
*******************************************************************************/

inline static void messageDecode(void)
{
     volatile UWord8 *varaddr;
     unsigned char i;
     int j;

     switch(dataBuff[0])
	{
		/* -------------------------
		    special format commands
		   ------------------------- */
		case CMD_COMMUNICATION_TEST://测试通讯是否正常
		{
			respPrepare(RS232COM_STS_OK, 1);
		}break;
		case CMD_GET_VARIABLE:		//获取参数指令
		{
			respPrepare(RS232COM_STS_OK, 1);
//			Main_Program(0x03);
		}break;
		case CMD_CHANGEVAR:			//修改参数指令
		{
			respPrepare(RS232COM_STS_OK, 1);	
//			Main_Program(0x04);
		}break;
		case CMD_PROGRAM_RENEW:		//程序下载指令
		{
			respPrepare(RS232COM_STS_OK, 1);	
			ioctl(MIOS_PIO,PIO_SET_PIN,PIO_BIT_ALL);
			archDisableInt();
			Flash_prog_start(0x05);
//			Main_Program(0x05);
		}break;
		case CMD_GET_FRAMDATA:		//获得铁电数据指令
		{
		//	respPrepare(RS232COM_STS_OK, 1);	
		    GetFramData();
		//	Main_Program(0x03);
		}break;
		case CMD_GET_CLOCKDATA:	//获得实时时钟数据指令
		{
		//	respPrepare(RS232COM_STS_OK, 1);
			GetClockData();
		}break;
		case CMD_CHANGE_CLOCK://修改实时时钟
		{
	       InitClockTime();
	       break;
		}
		case CMD_READ_CLOCK_TIME://读下位机时间数据上传到上位机
		{  
		                         //added by G.A.N
			ReadClockTime();
        	break;
		}
		case PCMASTER_CMD_READVAR8EX:               /* read 8-bit variable */
		{
               memCopy(((sReadVarEx *)dataBuff)->addrByte, 
                        (UWord8*)&varaddr, POINT_LEN);
               *(((sReturnData *)dataBuff)->data) = *varaddr;  /* read 8-bit */
               
               respPrepare(PCMASTER_STC_OK, 2);     /* OK */
		}break;
		case PCMASTER_CMD_READVAR16EX:              /* read 16-bit variable */
		{
               memCopy(((sReadVarEx *)dataBuff)->addrByte, 
                        (UWord8*)&varaddr, POINT_LEN);
               *(UWord16*)(((sReturnData *)dataBuff)->data) = 
                                *(UWord16*)varaddr; /* read 16-bit */
               
               respPrepare(PCMASTER_STC_OK, 3);     /* OK */
		}break;
		case PCMASTER_CMD_READVAR32EX:              /* read 32-bit variable */
		{
               memCopy(((sReadVarEx *)dataBuff)->addrByte, 
                        (UWord8*)&varaddr, POINT_LEN);
               *(UWord32*)(((sReturnData *)dataBuff)->data) = 
                                *(UWord32*)varaddr;  /* read 32-bit */

               respPrepare(PCMASTER_STC_OK, 5);   /* OK */
		}break;
		#ifdef PCMASTER_INCLUDE_CMD_SCOPE
		case PCMASTER_CMD_READSCOPE:              /* read scope variables */
		{
		     unsigned char offset;
		
			/* scope not configured */
			if (scope.varCnt==0)			
			{
			     /* scope not initialized */
				respPrepare(PCMASTER_STC_NOTINIT,1);
			}		
			else      /* scope already configured */
			{
			    offset = 0; /* reset offset value */
			    
				/* execute command */
				for (i=0 ; i<scope.varCnt ; i++)    /* read each variable */
				{
				    /* read each byte of variable */
                    memCopy((UWord8*)(scope.varDef[i].varAddr), (UWord8*)
                       &(((sReturnData *)dataBuff)->data[offset]), 
                       scope.varDef[i].varSize);
                    offset += scope.varDef[i].varSize;
				}
				respPrepare(PCMASTER_STC_OK, (UWord8)(offset + 1));	/* OK */
			}
		}break;
		#endif
        #ifdef PCMASTER_INCLUDE_CMD_RECORDER
		case PCMASTER_CMD_GETRECSTS:    /* get recorder status */
		{
			if (recorder.varCnt)		/* recorder is initialized */
			{
				if (!(status & ST_RECACTIVATED))
				{
				     /* recorder finished */
					respPrepare(PCMASTER_STC_RECDONE, 1);	
				}
				else
				{
				     /* recorder running */
					respPrepare(PCMASTER_STC_RECRUN, 1);
				}
			}
			else						/* recorder is not initialized */
			{
			     /* recorder not initialized */
				respPrepare(PCMASTER_STC_NOTINIT, 1);
			}
		}break;
		case PCMASTER_CMD_STARTREC:		/* start recorder */
		{
			if (recorder.varCnt)		/* recorder initialized */
			{
				if (!(status & ST_RECRUNNING))    /* recorder not running */
				{
				     /* stop recorder if it is running */
					periphBitClear(ST_RECRUNNING, &status);
					/* initialize time div */
					recorder.recTime = (recorder.timeDiv);	
                    /* load actual value of trigger variable */ 
                    recorder.recLastVal.udw  = *(UWord32 *)(recorder.trgVarAddr);
                    
					/* activate recorder to wait for trigger */
					periphBitSet(ST_RECACTIVATED, &status);	
					respPrepare(PCMASTER_STC_OK, 1);	/* OK */
				}
				else
				{
				     /* recorder running */
					respPrepare(PCMASTER_STC_RECRUN, 1);
				}
			}
			else      /* recorder is not initialized */
			{
			     /* recorder not initialized */
				respPrepare(PCMASTER_STC_NOTINIT, 1);	
			}
		}break;
		case PCMASTER_CMD_STOPREC:              /* stop recorder */
		{
			if (recorder.varCnt)                /* recorder initialized */
			{
				if (status & ST_RECACTIVATED)   /* recorder activated */
				{	
					if (status & ST_RECRUNNING) /* recorder running */
					{
					     /* recorder finished */
						respPrepare(PCMASTER_STC_RECDONE, 1);	
					}
					else           /* recorder not running */
					{	
						/* initialize posttrigger value */
						recorder.recToEnd = recorder.postTrigger;	
						/* manually trigger the recorder */
						periphBitSet(ST_RECRUNNING,&status);
						respPrepare(PCMASTER_STC_OK, 1);	/* OK */
					}
				}
				else                            /* recorder not activated */
				{
				    /* recorder finished */
					respPrepare(PCMASTER_STC_RECDONE, 1);
				}
			}						
			else    /* recorder not initialized */
			{
				respPrepare(PCMASTER_STC_NOTINIT, 1);
			}
		}break;				
		case PCMASTER_CMD_GETRECBUFFEX:         /* get recorder buffer */
		{
		    UWord16 temp;
		    volatile UWord32 tmpAddr32;
		
			if ((recorder.varCnt) != 0)         /* recorder initialized */
			{
				if (!(status & ST_RECRUNNING))  /* recorder not running */
				{
					/* recorder buffer address */
                    tmpAddr32 = (UWord32)recorderBuff;
                    memCopy((UWord8 *)&tmpAddr32, ((sReturnData *)dataBuff)->data, POINT_LEN);
                   					
					/* recorder buffer address   !!! division !!!! */
					temp = (UWord16)((recorder.recPos) / (recorder.recSetLen)); 
					
					/* position of the last sample in recorder buffer */
                    memCopy((UWord8 *)&temp, &(((sReturnData *)dataBuff)->data[4]), WORD16_LEN);
					
					respPrepare(PCMASTER_STC_OK, 7);    /* OK */
				}
				else      /* recorder running */
				{
				     /* service busy */
					respPrepare(PCMASTER_STC_SERVBUSY, 1);
				}
			} else        /* recorder initialized */
			{
			     /* recorder not initialized */
				respPrepare(PCMASTER_STC_NOTINIT, 1);
			}
		}break;
        #endif
        #ifdef PCMASTER_INCLUDE_CMD_APPCMD
		/* get user application	command call status */
		case PCMASTER_CMD_GETAPPCMDSTS:
		{
			(((sReturnData *)dataBuff)->data[0]) = appCmdSts;
			respPrepare(PCMASTER_STC_OK,2);     /* OK */
		}break;
		#endif
		#ifndef PCMASTER_INCLUDE_CMD_GETINFO_BRIEF
		case PCMASTER_CMD_GETINFO:              /* get info about hardware */
		{
			cmdGetInfo();  /* execute the command */
			/* OK */
			respPrepare(PCMASTER_STC_OK,(1 + 10 + PCMASTER_IDT_STRING_LEN));
		}break;
		#endif
		#ifdef PCMASTER_INCLUDE_CMD_GETINFO_BRIEF
		case PCMASTER_CMD_GETINFOBRIEF:    /* get brief info about hardware */
		{
		     /* execute the command */
			cmdGetInfoBrief();
			respPrepare(PCMASTER_STC_OK,(1 + 6)); /* OK */
		}break;
		#endif		

		/* --------------------------
		    standard format commands
		   -------------------------- */
		#ifdef PCMASTER_INCLUDE_CMD_SCOPE
		case PCMASTER_CMD_SETUPSCOPEEX:     /* setup scope */
		{
		    char varSizeSum;
		
			if ( ((((sSetupScopeEx *)dataBuff)->varCnt) ==0) || \
			        ((((sSetupScopeEx *)dataBuff)->varCnt) > 8) )	
			/* varCnt is zero or greater than 8 */
			{
			     /* invalid buffer size */
				respPrepare(PCMASTER_STC_INVBUFF,1);
				return;
			}
		
			/* init sumarization */
			varSizeSum = 0;
			
			/* init scope */
			for( i=0 ; i<((sSetupScopeEx *)dataBuff)->varCnt ; i++)
			{
		        /* init variable size */
		        scope.varDef[i].varSize =
		                    (((sSetupScopeEx *)dataBuff)->varDef[i].varSize);
		        /* sum size in bytes of all variables */
		        varSizeSum += scope.varDef[i].varSize;      
		        /* init variable address */

                memCopy(((sSetupScopeEx *)dataBuff)->varDef[i].varAddrByte,
                    (UWord8 *)&(scope.varDef[i].varAddr), POINT_LEN);

				/* supported variable sizes are 1, 2, 4... */
				if ( ((scope.varDef[i].varSize) == 0) || 
				     ((scope.varDef[i].varSize) == 3) || 
				     ((scope.varDef[i].varSize) > 4) )
				{
					/* invalid size of variable */
					respPrepare(PCMASTER_STC_INVSIZE,1);	
                         scope.varCnt = 0;    /* reset scope */
					return;
				}
			}

            /* check if the data will fit into the i/o buffer */
            if (varSizeSum > PCMASTER_BUFFER_SIZE)
            {
                respPrepare(PCMASTER_STC_RSPBUFFOVF,1);
                scope.varCnt = 0;    /* reset scope */
                return;
            }

			scope.varCnt = (((sSetupScopeEx *)dataBuff)->varCnt);
			respPrepare(PCMASTER_STC_OK,1);
		}break;
		#endif
        #ifdef PCMASTER_INCLUDE_CMD_RECORDER
		case PCMASTER_CMD_SETUPRECEX:   /* setup recorder */
		{
		
		     /* reset the recorder */
			periphBitClear(ST_RECRUNNING | ST_RECACTIVATED, &status);

            if ( ((((sSetupRecEx *)dataBuff)->varCnt) == 0) || 
                 ((((sSetupRecEx *)dataBuff)->varCnt) > 8) )	
			/* varCnt is zero or greater than 8 */
			{
			     /* invalid buffer size */
				respPrepare(PCMASTER_STC_INVBUFF, 1);
				return;
			}

			/* init recorder */
            recorder.trgMode        = 
                (((sSetupRecEx *)dataBuff)->trgMode);
            recorder.totalSmps      = 
                *(UWord16*)&(((sSetupRecEx *)dataBuff)->totalSmps);
            recorder.postTrigger    = 
                *(UWord16*)&(((sSetupRecEx *)dataBuff)->postTrigger);
            recorder.timeDiv        = 
                *(UWord16*)&(((sSetupRecEx *)dataBuff)->timeDiv);
            memCopy((((sSetupRecEx *)dataBuff)->trgVarAddrByte), 
                    (UWord8*)&(recorder.trgVarAddr), POINT_LEN);
            recorder.trgVarSize     = (((sSetupRecEx *)dataBuff)->trgVarSize);
            recorder.trgVarSigned   = (((sSetupRecEx *)dataBuff)->trgVarSigned);
            memCopy(&(((sSetupRecEx *)dataBuff)->trgTreshold), 
                    (UWord8*)&(recorder.trgTreshold.dw), POINT_LEN);
            
			recorder.varCnt = 0;    /* reset recorder */
			/* size of one set of recorder samples (in bytes) */
			recorder.recSetLen = 0;
			
			/* init recorder */
			for( i=0 ; i<((sSetupRecEx *)dataBuff)->varCnt ; i++)
			{
		        /* init variable size */
		        recorder.varDef[i].varSize = 
		            (((sSetupRecEx *)dataBuff)->varDef[i].varSize);
		        /* init variable addresses */
                memCopy(((sSetupRecEx *)dataBuff)->varDef[i].varAddrByte, 
                        (UWord8*)&(recorder.varDef[i].varAddr), POINT_LEN);

				/* supported variable sizes are 1, 2, 4 */
				if ( !(((recorder.varDef[i].varSize)==1) || 
				       ((recorder.varDef[i].varSize)==2) || 
				       ((recorder.varDef[i].varSize)==4)) )
				{
					/* invalid size of variable */
					respPrepare(PCMASTER_STC_INVSIZE,1);	
                    recorder.varCnt = 0;    /* reset recorder */
					return;
				}
				
				/* length of one set of samples (in bytes) */
				recorder.recSetLen += recorder.varDef[i].varSize;
			}
			
			/* buffer length required (in bytes) */
			recorder.totalSmps = recorder.totalSmps * recorder.recSetLen;	
			

			/* store number of variables */
			recorder.varCnt = (((sSetupRecEx *)dataBuff)->varCnt);
									
			/* in case of PCMASTER_REC_TRIGRIS, PCMASTER_REC_TRIGFAL */
			if (recorder.trgMode) 
			{
				if (!( ((recorder.trgVarSize) == 1) || 
				       ((recorder.trgVarSize) == 2) ||
				       ((recorder.trgVarSize) == 4))  )		
				/* trigger variable size is not 1, 2 or 4 */
				{
				     /* invalid buffer size */
					respPrepare(PCMASTER_STC_INVSIZE, 1);
					(recorder.varCnt) = 0;        /* reset recorder */
					return;
				}
				/* encode recorder trigger configuration to 
				                                   the status variable */
				status = (UWord16)((status & 0xFFF0) | (((recorder.trgVarSize) << 1) \
				                            + (recorder.trgVarSigned)));
			}
			
			/* prepare recorder for start */
			recorder.recTime  = recorder.timeDiv;
			recorder.recToEnd = 1;
			recorder.recPos   = 0;
						
			if ((recorder.totalSmps) <= PCMASTER_REC_BUFF_LEN)		
			/* buffer length required is smaller than recorder buffer */
			{
                /* load actual value of trigger variable */ 
                recorder.recLastVal.udw  = *(UWord32 *)(recorder.trgVarAddr);

				respPrepare(PCMASTER_STC_OK,1);
				/* activate recorder */
				periphBitSet(ST_RECACTIVATED, &status); 
			} 
			else
			/* invalid buffer size specified */
			{
				recorder.varCnt = 0;
				/* invalid buffer size */
				respPrepare(PCMASTER_STC_INVBUFF, 1);
				break;
			}
		}break;
        #endif
		case PCMASTER_CMD_READMEMEX:        /* read block of memory */
		{
			length = ((sReadMemEx *)dataBuff)->size;

			if (length <= (PCMASTER_BUFFER_SIZE))
			/* memory block will fit into PC master communication i/o buffer */	
			{
                /* read address */
                memCopy(((sReadMemEx *)dataBuff)->addrByte, 
                        (UWord8*)&varaddr, POINT_LEN);
                memCopy(varaddr, 
                        (((sReturnData *)dataBuff)->data), length);

				respPrepare(PCMASTER_STC_OK,(UWord8)(length+1));	/* OK */
			}
			else						
			/* response greater than buffer */
			{
				/* response buffer overflow */
				respPrepare(PCMASTER_STC_RSPBUFFOVF,1);	
			}
		}break;
		case PCMASTER_CMD_WRITEMEMEX:       /* write block of memory */
		{
			/* read length of memory block from the message */
			length = ((sWriteMemEx *)dataBuff)->size;
			
			archDisableInt();	/* disable interrupts for this operation */

            /* read address */
            memCopy(((sWriteMemEx *)dataBuff)->addrByte, 
                    (UWord8*)&varaddr, POINT_LEN);
            /* write data */
            memCopy( (((sWriteMemEx *)dataBuff)->data), varaddr, length);
		
			archEnableInt();	/* disable interrupts for this operation */

			respPrepare(PCMASTER_STC_OK,1);
		}break;
		case PCMASTER_CMD_WRITEMEMMASKEX:        /* write to memory with mask */
		{
			UWord8 tmp;    /* variables only for writememmask */
			
			/* read length of memory block from the message */
			length = ((sWriteMemEx *)dataBuff)->size;
            /* read address */
            memCopy(((sWriteMemEx *)dataBuff)->addrByte, 
                    (UWord8*)&varaddr, POINT_LEN);			

            for (i=0 ; i<((sWriteMemEx *)dataBuff)->size ; i++)
            {
                tmp  = ((sWriteMemEx *)dataBuff)->data[i + length]; /* mask */
                tmp &= ((sWriteMemEx *)dataBuff)->data[i];   /* mask & data */

                archDisableInt();             /* disable interrupts */
                tmp |= (*varaddr) & 
                         ~(((sWriteMemEx *)dataBuff)->data[i + length]);	
                *varaddr = tmp;               /* write back modified data */
                archEnableInt();              /* enable interrupts */

                varaddr++;                    /* increment address */
            }

			respPrepare(PCMASTER_STC_OK,1);    /* OK */
		}break;	
		#ifdef PCMASTER_INCLUDE_CMD_APPCMD
		case PCMASTER_CMD_CALLAPPCMD:      /* call user application command */
		{
		    if (((sCallAppCmd *)dataBuff)->cmdLen > PCMASTER_APPCMD_BUFF_LEN)	
			/* check Application Command length */
			{
			     /* invalid buffer size */
				respPrepare(PCMASTER_STC_INVBUFF,1);
			}
			else
			{
				if (appCmdSts == PCMASTER_APPCMD_RUNNING)	
				/* Application Command already called */
				{
				     /* service is busy	 */
					respPrepare(PCMASTER_STC_SERVBUSY,1);
				}
				else           /* no Application Command was called */
				{
				/* copy Application Command data to 
				                         Application Command buffer */
					for (i=0 ; i<((sCallAppCmd *)dataBuff)->cmdLen ; i++)
					{
					    /* copy data to appcmd buffer */
					    appCmdBuff[i] = 
					              ((sCallAppCmd *)dataBuff)->appCmdData[i];
					}
		
					appCmdSts = PCMASTER_APPCMD_RUNNING;  /* new App Cmd */
					respPrepare(PCMASTER_STC_OK,1);       /* OK */
				}
			}
		}break;
		#endif
		default:                                         /* invalid command */
		{
			respPrepare(PCMASTER_STC_INVCMD,1);         /* invalid command */
		}break; 
	}
}

/*******************************************************************************
*
* Module: unsigned int readRecSample(unsigned int position)
*
* Description: The function samples onr set of variables into the internal 
*              recorder buffer
*       
* Global Data:
*       recorderBuff - recorder data buffer
*       recorder     - structure with the settings and temporary 
*                      variables of recorder
*
* Returns: position in the recorder buffer after data sampling
*
* Arguments: position in the recorder buffer
*
* Range Issues: none
*
* Special Issues: none
*
*******************************************************************************/

#ifdef PCMASTER_INCLUDE_CMD_RECORDER
static UWord16 readRecSample(UWord16 position)
{
    Word16 i;
      
    for (i=0 ; i < recorder.varCnt ; i++)    /* read each variable */
    {
	    /* read each variable */
        memCopy((recorder.varDef[i].varAddr), &recorderBuff[position], \
                recorder.varDef[i].varSize);
        position += recorder.varDef[i].varSize;
	}
	return(position);
}
#endif

/*******************************************************************************
*
* Module: void pcmasterRecorder(void)
*
* Description: The function checks the trigger condition, time base multiple
*              and does the sampling
*     
* Global Data:
*       recorderBuff - recorder data buffer
*       recorder     - structure with the settings and temporary 
*                      variables of recorder
*
* Returns: none
*
* Arguments: none
*
* Range Issues: none
*
* Special Issues: none
*
*******************************************************************************/

#ifdef PCMASTER_INCLUDE_CMD_RECORDER
void pcmasterRecorder(void)
{
volatile union{
    UWord8      uch;
    Word8       ch;
	UWord16     uw;
	Word16      w;
    UWord32     udw;
    Word32      dw;
} actual;

	if (status & ST_RECACTIVATED)	/* recorder activated */
	{
		if (recorder.recTime == recorder.timeDiv)
		/* now is the right time to make samples */
		{
            if (!(ST_REC_READ_PRETRIG & status2))
            {
                if (recPretrigCount >= (recorder.totalSmps - 
                            (recorder.recSetLen * recorder.postTrigger))) 
                    periphBitSet(ST_REC_READ_PRETRIG, &status2);
                    else recPretrigCount += recorder.recSetLen;
            }
		
			switch (status & 0x000F)
			{
			/******************************************************************/
			case TRG_UNSIGNED_CHAR:
			{
			    /* read actual value of trigger variable */
                actual.uch = *(UWord8 *)(recorder.trgVarAddr);

                /* read new samples */
                recorder.recPos = readRecSample(recorder.recPos);
                /* wrap around */
                if (recorder.recPos >= recorder.totalSmps) recorder.recPos=0;	
				
				if ( (!(status & ST_RECRUNNING)) && (status2 & ST_REC_READ_PRETRIG) )
				{
					if ((recorder.trgMode == PCMASTER_REC_TRIGRIS) &&
                        (actual.uch >= recorder.trgTreshold.uch) &&
                        (recorder.recLastVal.uch < recorder.trgTreshold.uch))
					/* recorder is configured to rising edge
					   actual value greater than treshold
					   last value smaller than treshold */
					{
						periphBitSet(ST_RECRUNNING, &status);				
						recorder.recToEnd = recorder.postTrigger-1;
					}
					else if ((recorder.trgMode == PCMASTER_REC_TRIGFAL) &&
                             (actual.uch <= recorder.trgTreshold.uch) &&
                           (recorder.recLastVal.uch > recorder.trgTreshold.uch))
					/* recorder is configured to falling edge
					   actual value smaller than treshold
					   last value greater than treshold */
					{
						periphBitSet(ST_RECRUNNING, &status);				
						recorder.recToEnd = recorder.postTrigger-1;
					}
				}
				else if(status2 & ST_REC_READ_PRETRIG) recorder.recToEnd--;
			
				if (recorder.recToEnd==0)
				/* buffer is full */
				{
					periphBitClear(ST_RECRUNNING | ST_RECACTIVATED, &status);
					recorder.recToEnd=1;
				}
				/* store last value */
				recorder.recLastVal.uch = actual.uch;	
				/* reset recorder time */
				recorder.recTime = 0;		
			}break;
			/******************************************************************/
			case TRG_SIGNED_CHAR:
			{
			    /* read actual value of trigger variable */
                actual.ch = *(Word8 *)(recorder.trgVarAddr);

                /* read new samples */
                recorder.recPos = readRecSample(recorder.recPos);
                /* wrap around */
                if (recorder.recPos >= recorder.totalSmps) recorder.recPos=0;	
				
				if ( (!(status & ST_RECRUNNING)) && (status2 & ST_REC_READ_PRETRIG) )
				{
                    if ((recorder.trgMode == PCMASTER_REC_TRIGRIS) &&
                        (actual.ch >= recorder.trgTreshold.ch) &&
                        (recorder.recLastVal.ch < recorder.trgTreshold.ch))
					/* recorder is configured to rising edge
					   actual value greater than treshold
					   last value smaller than treshold */
					{
						periphBitSet(ST_RECRUNNING, &status);				
						recorder.recToEnd = recorder.postTrigger-1;
					}
                    else if ((recorder.trgMode == PCMASTER_REC_TRIGFAL) &&
                             (actual.ch <= recorder.trgTreshold.ch) &&
                             (recorder.recLastVal.ch > recorder.trgTreshold.ch))
					/* recorder is configured to falling edge
					   actual value smaller than treshold
					   last value greater than treshold */
					{
						periphBitSet(ST_RECRUNNING, &status);				
						recorder.recToEnd = recorder.postTrigger-1;
					}
				}
				else if(status2 & ST_REC_READ_PRETRIG) recorder.recToEnd--;
			
				if (recorder.recToEnd==0)
				/* buffer is full */
				{
				     periphBitClear(ST_RECRUNNING | ST_RECACTIVATED, &status);		
					recorder.recToEnd=1;
				}
				/* store last value */
				recorder.recLastVal.ch = actual.ch;	
				/* reset recorder time */
				recorder.recTime = 0;		
			}break;
			/******************************************************************/
			case TRG_UNSIGNED_INT:
			{
			    /* read actual value of trigger variable */
                actual.uw = *(UWord16 *)(recorder.trgVarAddr);

                /* read new samples */
                recorder.recPos = readRecSample(recorder.recPos);
                /* wrap around */
                if (recorder.recPos >= recorder.totalSmps) recorder.recPos=0;	
				
				if ( (!(status & ST_RECRUNNING)) && (status2 & ST_REC_READ_PRETRIG) )
				{
                    if ((recorder.trgMode == PCMASTER_REC_TRIGRIS) &&
                        (actual.uw >= recorder.trgTreshold.uw) &&
                        (recorder.recLastVal.uw < recorder.trgTreshold.uw))
					/* recorder is configured to rising edge
					   actual value greater than treshold
					   last value smaller than treshold */
					{
						periphBitSet(ST_RECRUNNING,&status);				
						recorder.recToEnd = recorder.postTrigger-1;
					}
                    else if ((recorder.trgMode == PCMASTER_REC_TRIGFAL) &&
                             (actual.uw <= recorder.trgTreshold.uw) &&
                             (recorder.recLastVal.uw > recorder.trgTreshold.uw))
					/* recorder is configured to falling edge
					   actual value smaller than treshold
					   last value greater than treshold */
					{
						periphBitSet(ST_RECRUNNING,&status);				
						recorder.recToEnd = recorder.postTrigger-1;
					}
				}
				else if(status2 & ST_REC_READ_PRETRIG) recorder.recToEnd--;
			
				if (recorder.recToEnd==0)
				/* buffer is full */
				{
					periphBitClear(ST_RECRUNNING | ST_RECACTIVATED, &status);		
					recorder.recToEnd=1;
				}
				/* store last value */
				recorder.recLastVal.uw = (UWord16)actual.uw;	
				/* reset recorder time */
				recorder.recTime = 0;		
			}break; 
			/******************************************************************/			
			case TRG_SIGNED_INT:
			{
			    /* read actual value of trigger variable */
				actual.w = *(Word16 *)(recorder.trgVarAddr);

                /* read new samples */
                recorder.recPos = readRecSample(recorder.recPos);
                /* wrap around */
                if (recorder.recPos >= recorder.totalSmps) recorder.recPos=0;	
				
				if ( (!(status & ST_RECRUNNING)) && (status2 & ST_REC_READ_PRETRIG) )
				{
                    if ((recorder.trgMode == PCMASTER_REC_TRIGRIS) &&
                        (actual.w >= recorder.trgTreshold.w) &&
                        (recorder.recLastVal.w < recorder.trgTreshold.w))
					/* recorder is configured to rising edge
					   actual value greater than treshold
					   last value smaller than treshold */
					{
						periphBitSet(ST_RECRUNNING, &status);				
						recorder.recToEnd = recorder.postTrigger-1;
					}
                    else if ((recorder.trgMode == PCMASTER_REC_TRIGFAL) &&
                             (actual.w <= recorder.trgTreshold.w) &&
                             (recorder.recLastVal.w > recorder.trgTreshold.w))
					/* recorder is configured to falling edge
					   actual value smaller than treshold
					   last value greater than treshold */
					{
						periphBitSet(ST_RECRUNNING ,&status);				
						recorder.recToEnd = recorder.postTrigger-1;
					}
				}
				else if(status2 & ST_REC_READ_PRETRIG) recorder.recToEnd--;
			
				if (recorder.recToEnd==0)
				/* buffer is full */
				{
					periphBitClear(ST_RECRUNNING | ST_RECACTIVATED, &status);			
					recorder.recToEnd=1;
				}
				/* store last value */
				recorder.recLastVal.w=(Word16)actual.w;	
				/* reset recorder time */
				recorder.recTime=0;		
			}break;
			/******************************************************************/
			case TRG_UNSIGNED_DWORD:
			{
			    /* read actual value of trigger variable */
                actual.udw = *(UWord32 *)(recorder.trgVarAddr);

                /* read new samples */
                recorder.recPos = readRecSample(recorder.recPos);
                /* wrap around */
                if (recorder.recPos >= recorder.totalSmps) recorder.recPos=0;	
				
				if ( (!(status & ST_RECRUNNING)) && (status2 & ST_REC_READ_PRETRIG) )
				{
                    if ((recorder.trgMode == PCMASTER_REC_TRIGRIS) &&
                        (actual.udw >= recorder.trgTreshold.udw) &&
                        (recorder.recLastVal.udw < recorder.trgTreshold.udw))
					/* recorder is configured to rising edge
					   actual value greater than treshold
					   last value smaller than treshold */
					{
						periphBitSet(ST_RECRUNNING,&status);				
						recorder.recToEnd = recorder.postTrigger-1;
					}
                    else if ((recorder.trgMode == PCMASTER_REC_TRIGFAL) &&
                             (actual.udw <= recorder.trgTreshold.udw) &&
                           (recorder.recLastVal.udw > recorder.trgTreshold.udw))
					/* recorder is configured to falling edge
					   actual value smaller than treshold
					   last value greater than treshold */
					{
						periphBitSet(ST_RECRUNNING,&status);				
						recorder.recToEnd = recorder.postTrigger-1;
					}
				}
				else if(status2 & ST_REC_READ_PRETRIG) recorder.recToEnd--;
			
				if (recorder.recToEnd==0)
				/* buffer is full */
				{
					periphBitClear(ST_RECRUNNING | ST_RECACTIVATED, &status);		
					recorder.recToEnd=1;
				}
				/* store last value */
				recorder.recLastVal.udw = (UWord32)actual.udw;	
				/* reset recorder time */
				recorder.recTime = 0;		
			}break; 
			/******************************************************************/			
			case TRG_SIGNED_DWORD:
			{
			    /* read actual value of trigger variable */
				actual.dw = *(Word32 *)(recorder.trgVarAddr);

                /* read new samples */
                recorder.recPos = readRecSample(recorder.recPos);
                /* wrap around */
                if (recorder.recPos >= recorder.totalSmps) recorder.recPos=0;	
				
				if ( (!(status & ST_RECRUNNING)) && (status2 & ST_REC_READ_PRETRIG) )
				{
                    if ((recorder.trgMode == PCMASTER_REC_TRIGRIS) &&
                        (actual.dw >= recorder.trgTreshold.dw) &&
                        (recorder.recLastVal.dw < recorder.trgTreshold.dw))
					/* recorder is configured to rising edge
					   actual value greater than treshold
					   last value smaller than treshold */
					{
						periphBitSet(ST_RECRUNNING, &status);				
						recorder.recToEnd = recorder.postTrigger-1;
					}
                    else if ((recorder.trgMode == PCMASTER_REC_TRIGFAL) &&
                             (actual.dw <= recorder.trgTreshold.dw) &&
                             (recorder.recLastVal.dw > recorder.trgTreshold.dw))
					/* recorder is configured to falling edge
					   actual value smaller than treshold
					   last value greater than treshold */
					{
						periphBitSet(ST_RECRUNNING ,&status);				
						recorder.recToEnd = recorder.postTrigger-1;
					}
				}
				else if(status2 & ST_REC_READ_PRETRIG) recorder.recToEnd--;				
			
				if (recorder.recToEnd==0)
				/* buffer is full */
				{
					periphBitClear(ST_RECRUNNING | ST_RECACTIVATED, &status);			
					recorder.recToEnd=1;
				}
				/* store last value */
				recorder.recLastVal.dw=(Word32)actual.dw;	
				/* reset recorder time */
				recorder.recTime=0;		
			}break;
			/******************************************************************/
			case 0: /* no trigger variable specified */
			{
				/* read new samples */
                recorder.recPos = readRecSample(recorder.recPos);

				/* wrap around */
				if (recorder.recPos >= recorder.totalSmps) recorder.recPos=0;		
									
				if (status & ST_RECRUNNING)
				{
				    recorder.recToEnd--;
				}
				if (recorder.recToEnd==0)   /* buffer is full */
				{
                    periphBitClear(ST_RECRUNNING | ST_RECACTIVATED, &status);			
                    periphBitClear(ST_REC_READ_PRETRIG, &status2);			
                    recorder.recToEnd = 1;
				}
				/* reset recorder time */
				recorder.recTime=0;		
			}break;
			/******************************************************************/
    		}
		}
		/* wait for the right time */
		else recorder.recTime++;			
	}
    else /* recorder not activated */
    {
        recPretrigCount = 0;
        periphBitClear(ST_REC_READ_PRETRIG, &status2);
    }	
}
#endif

/*******************************************************************************
*
* Module: static void messageData(unsigned int startOfMessage)
*
* Description: 2nd layer of the protocol decoding. This function checks if the
*              received message is complete and checks the checksum as well. If
*              the message is OK the 3rd layer function messageDecode is called.
*     
* Global Data:
*       pos      - position in buffer (0,1,2,...)
*       length   - length of data in a message used for receiving 
*                  and transmitting (exclude SOB, include checksum)
*       checkSum - variable for checksum accumulation
*       status   - status word of receiver
*       inChar   - currently read input char 
*                  (it contains checksum at the end of message)
*       dataBuff - PC master communication i/o buffer
*
* Returns: none
*
* Arguments: none
*
* Range Issues: none
*
* Special Issues: none
*
*******************************************************************************/

static void messageData(unsigned int startOfMessage)
{
	if (startOfMessage == 0)	/* no start of message */
	{
		if (status & ST_STARTED)	/* start of message already detected */
		{
			if (pos != length)		
			{
				/* read byte, accumulate checksum */
				dataBuff[pos] = inChar;		
				checkSum += inChar;	          /* checksum accumulation */
				pos++;                        /* next position in buffer */

				if (status & ST_STD_CMD)	
				/* inChar contains length of standard format message */
				{
					length = (UWord8)(inChar + 2);	/* read length of message */
					periphBitClear(ST_STD_CMD,&status);    /* clear flag */
			
					if (length > (PCMASTER_BUFFER_SIZE))
					/* command is greater than input buffer */
					{
						/* clear flag */
						periphBitClear(ST_STARTED | ST_ST_CHAR_REC, \
						                                        &status);	
						/* input buffer overflow */
						respPrepare(PCMASTER_STC_CMDBUFFOVF,1);	
						sendResponse(&response);	/* send response to PC */
						/* disable Rx Full Interrupt during transmitting*/
						
						/* disable rx int */
                        ioctl(PCMASTER_COMM_MODULE, SCI_RX_INT, SCI_DISABLE);
					}
				}			
			}
			else	/* end of message */
			{
				checkSum += inChar;			/* accumulate checksum */
				if ((checkSum & 0x00FF) == 0) /* correct checksum */
				{
					messageDecode();
				}
				else						/* checksum error */
				{
					/* checksum error response */
					respPrepare(PCMASTER_STC_CMDSERR,1);	
				}
				
				/* clear flag */
				periphBitClear(ST_STARTED | ST_ST_CHAR_REC,&status);	
				sendResponse(&response);	/* send response to PC */
				/* disable Rx Full Interrupt during transmitting*/
				
				/* disable rx int */
                ioctl(PCMASTER_COMM_MODULE, SCI_RX_INT, SCI_DISABLE);
			}
		}
	}
	else			/* start of message */
	{
		/* reset receiver, read first byte of message */
		periphBitSet(ST_STARTED,&status);			/* message receiving */
		/* read byte, start of checksum accumulating */
        dataBuff[0] = inChar;
		checkSum = (Word8)inChar;
		/* next position in buffer */
		pos = 1;							
		/* value sufficient for standard format commands */
		length = 2;							
		
		if (inChar >= 0xC0)		/* special format command */
		{
		    /* length decoding */
			length = (UWord8)(((inChar & 0x30) >> 3) + 1); 
		}
		else	
		/* standard format command (next byte will be 
		                                        length of the message) */
		{
			periphBitSet(ST_STD_CMD, &status);  /* wait for next character */
		}
	}
}

/*******************************************************************************
*
* Module: void pcmasterRxTxIsr(void)
*
* Description: 1st layer of the protocol decoding. This function receives and 
*              stores data and supports protocol transparency. This layer does
*              not generate any error mesages.
*
* Global Data:
*       status   - status word of receiver
*       inChar   - currently read input char 
*                  (it contains checksum at the end of message)
*
* Returns: none
*
* Arguments: none
*
* Range Issues: none
*
* Special Issues: none
*
*******************************************************************************/

static void pcmasterRxTxIsr(void)
{

	/* message is transmitted */
	if (status & ST_SENDING) 	sendBuffer(); 	/* send data */			
	else
	{
        inChar = (UWord8)ioctl(PCMASTER_COMM_MODULE, SCI_READ_DATA, NULL);
		//wangwei add 2005-12-05
		
		if (inChar == 'X')
		{
		///ioctl( MIOS_PIO, PIO_SET_PIN, PIO_BIT_ALL);
		 //	archDisableInt();
		 //Flash_prog_start(0X01);//Flash模式
		//	Flash_Sector_Prog();  //Ram模式
//			Main_Program(0x01);
		//	Flash_prog_start(0x01);
		}else
		if (inChar == 'D')
		{
		///	ioctl( MIOS_PIO, PIO_SET_PIN, PIO_BIT_ALL);
			//Flash_prog_start(0X02);// Flash模式
		//	SCI_SectorData_Send();   //Ram模式
//			Main_Program(0x02);
		//	Flash_prog_start(0x02);
		}else
		if (inChar == 'G')//上位机获取参数段
		{
		///	ioctl( MIOS_PIO, PIO_SET_PIN, PIO_BIT_ALL);
			//Flash_prog_start(0X02);// Flash模式
		//	SCI_SectorData_Send();   //Ram模式
//			Main_Program(0x03);
		//	Flash_prog_start(0x03);	
		}else
		if (inChar == 'M')//修改参数段
		{
		///	ioctl( MIOS_PIO, PIO_SET_PIN, PIO_BIT_ALL);
			//Flash_prog_start(0X02);// Flash模式
		//	SCI_SectorData_Send();   //Ram模式
//			Main_Program(0x04);
		//	Flash_prog_start(0x04);	
		}else
		if (inChar == 'W') 
		{
//		 	ioctl( MIOS_PIO, PIO_SET_PIN, PIO_BIT_ALL);
	//	 	archDisableInt();
		// 	Main_Program(0x05);
//		 	Flash_prog_start(0x05);	 	
		}else
		if(inChar == 'C')
		{
			
//			GetFramData();
		}else
		if(inChar == 'A')
		{
//			GetClockData();
		}
		else
		{
		// 	ioctl(PCMASTER_COMM_MODULE, SCI_WRITE_DATA, inChar);//测试连接用
		}
		
		if ((status & ST_ST_CHAR_REC) == 0)	/* last byte was not '+' */
		{
			if (inChar == '+') 			    /* '+' received */
			{
				periphBitSet(ST_ST_CHAR_REC, &status);
			}
			else 						/* any byte received */
			{
				messageData(0);			/* byte received */
			}
		}
		else				            /* the last byte was '+' */
		{
			if (inChar == '+') 	/* doubled '+' (this is the second one) */
			{
				messageData(0);         /* byte received */
			}
			else                        /* start of message */
			{
				messageData(1);         /* byte received */
			}	

				periphBitClear(ST_ST_CHAR_REC, &status);    /* clear flag */
		}
		
	
	}
}

/*******************************************************************************
*
* Module: void pcmasterDispatcher(void)
*
* Description: The pcmasterDispatcher function is an interrupt function called
*              as an SCI dispatcher.
*
* Global Data: none
*
* Returns: none
*
* Arguments: none
*
* Range Issues: none
*
* Special Issues: none
*
*******************************************************************************/

void pcmasterDispatcher(void)
{
    volatile UWord8 temp;
    
     //  ioctl( MIOS_PIO, PIO_TOGGLE_PIN, PIO_BIT_1);//wangwei add
       
       
       
       
    /* rx error */
    if (ioctl(PCMASTER_COMM_MODULE, SCI_GET_FLAGS, SCI_RX_OVERRUN | SCI_RX_NOISE_ERROR | 
                          SCI_RX_FRAMING_ERROR | SCI_RX_PARITY_ERROR))      
    {
        /* clear error flags */
        temp = (UWord8)ioctl(PCMASTER_COMM_MODULE, SCI_READ_DATA, NULL);  
    } else
    if (ioctl(PCMASTER_COMM_MODULE, SCI_GET_FLAGS, SCI_RX_FULL))   /* received new data */
    {
        pcmasterRxTxIsr();

    } else
    if (ioctl(PCMASTER_COMM_MODULE, SCI_GET_FLAGS, SCI_TX_EMPTY))      /* tx empty */
    {
        pcmasterRxTxIsr();       
    }
}
