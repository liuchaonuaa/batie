/*******************************************************************************
*
* Motorola Inc.
* (c) Copyright 2002 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name: pcmaster.h
*
* Description: Header file for pcmaster.c (PC master communication)
*
* Modules Included: None
*
*******************************************************************************/

#ifndef _PCMASTER_H_
#define _PCMASTER_H_

/******************************************************************************/
/*         PC master communication protocol version 3.0 specific part:        */
/*                                                                            */
/*                            !!! DO NOT MODIFY !!!                           */
/******************************************************************************/
/*-------------------------------------
  command message - standard commands
  -------------------------------------*/

#define PCMASTER_CMD_READMEM          0x01 /* read block of memory */
#define PCMASTER_CMD_READMEMEX        0x04 /* v3+ */
#define PCMASTER_CMD_WRITEMEM	      0x02 /* write block of memory */
#define PCMASTER_CMD_WRITEMEMMASK     0x03 /* write block of memory with mask */
#define PCMASTER_CMD_WRITEMEMEX       0x05 /* v3+ */
#define PCMASTER_CMD_WRITEMEMMASKEX   0x06 /* v3+ */
#define PCMASTER_CMD_SETUPSCOPE       0x08 /* setup scope */
#define PCMASTER_CMD_SETUPSCOPEEX     0x0A /* v3+ */
#define PCMASTER_CMD_SETUPREC         0x09 /* setup recorder */
#define PCMASTER_CMD_SETUPRECEX       0x0B /* v3+ */
#define PCMASTER_CMD_CALLAPPCMD       0x10 /* call user application command */

/*-------------------------------------
   command message - special commands
  -------------------------------------*/
/* no data part */
#define PCMASTER_CMD_GETINFO       0xC0   /* get system information */
#define PCMASTER_CMD_GETINFOBRIEF  0xC8   /* get brief system information */
#define PCMASTER_CMD_STARTREC      0xC1   /* start recorder */
#define PCMASTER_CMD_STOPREC       0xC2   /* stop recorder */
#define PCMASTER_CMD_GETRECSTS     0xC3   /* get recorder status */
#define PCMASTER_CMD_GETRECBUFF    0xC4   /* get recorder buffer information */
#define PCMASTER_CMD_GETRECBUFFEX  0xC9   /* v3+ */
#define PCMASTER_CMD_READSCOPE     0xC5   /* read scope variables */
#define PCMASTER_CMD_GETAPPCMDSTS  0xC6   
/* 2 bytes data part */
#define PCMASTER_CMD_READVAR8      0xD0   
#define PCMASTER_CMD_READVAR16     0xD1   
#define PCMASTER_CMD_READVAR32     0xD2   
/* 4 bytes data part */
#define PCMASTER_CMD_WRITEVAR8     0xE3
#define PCMASTER_CMD_WRITEVAR16    0xE4
#define PCMASTER_CMD_READVAR8EX    0xE0   
#define PCMASTER_CMD_READVAR16EX   0xE1   
#define PCMASTER_CMD_READVAR32EX   0xE2   

/* 6 bytes data part */
/* write 32-bit variable */
#define PCMASTER_CMD_WRITEVAR32    0xF0

/* get info command parameters */
#define PCMASTER_PROT_VER          3       /* PC master protocol version 3.0 */
#define PCMASTER_DATABUSWDT        1       /* data bud width 8 bit */
#define PCMASTER_CFG_FLAFGS        0x0001  /* big endian */
#define PCMASTER_IDT_STRING_LEN    25      /* length of identification string */

/*-------------------------------------
  response message - status byte
  -------------------------------------*/
/* confirmation codes */
#define PCMASTER_STC_OK            0x00   /* operation succesful */
#define PCMASTER_STC_RECRUN        0x01   /* recorder running */
#define PCMASTER_STC_RECDONE       0x02   /* recorder already finished */

/* error codes */
#define PCMASTER_STC_INVCMD        0x81   /* invalid command */
#define PCMASTER_STC_CMDSERR       0x82   /* checksum error */
#define PCMASTER_STC_CMDBUFFOVF    0x83   /* command too long */
#define PCMASTER_STC_RSPBUFFOVF    0x84   /* response would be too long */
#define PCMASTER_STC_INVBUFF       0x85   /* invalid buffer length specified */
#define PCMASTER_STC_INVSIZE       0x86   /* invalid size */
#define PCMASTER_STC_SERVBUSY      0x87   /* service is busy */
#define PCMASTER_STC_NOTINIT       0x88   /* scope/recorder not configured */
#define PCMASTER_STC_UNKNOWN       0xFF   /* reserved */

/* recorder trigger modes */
#define PCMASTER_REC_TRIGOFF       0      /* manual mode (trigger disabled) */
#define PCMASTER_REC_TRIGRIS       1      /* rising edge */
#define PCMASTER_REC_TRIGFAL       2      /* falling edge */

