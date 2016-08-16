/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2010 Freescale Semiconductor
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   freemaster.h
*
* @brief  FreeMASTER Driver main API header file, HC(S)12(X) platform
*
* @version 1.0.11.0
* 
* @date Apr-16-2010
* 
*******************************************************************************
*
* This is the only header file needed to be included by the user application
* to implement the FreeMASTER interface. In addition, user has to write her 
* "freemaster_cfg.h" configuration file and put it anywhere on the #include path
*
*******************************************************************************/

#ifndef __FREEMASTER_H
#define __FREEMASTER_H

/* identify our current platform */
#define FMSTR_PLATFORM_HC12 1

/* user configuration */
#include "freemaster_cfg.h"

/* HCS12X only: determine large/small model for FreeMASTER pointers and memory 
   access. The user may enable FMSTR_LARGE_MODEL model in configuration file
   even if project is configured for small or banked models. */
   
#ifdef __HCS12X__
    #ifndef FMSTR_LARGE_MODEL
        #if defined(__LARGE__)
        #define FMSTR_LARGE_MODEL 1
        #elif defined(__SMALL__) || defined(__BANKED__)
        #define FMSTR_LARGE_MODEL 0
        #else
        #error Unknown compiler memory model
        #endif
    #endif
#else
    /* large driver model not implemented on HC12 or HCS12 */
    #ifndef FMSTR_LARGE_MODEL
    #define FMSTR_LARGE_MODEL 1  //ADD BY XIE
    #endif
    #if FMSTR_LARGE_MODEL
    #error Large FreeMASTER driver model possible on HCS12X only
    #endif
#endif

/*****************************************************************************
* Global types
******************************************************************************/

#if FMSTR_LARGE_MODEL
typedef unsigned char*__far  FMSTR_ADDR;   /* CPU address type (3bytes) */

#else
typedef unsigned char*__near FMSTR_ADDR;   /* CPU address type (2bytes) */
#endif

typedef unsigned short FMSTR_SIZE;   /* general size type (at least 16 bits) */
typedef unsigned char FMSTR_BOOL;    /* general boolean type  */

/* application command-specific types */
typedef unsigned char FMSTR_APPCMD_CODE;
typedef unsigned char FMSTR_APPCMD_DATA, *FMSTR_APPCMD_PDATA;
typedef unsigned char FMSTR_APPCMD_RESULT;

/* pointer to application command callback handler */
typedef FMSTR_APPCMD_RESULT (*FMSTR_PAPPCMDFUNC)(FMSTR_APPCMD_CODE,FMSTR_APPCMD_PDATA,FMSTR_SIZE);

/*****************************************************************************
* TSA-related user types and macros
******************************************************************************/

#ifdef __HCS12X__
    #if FMSTR_LARGE_MODEL
        /* sizeof(void*) is 3 in large model, we must make TSA entries 4 bytes  */
        #define FMSTR_TSATBL_STRPTR          unsigned long
        #define FMSTR_TSATBL_VOIDPTR         unsigned long
        #define FMSTR_TSATBL_STRPTR_CAST(x)  ((unsigned long)((char*__far)(x)))
        #define FMSTR_TSATBL_VOIDPTR_CAST(x) ((unsigned long)((void*__far)(x)))
    #else
        /* HCS12X small model near pointers */
        #define FMSTR_TSATBL_STRPTR   char*__near 
        #define FMSTR_TSATBL_VOIDPTR  void*__near
    #endif
#endif

#include "freemaster_tsa.h"

/*****************************************************************************
* Constants
******************************************************************************/

/* application command status information  */
#define FMSTR_APPCMDRESULT_NOCMD      0xff
#define FMSTR_APPCMDRESULT_RUNNING    0xfe
#define MFSTR_APPCMDRESULT_LASTVALID  0xf7  /* F8-FF are reserved  */

/* recorder time base declaration helpers */
#define FMSTR_REC_BASE_SECONDS(x)  ((x) & 0x3fff)
#define FMSTR_REC_BASE_MILLISEC(x) (((x) & 0x3fff) | 0x4000)
#define FMSTR_REC_BASE_MICROSEC(x) (((x) & 0x3fff) | 0x8000)
#define FMSTR_REC_BASE_NANOSEC(x)  (((x) & 0x3fff) | 0xc000)

/*****************************************************************************
* Global functions 
******************************************************************************/

/* FreeMASTER serial communication API */
void FMSTR_Init(void);    /* general initiazlation */
void FMSTR_Poll(void);    /* polling call, use in SHORT_INTR and POLL_DRIVEN modes */

#include "non_bank.sgm"
void FMSTR_Isr(void);     /* interrupt handler for LONG_INTR and SHORT_INTR modes */
void FMSTR_Isr2(void);    /* the second interrupt handler (when RX,TX vecotrs separate) */
#include "default.sgm"

/* Recorder API */
void FMSTR_Recorder(void);
void FMSTR_TriggerRec(void);
void FMSTR_SetUpRecBuff(FMSTR_ADDR nBuffAddr, FMSTR_SIZE nBuffSize);

/* Application commands API */
FMSTR_APPCMD_CODE  FMSTR_GetAppCmd(void);
FMSTR_APPCMD_PDATA FMSTR_GetAppCmdData(FMSTR_SIZE* pDataLen);
FMSTR_BOOL         FMSTR_RegisterAppCmdCall(FMSTR_APPCMD_CODE nAppCmdCode, FMSTR_PAPPCMDFUNC pCallbackFunc);

void FMSTR_AppCmdAck(FMSTR_APPCMD_RESULT nResultCode);
void FMSTR_AppCmdSetResponseData(FMSTR_ADDR nResultDataAddr, FMSTR_SIZE nResultDataLen);

#endif /* __FREEMASTER_H */

