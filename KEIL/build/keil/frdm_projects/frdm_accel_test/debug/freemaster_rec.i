#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.c"






 









 

#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster.h"






 















 




 


 
#line 1 "..\\..\\..\\..\\src\\projects\\frdm_projects\\frdm_accel_test\\freemaster_cfg.h"






 






 







 













 





 





 







 






 













 







 







 







#line 33 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster.h"



 

typedef unsigned char* FMSTR_ADDR;    
typedef unsigned short FMSTR_SIZE;    
typedef unsigned char FMSTR_BOOL;     

 
typedef unsigned char FMSTR_APPCMD_CODE;
typedef unsigned char FMSTR_APPCMD_DATA, *FMSTR_APPCMD_PDATA;
typedef unsigned char FMSTR_APPCMD_RESULT;

 
typedef FMSTR_APPCMD_RESULT (*FMSTR_PAPPCMDFUNC)(FMSTR_APPCMD_CODE,FMSTR_APPCMD_PDATA,FMSTR_SIZE);



 

#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_tsa.h"






 









 




#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster.h"






 















 

#line 96 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster.h"

#line 23 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_tsa.h"
#line 24 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_tsa.h"



 

 


 
#line 40 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_tsa.h"

 
typedef FMSTR_SIZE FMSTR_TSA_TINDEX;
typedef FMSTR_SIZE FMSTR_TSA_TSIZE;

 
 
#line 59 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_tsa.h"

 
 
typedef struct
{
    union { const char*  p; FMSTR_ADDR n; } name;
    union { const char*  p; FMSTR_ADDR n; } type;
    union { const void* p; FMSTR_ADDR n; } addr;
    union { const void* p; FMSTR_ADDR n; } info;
} FMSTR_TSA_ENTRY;

 
#line 79 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_tsa.h"

 
 









 





    


    
















 
 
 
 

#line 136 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_tsa.h"

 


 



 
 



        





        





 

 
const FMSTR_TSA_ENTRY* FMSTR_TsaGetTable(FMSTR_TSA_TINDEX nTableIndex, FMSTR_TSA_TSIZE* pTableSize);



#line 55 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster.h"



 

 




 







 

 
FMSTR_BOOL FMSTR_Init(void);     
void FMSTR_Poll(void);     

void FMSTR_Isr(void);      
void FMSTR_Isr2(void);     

 
void FMSTR_Recorder(void);
void FMSTR_TriggerRec(void);
void FMSTR_SetUpRecBuff(FMSTR_ADDR nBuffAddr, FMSTR_SIZE nBuffSize);

 
FMSTR_APPCMD_CODE  FMSTR_GetAppCmd(void);
FMSTR_APPCMD_PDATA FMSTR_GetAppCmdData(FMSTR_SIZE* pDataLen);
FMSTR_BOOL         FMSTR_RegisterAppCmdCall(FMSTR_APPCMD_CODE nAppCmdCode, FMSTR_PAPPCMDFUNC pCallbackFunc);

void FMSTR_AppCmdAck(FMSTR_APPCMD_RESULT nResultCode);
void FMSTR_AppCmdSetResponseData(FMSTR_ADDR nResultDataAddr, FMSTR_SIZE nResultDataLen);



#line 20 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.c"
#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"






 









 









#line 28 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"










 



 
 

#line 53 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 62 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 71 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 80 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 89 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 98 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 107 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 116 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 125 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 134 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"






 









 






 
#line 31 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"
	#pragma diag_suppress 174
	#pragma diag_suppress 177
	#pragma diag_suppress 174
	#pragma diag_suppress 550




 

 




 




 








 

#line 69 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"



 

typedef unsigned char  FMSTR_U8;          
typedef unsigned short FMSTR_U16;         
typedef unsigned long  FMSTR_U32;         

typedef signed char    FMSTR_S8;          
typedef signed short   FMSTR_S16;         
typedef signed long    FMSTR_S32;         