/* recorder trigger data formats */
#define TRG_UNSIGNED_CHAR           0x02
#define TRG_SIGNED_CHAR             0x03
#define TRG_UNSIGNED_INT            0x04
#define TRG_SIGNED_INT              0x05
#define TRG_UNSIGNED_DWORD          0x08
#define TRG_SIGNED_DWORD            0x09

/******************************************************************************/
/*                                                                            */
/*   PC master buffer lengths and other default values:                       */
/*	                                                                          */
/*   PCMASTER_BUFFER_SIZE         - PC master input/output buffer size        */
/*   PCMASTER_REC_BUFF_LEN        - PC master Recorder buffer size            */
/*   PCMASTER_APPCMD_BUFF_LEN	  - PC master Applciation Command buffer size */
/*   PCMASTER_RECORDER_TIME_BASE  - PC master Recorder time base value        */
/*   PCMASTER_GLOB_VERSION_MAJOR  - board firmware major number               */
/*   PCMASTER_GLOB_VERSION_MINOR  - board firmware minor number               */
/*   PCMASTER_IDT_STRING          - device identification string              */
/*                                                                            */
/*   NOTE: This values should be defined in the appconfig.h file              */
/*                                                                            */
/*   E.G.                                                                     */
/*                                                                            */
/*   #define PCMASTER_BUFFER_SIZE 150                                         */
/*   (this code placed in the appconfig.h file will enlarge the PC master     */
/*   input/output buffer size to 150 from default value 40)                   */
/*	                                                                          */
/******************************************************************************/

#ifndef PCMASTER_BUFFER_SIZE
  /* PC master input/output buffer size */
  #define PCMASTER_BUFFER_SIZE 40
#endif

#ifndef PCMASTER_REC_BUFF_LEN
  /* recorder buffer length */
  #define PCMASTER_REC_BUFF_LEN 200
#endif

#ifndef PCMASTER_RECORDER_TIME_BASE
  /* recorder time base default value */
  #define PCMASTER_RECORDER_TIME_BASE	0x8000 
#endif

#ifndef PCMASTER_APPCMD_BUFF_LEN
/* Application Command buffer length */
#define PCMASTER_APPCMD_BUFF_LEN 10
#endif

#ifndef PCMASTER_GLOB_VERSION_MAJOR
  /* board firmware version major number */
  #define PCMASTER_GLOB_VERSION_MAJOR	0				
#endif

#ifndef	PCMASTER_GLOB_VERSION_MINOR
  /* board firmware version minor number */
  #define PCMASTER_GLOB_VERSION_MINOR	0
#endif

#ifndef PCMASTER_IDT_STRING
  /* device identification string */
  #define PCMASTER_IDT_STRING "PC master communication !"
#endif

#ifndef PCMASTER_COMM_MODULE
    /* set PC master software communication module */
    /* available modules:  QSMCM_SCI1
                           QSMCM_SCI2

                           QSMCM_A_SCI1 (MPC565/566)
                           QSMCM_A_SCI2 (MPC565/566)
                           QSMCM_B_SCI1 (MPC565/566)
                           QSMCM_B_SCI2 (MPC565/566)    */
    #if defined(APPCFG_MPC555) || defined(APPCFG_MPC556)
        #define PCMASTER_COMM_MODULE    QSMCM_SCI1
    #endif
    #if defined(APPCFG_MPC561) || defined(APPCFG_MPC562) || defined(APPCFG_MPC563) || \
        defined(APPCFG_MPC564) || defined(APPCFG_MPC565) || defined(APPCFG_MPC566) || \
        defined(APPCFG_MPC533) || defined(APPCFG_MPC535) || defined(APPCFG_MPC534) || \
        defined(APPCFG_MPC536)
        #define PCMASTER_COMM_MODULE    QSMCM_A_SCI1
    #endif
#endif

/******************************************************************************/
/*      GLOBAL FUNCTION DECLARATION                                           */
/******************************************************************************/

Word16 pcmasterInit(void);

#ifdef PCMASTER_INCLUDE_CMD_APPCMD
  unsigned char pcmasterGetAppCmdSts(void);
#else
  #define pcmasterGetAppCmdSts() 0 /* no new command received */
#endif

#ifdef PCMASTER_INCLUDE_CMD_APPCMD
  char pcmasterWriteAppCmdSts(unsigned char state);
#else
  #define pcmasterWriteAppCmdSts(x) 0
#endif

#ifdef PCMASTER_INCLUDE_CMD_RECORDER
  void pcmasterRecorder(void);
#else
  #define pcmasterRecorder()
#endif

void pcmasterDispatcher(void);

#endif