typedef unsigned char  FMSTR_FLAGS;       
typedef unsigned char  FMSTR_SIZE8;       
typedef signed short   FMSTR_INDEX;       

typedef unsigned char  FMSTR_BCHR;        
typedef unsigned char* FMSTR_BPTR;        

typedef unsigned char  FMSTR_SCISR;       



 

void FMSTR_CopyMemory(FMSTR_ADDR nDestAddr, FMSTR_ADDR nSrcAddr, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_CopyToBuffer(FMSTR_BPTR pDestBuff, FMSTR_ADDR nSrcAddr, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_CopyFromBuffer(FMSTR_ADDR nDestAddr, FMSTR_BPTR pSrcBuff, FMSTR_SIZE8 nSize);
void FMSTR_CopyFromBufferWithMask(FMSTR_ADDR nDestAddr, FMSTR_BPTR pSrcBuff, FMSTR_SIZE8 nSize);

 

void FMSTR_SetExAddr(FMSTR_BOOL bNextAddrIsEx);






FMSTR_BPTR FMSTR_ValueFromBuffer16(FMSTR_U16* pDest, FMSTR_BPTR pSrc);
FMSTR_BPTR FMSTR_ValueFromBuffer32(FMSTR_U32* pDest, FMSTR_BPTR pSrc);
FMSTR_BPTR FMSTR_ValueToBuffer16(FMSTR_BPTR pDest, FMSTR_U16 src);
FMSTR_BPTR FMSTR_ValueToBuffer32(FMSTR_BPTR pDest, FMSTR_U32 src);




 




#line 133 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"




#line 144 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"








 
#line 168 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"
    FMSTR_BPTR FMSTR_AddressFromBuffer(FMSTR_ADDR* pAddr, FMSTR_BPTR pSrc);
    FMSTR_BPTR FMSTR_AddressToBuffer(FMSTR_BPTR pDest, FMSTR_ADDR nAddr);


#line 178 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"







 

 





 

 




 

#line 216 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"



 

 
#line 230 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 
#line 248 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 
#line 261 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"



 

 



 





 



 



 


 


 


 




 

 








 
#line 317 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 
#line 332 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 





 


 
#line 355 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 
#line 363 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 




 


 





 
#line 386 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 
#line 394 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 



 
typedef struct
{
    FMSTR_U8 nDataIx;
} FMSTR_FCAN_TCTX;

 




 






 





 





 


 



 
typedef struct
{
    FMSTR_U8 nDataIx;
} FMSTR_FCAN_RCTX;

 



 
#line 453 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 



 




 





#line 138 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"












 







 











 

#line 178 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"







 


 




 





 

void FMSTR_InitSerial(void);
FMSTR_BOOL FMSTR_InitMQX(void);
void FMSTR_SendResponse(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nLength);
void FMSTR_ProcessSCI(void);
void FMSTR_ProcessJTAG(void);

FMSTR_BOOL FMSTR_ProtocolDecoder(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetBoardInfo(FMSTR_BPTR pMessageIO);

FMSTR_BPTR FMSTR_ReadMem(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_ReadVar(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_WriteMem(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_WriteVar(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_WriteVarMask(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_WriteMemMask(FMSTR_BPTR pMessageIO);

void FMSTR_InitAppCmds(void);
FMSTR_BPTR FMSTR_StoreAppCmd(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetAppCmdStatus(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetAppCmdRespData(FMSTR_BPTR pMessageIO);

void FMSTR_InitScope(void);
FMSTR_BPTR FMSTR_SetUpScope(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_ReadScope(FMSTR_BPTR pMessageIO);

void FMSTR_InitRec(void);
FMSTR_BPTR FMSTR_SetUpRec(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_StartRec(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_StopRec(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetRecStatus(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetRecBuff(FMSTR_BPTR pMessageIO);
FMSTR_BOOL FMSTR_IsInRecBuffer(FMSTR_ADDR nAddr, FMSTR_SIZE8 nSize);
FMSTR_SIZE FMSTR_GetRecBuffSize(void);

void FMSTR_InitTsa(void);
FMSTR_BPTR FMSTR_GetTsaInfo(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetStringLen(FMSTR_BPTR pMessageIO);
FMSTR_BOOL FMSTR_CheckTsaSpace(FMSTR_ADDR nAddr, FMSTR_SIZE8 nSize, FMSTR_BOOL bWriteAccess);
FMSTR_U16  FMSTR_StrLen(FMSTR_ADDR nAddr);

void FMSTR_InitSfio(void);
FMSTR_BPTR FMSTR_SfioFrame(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_SfioGetResp(FMSTR_BPTR pMessageIO);

void FMSTR_InitPipes(void);
FMSTR_BPTR FMSTR_PipeFrame(FMSTR_BPTR pMessageIO);

void FMSTR_InitCan(void);
void FMSTR_SetCanCmdID(FMSTR_U32 canID);
void FMSTR_SetCanRespID(FMSTR_U32 canID);
FMSTR_BOOL FMSTR_TxCan(void);
FMSTR_BOOL FMSTR_RxCan(void);
void FMSTR_ProcessCanRx(void);
void FMSTR_ProcessCanTx(void);



 









 

 






 
#line 287 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 295 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 311 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 
 












#line 333 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"





 
#line 346 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 




 
 








    






 
#line 439 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 
#line 471 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 481 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 
#line 492 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 
#line 503 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 








 






 




















 




 




 




 




 




 




    
     



    
     









 






 












 














 




 
#line 642 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 




 




 




#line 695 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 


         
#line 706 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 
#line 715 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 




 
#line 759 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"
     



     





     





     





     





     
#line 794 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"
    
     
#line 802 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"
    




#line 21 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.c"
#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"






 









 






 
  
#line 42 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"



 
  
 
#line 59 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"

 






 
#line 75 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"

 





 

 



  
 




 
#line 110 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"



 







 


 






 

 
#line 140 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"

 






#line 22 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.c"



#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.h"






 









 








#line 27 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.h"
#line 28 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.h"



 

 
typedef volatile union 
{
    FMSTR_FLAGS all;
    
    struct 
    {
        unsigned bIsConfigured : 1;      
        unsigned bIsRunning : 1;         
        unsigned bIsStopping : 1;        
        unsigned bInvirginCycle : 1;     
        unsigned bTrgCrossActive : 1;    
    } flg;
    
} FMSTR_REC_FLAGS;

 
#line 57 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.h"



 

 
extern FMSTR_U16  pcm_wRecTotalSmps;         
extern FMSTR_U16  pcm_wRecPostTrigger;       
extern FMSTR_U8   pcm_nRecTriggerMode;       
extern FMSTR_U16  pcm_wRecTimeDiv;           

extern FMSTR_U8    pcm_nRecVarCount;         
extern FMSTR_ADDR  pcm_pRecVarAddr[8];  
extern FMSTR_SIZE8 pcm_pRecVarSize[8];  

 
extern FMSTR_U16  pcm_wRecBuffStartIx;       

extern FMSTR_ADDR pcm_dwRecWritePtr;         
extern FMSTR_ADDR pcm_dwRecEndBuffPtr;       
extern FMSTR_U16  pcm_wRecTimeDivCtr;        
extern FMSTR_U16  pcm_wStoprecCountDown;     

extern FMSTR_REC_FLAGS pcm_wRecFlags;


#line 26 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.c"







 

 
FMSTR_U16  pcm_wRecTotalSmps;         


FMSTR_U16  pcm_wRecPostTrigger;       



FMSTR_U8   pcm_nRecTriggerMode;       



FMSTR_U16  pcm_wRecTimeDiv;           


FMSTR_U8    pcm_nRecVarCount;         
FMSTR_ADDR  pcm_pRecVarAddr[8];  
FMSTR_SIZE8 pcm_pRecVarSize[8];  

 

FMSTR_U16  pcm_wRecTimeDivCtr;        


FMSTR_U16  pcm_wStoprecCountDown;     

 
FMSTR_REC_FLAGS pcm_wRecFlags;



 


FMSTR_U16   pcm_wRecBuffStartIx;      

 
FMSTR_ADDR pcm_dwRecWritePtr;         
FMSTR_ADDR pcm_dwRecEndBuffPtr;       

 
static FMSTR_ADDR pcm_nTrgVarAddr;           
static FMSTR_U8   pcm_nTrgVarSize;           
static FMSTR_U8   pcm_bTrgVarSigned;         

 
static union 
{

    FMSTR_U8  u8; 
    FMSTR_S8  s8;

    FMSTR_U16 u16;
    FMSTR_S16 s16;
    FMSTR_U32 u32;
    FMSTR_S32 s32;
} pcm_uTrgThreshold;                         


static FMSTR_ADDR  pcm_nRecBuffAddr;         
static FMSTR_SIZE  pcm_wRecBuffSize;         

 
typedef FMSTR_BOOL (*FMSTR_PCOMPAREFUNC)(void);

 
static FMSTR_PCOMPAREFUNC pcm_pCompareFunc;


 



 
static FMSTR_U8 pcm_pOwnRecBuffer[1024];
 







 

static FMSTR_BOOL FMSTR_Compare8S(void);
static FMSTR_BOOL FMSTR_Compare8U(void);
static FMSTR_BOOL FMSTR_Compare16S(void);
static FMSTR_BOOL FMSTR_Compare16U(void);
static FMSTR_BOOL FMSTR_Compare32S(void);
static FMSTR_BOOL FMSTR_Compare32U(void);
static void FMSTR_Recorder2(void);

 



 

void FMSTR_InitRec(void)
{   
     
    pcm_wRecFlags.all = 0U;

    
 
    
#line 150 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.c"
     
    pcm_wRecBuffSize = (FMSTR_SIZE) 1024;
    ( pcm_nRecBuffAddr = (FMSTR_ADDR) (FMSTR_U8*) pcm_pOwnRecBuffer );
    
     


}

 



 




inline

void FMSTR_AbortRec(void)
{
     
    pcm_wRecFlags.all = 0U;
}

 








 

void FMSTR_SetUpRecBuff(FMSTR_ADDR pBuffer, FMSTR_SIZE nBuffSize)
{    
    pcm_nRecBuffAddr = pBuffer;
    pcm_wRecBuffSize = nBuffSize;
}

 








 

FMSTR_BPTR FMSTR_SetUpRec(FMSTR_BPTR pMessageIO)
{
    FMSTR_BPTR pResponse = pMessageIO;
    FMSTR_SIZE8 nRecVarsetSize;
    FMSTR_SIZE blen;
    FMSTR_U8 i, sz;
    FMSTR_U8 nResponseCode;
    
     
    FMSTR_AbortRec();

#line 222 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.c"
     
    pcm_wRecBuffSize = (FMSTR_SIZE)1024;
    ( pcm_nRecBuffAddr = (FMSTR_ADDR) (FMSTR_U8*) pcm_pOwnRecBuffer );


     

    pMessageIO = ( ((FMSTR_BPTR)(pMessageIO)) + (2U) );
    pMessageIO = ( (*((FMSTR_U8*)(&pcm_nRecTriggerMode)) = *(FMSTR_U8*)(pMessageIO)), (((FMSTR_BPTR)(pMessageIO))+1) );




    pMessageIO = FMSTR_ValueFromBuffer16(&pcm_wRecTotalSmps, pMessageIO);


    pMessageIO = FMSTR_ValueFromBuffer16(&pcm_wRecPostTrigger, pMessageIO);





    pMessageIO = FMSTR_ValueFromBuffer16(&pcm_wRecTimeDiv, pMessageIO);





     
    pMessageIO = FMSTR_AddressFromBuffer(&pcm_nTrgVarAddr, pMessageIO);
    pMessageIO = ( (*((FMSTR_U8*)(&pcm_nTrgVarSize)) = *(FMSTR_U8*)(pMessageIO)), (((FMSTR_BPTR)(pMessageIO))+1) );

     
    pMessageIO = ( (*((FMSTR_U8*)(&pcm_bTrgVarSigned)) = *(FMSTR_U8*)(pMessageIO)), (((FMSTR_BPTR)(pMessageIO))+1) );

     
    pMessageIO = FMSTR_ValueFromBuffer32(&pcm_uTrgThreshold.u32, pMessageIO);



    
     
    pMessageIO = ( (*((FMSTR_U8*)(&pcm_nRecVarCount)) = *(FMSTR_U8*)(pMessageIO)), (((FMSTR_BPTR)(pMessageIO))+1) );

     
    if(!pcm_nRecVarCount || pcm_nRecVarCount > (FMSTR_U8)8)
    {



        nResponseCode = 0x85U;
        goto FMSTR_SetUpRec_exit;

    }

     
    nRecVarsetSize = 0U;

     
    for(i=0U; i<pcm_nRecVarCount; i++)
    {
         
        pMessageIO = ( (*((FMSTR_U8*)(&sz)) = *(FMSTR_U8*)(pMessageIO)), (((FMSTR_BPTR)(pMessageIO))+1) );
        
        pcm_pRecVarSize[i] = sz;
        nRecVarsetSize += sz;
        
         
        pMessageIO = FMSTR_AddressFromBuffer(&pcm_pRecVarAddr[i], pMessageIO);

         
        if(sz == 0U || sz > 8U)
        {



            nResponseCode = 0x86U;
            goto FMSTR_SetUpRec_exit;

        }

#line 315 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.c"
        
#line 327 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.c"
    }

     

     
    pcm_pCompareFunc = ((void *) 0);
    if(pcm_nRecTriggerMode)
    {
         
#line 347 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.c"
         
        switch(pcm_nTrgVarSize)
        {

        case 1: pcm_pCompareFunc = pcm_bTrgVarSigned ? FMSTR_Compare8S : FMSTR_Compare8U; break;

        case 2: pcm_pCompareFunc = pcm_bTrgVarSigned ? FMSTR_Compare16S : FMSTR_Compare16U; break;
        case 4: pcm_pCompareFunc = pcm_bTrgVarSigned ? FMSTR_Compare32S : FMSTR_Compare32U; break;
        
         
        default:



            nResponseCode = 0x86U;
            goto FMSTR_SetUpRec_exit;

        }
    }

    
     
    blen = (FMSTR_SIZE) (pcm_wRecTotalSmps * nRecVarsetSize / 1);

     
    if(blen > FMSTR_GetRecBuffSize())
    {



        nResponseCode = 0x86U;
        goto FMSTR_SetUpRec_exit;

    }


     
    pcm_dwRecEndBuffPtr = pcm_nRecBuffAddr + blen;


#line 398 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.c"

     
    pcm_wRecFlags.flg.bIsConfigured = 1U;
    nResponseCode = 0x00U;





FMSTR_SetUpRec_exit:
    return ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)(nResponseCode)), (((FMSTR_BPTR)(pResponse))+1) );
}

 





 

void FMSTR_TriggerRec(void)
{
    if(!pcm_wRecFlags.flg.bIsStopping)
    {
        pcm_wRecFlags.flg.bIsStopping = 1U;

        pcm_wStoprecCountDown = pcm_wRecPostTrigger;



    }
}

 











 

FMSTR_BPTR FMSTR_StartRec(FMSTR_BPTR pMessageIO)
{
     FMSTR_U8 nResponseCode;   
     
    if(!pcm_wRecFlags.flg.bIsConfigured)
    {



        nResponseCode = 0x88U;
        goto FMSTR_StartRec_exit;

    }
        
     
    if(pcm_wRecFlags.flg.bIsRunning)
    {



        nResponseCode = 0x01U;
        goto FMSTR_StartRec_exit;

    }


     
    pcm_dwRecWritePtr = pcm_nRecBuffAddr;

     
    pcm_wRecBuffStartIx = 0U;


     

    pcm_wRecTimeDivCtr = 0U;


     
    pcm_wRecFlags.flg.bIsStopping = 0U;           
    pcm_wRecFlags.flg.bTrgCrossActive = 0U;       
    pcm_wRecFlags.flg.bInvirginCycle = 1U;        
     

     




     
    pcm_wRecFlags.flg.bIsRunning = 1U;            

    nResponseCode = 0x00U;






FMSTR_StartRec_exit:
    return ( (*((FMSTR_U8*)(pMessageIO)) = (FMSTR_U8)(nResponseCode)), (((FMSTR_BPTR)(pMessageIO))+1) );
}

 










 

FMSTR_BPTR FMSTR_StopRec(FMSTR_BPTR pMessageIO)
{
    FMSTR_U8 nResponseCode;
     
    if(!pcm_wRecFlags.flg.bIsConfigured)
    {
        nResponseCode = 0x88U;
        goto FMSTR_StopRec_exit;
    }
        
     
    if(!pcm_wRecFlags.flg.bIsRunning)
    {
        nResponseCode = 0x02U;
        goto FMSTR_StopRec_exit;
    }
    
     
    FMSTR_TriggerRec();
    nResponseCode = 0x00U;
    
FMSTR_StopRec_exit:
    return ( (*((FMSTR_U8*)(pMessageIO)) = (FMSTR_U8)(nResponseCode)), (((FMSTR_BPTR)(pMessageIO))+1) );
}

 










 

FMSTR_BPTR FMSTR_GetRecStatus(FMSTR_BPTR pMessageIO)
{
    FMSTR_U16 nResponseCode = (FMSTR_U16) (pcm_wRecFlags.flg.bIsRunning ? 
        0x01U : 0x02U);
    
     
    if(!pcm_wRecFlags.flg.bIsConfigured)
    {
        nResponseCode = 0x88U;
    }
        
     
    return ( (*((FMSTR_U8*)(pMessageIO)) = (FMSTR_U8)((FMSTR_U8) nResponseCode)), (((FMSTR_BPTR)(pMessageIO))+1) );
}

 


 





 

FMSTR_SIZE FMSTR_GetRecBuffSize()
{



    return (FMSTR_SIZE) 1024;

}

 











 

FMSTR_BOOL FMSTR_IsInRecBuffer(FMSTR_ADDR dwAddr, FMSTR_SIZE8 nSize)
{
    FMSTR_BOOL bRet = 0U;
    
    if(dwAddr >= pcm_nRecBuffAddr)
    {
        bRet = (FMSTR_BOOL)((dwAddr + nSize) <= (pcm_nRecBuffAddr + FMSTR_GetRecBuffSize()) ? (1U) : (0U));    
    }
    
    return bRet;
}


 










 

FMSTR_BPTR FMSTR_GetRecBuff(FMSTR_BPTR pMessageIO)
{
     
    if(!pcm_wRecFlags.flg.bIsConfigured)
    {
        return ( (*((FMSTR_U8*)(pMessageIO)) = (FMSTR_U8)(0x88U)), (((FMSTR_BPTR)(pMessageIO))+1) );
    }
    
     
    if(pcm_wRecFlags.flg.bIsRunning)
    {
        return ( (*((FMSTR_U8*)(pMessageIO)) = (FMSTR_U8)(0x87U)), (((FMSTR_BPTR)(pMessageIO))+1) );
    }
    
     
    pMessageIO = ( (*((FMSTR_U8*)(pMessageIO)) = (FMSTR_U8)(0x00U)), (((FMSTR_BPTR)(pMessageIO))+1) );
    pMessageIO = FMSTR_AddressToBuffer(pMessageIO, pcm_nRecBuffAddr);
    return FMSTR_ValueToBuffer16(pMessageIO, pcm_wRecBuffStartIx);
}

 









 





static FMSTR_BOOL FMSTR_Compare8S()
{
    return ((FMSTR_BOOL)(((( *(FMSTR_S8*)(pcm_nTrgVarAddr) )) < (pcm_uTrgThreshold . s8)) ? 0 : 1));
}

static FMSTR_BOOL FMSTR_Compare8U()
{
    return ((FMSTR_BOOL)(((( *(FMSTR_U8*)(pcm_nTrgVarAddr) )) < (pcm_uTrgThreshold . u8)) ? 0 : 1));
}



static FMSTR_BOOL FMSTR_Compare16S()
{
    return ((FMSTR_BOOL)(((( *(FMSTR_S16*)(pcm_nTrgVarAddr) )) < (pcm_uTrgThreshold . s16)) ? 0 : 1));
}

static FMSTR_BOOL FMSTR_Compare16U()
{
    return ((FMSTR_BOOL)(((( *(FMSTR_U16*)(pcm_nTrgVarAddr) )) < (pcm_uTrgThreshold . u16)) ? 0 : 1));
}

static FMSTR_BOOL FMSTR_Compare32S()
{
    return ((FMSTR_BOOL)(((( *(FMSTR_S32*)(pcm_nTrgVarAddr) )) < (pcm_uTrgThreshold . s32)) ? 0 : 1));
}

static FMSTR_BOOL FMSTR_Compare32U()
{
    return ((FMSTR_BOOL)(((( *(FMSTR_U32*)(pcm_nTrgVarAddr) )) < (pcm_uTrgThreshold . u32)) ? 0 : 1));
}

 







 





void FMSTR_Recorder(void)
{
     
    if(!pcm_wRecFlags.flg.bIsRunning)
    {
        return ;
    }
    
     
    FMSTR_Recorder2();
}

 



 





static void FMSTR_Recorder2(void)
{
    FMSTR_SIZE8 sz;
    FMSTR_BOOL cmp;
    FMSTR_U8 i;


     
    if(pcm_wRecTimeDivCtr)
    {
         
        pcm_wRecTimeDivCtr--;
        return;
    }
    
     

    pcm_wRecTimeDivCtr = pcm_wRecTimeDiv;





     
    for (i=0U; i<pcm_nRecVarCount; i++)
    {
        sz = pcm_pRecVarSize[i];
        FMSTR_CopyMemory(pcm_dwRecWritePtr, pcm_pRecVarAddr[i], sz);
        sz /= 1;
        pcm_dwRecWritePtr += sz;
    }
    
     
     
    pcm_wRecBuffStartIx++;
    
     
    if(pcm_dwRecWritePtr >= pcm_dwRecEndBuffPtr)
    {   
        pcm_dwRecWritePtr = pcm_nRecBuffAddr;
        pcm_wRecFlags.flg.bInvirginCycle = 0U;
        pcm_wRecBuffStartIx = 0U;
    }

     
    if(pcm_wRecFlags.flg.bInvirginCycle)
    {
        return;
    }
    
     
    if(!pcm_wRecFlags.flg.bIsStopping && pcm_pCompareFunc != ((void *) 0))
    {
         
        cmp = pcm_pCompareFunc();
        
         
        if(pcm_nRecTriggerMode == 2U)
        {
            cmp = (FMSTR_BOOL) !cmp;
        }
        
         
        if(cmp)
        {
             
            if(pcm_wRecFlags.flg.bTrgCrossActive)
            {
                 
                FMSTR_TriggerRec();
            }
        }
        else
        {
             
            pcm_wRecFlags.flg.bTrgCrossActive = 1U;
        }
    }
    
     
    if(pcm_wRecFlags.flg.bIsStopping)
    {
         
        if(!pcm_wStoprecCountDown)
        {
             
            pcm_wRecFlags.flg.bIsRunning = 0U;
            return;
        }
        
         
        pcm_wStoprecCountDown--;
    }
}



#line 856 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_rec.c"


