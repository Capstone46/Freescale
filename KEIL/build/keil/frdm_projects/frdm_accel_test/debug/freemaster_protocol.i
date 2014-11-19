#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"






 














 

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



#line 25 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"
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
    




#line 26 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"
#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"






 









 






 
  
#line 42 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"



 
  
 
#line 59 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"

 






 
#line 75 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"

 





 

 



  
 




 
#line 110 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"



 







 


 






 

 
#line 140 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"

 






#line 27 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"

 



 

FMSTR_BOOL FMSTR_Init(void)
{   






     
    FMSTR_InitScope();



     
    FMSTR_InitRec();


















     
    FMSTR_InitSerial();












return (1U);
}

 











 

FMSTR_BOOL FMSTR_ProtocolDecoder(FMSTR_BPTR pMessageIO)
{
    FMSTR_BPTR pResponseEnd;
    FMSTR_U8 nCmd;
    
     
    FMSTR_SetExAddr((0U));
    
     
     
    ( (*((FMSTR_U8*)(&nCmd)) = *(FMSTR_U8*)(pMessageIO)), (((FMSTR_BPTR)(pMessageIO))+1) );

     
    switch (nCmd)
    {
    
#line 152 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"



         

        case 0x04U:
            FMSTR_SetExAddr((1U));





            pResponseEnd = FMSTR_ReadMem(pMessageIO);
            break;
            




         

        case 0x0aU:
            FMSTR_SetExAddr((1U));





            pResponseEnd = FMSTR_SetUpScope(pMessageIO);
            break;  
            
        case 0xc5U:
            pResponseEnd = FMSTR_ReadScope(pMessageIO);
            break;




         
        case 0xc3U:
            pResponseEnd = FMSTR_GetRecStatus(pMessageIO);
            break;

         
        case 0xc1U:
            pResponseEnd = FMSTR_StartRec(pMessageIO);
            break;

         
        case 0xc2U:
            pResponseEnd = FMSTR_StopRec(pMessageIO);
            break;

         

        case 0x0bU:                 
            FMSTR_SetExAddr((1U));





            pResponseEnd = FMSTR_SetUpRec(pMessageIO);
            break;
            
         

        case 0xc9U:
            FMSTR_SetExAddr((1U));




            pResponseEnd = FMSTR_GetRecBuff(pMessageIO);
            break; 

 
#line 246 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"



         

        case 0x05U:
            FMSTR_SetExAddr((1U));





            pResponseEnd = FMSTR_WriteMem(pMessageIO);
            break;




         

        case 0x06U:
            FMSTR_SetExAddr((1U));





            pResponseEnd = FMSTR_WriteMemMask(pMessageIO);
            break;

            
#line 294 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"

#line 308 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"

#line 334 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"





         
        case 0xc0U: 

            pResponseEnd = FMSTR_GetBoardInfo(pMessageIO);
            break;

#line 355 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"







         
        default:
            pResponseEnd = ( (*((FMSTR_U8*)(pMessageIO)) = (FMSTR_U8)(0x81U)), (((FMSTR_BPTR)(pMessageIO))+1) );
            break;          
    }
    
     
    if(pResponseEnd != pMessageIO)
    {
         
        FMSTR_SIZE8 nSize = (FMSTR_SIZE8)(pResponseEnd - pMessageIO);
        FMSTR_SendResponse(pMessageIO, nSize);
        return (1U);
    }
    else
    {
         
        return (0U);
    }
}

 








 

FMSTR_BPTR FMSTR_GetBoardInfo(FMSTR_BPTR pMessageIO)
{
    FMSTR_BPTR pResponse = pMessageIO;
    FMSTR_U16 wTmp;
    FMSTR_U8 *pStr;

    pResponse = ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)(0x00U)), (((FMSTR_BPTR)(pResponse))+1) );              
    pResponse = ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)((FMSTR_U8)(3))), (((FMSTR_BPTR)(pResponse))+1) );             
    pResponse = ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)((FMSTR_U8)(0))), (((FMSTR_BPTR)(pResponse))+1) );            
    pResponse = ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)((FMSTR_U8)(1))), (((FMSTR_BPTR)(pResponse))+1) );        
    pResponse = ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)((FMSTR_U8)(2))), (((FMSTR_BPTR)(pResponse))+1) );   
    pResponse = ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)((FMSTR_U8)(0))), (((FMSTR_BPTR)(pResponse))+1) );   
    pResponse = ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)((FMSTR_U8)(((8)*5+18)))), (((FMSTR_BPTR)(pResponse))+1) );     

     








     
    wTmp = FMSTR_GetRecBuffSize();
    wTmp *= 1;

     
    pResponse = FMSTR_ValueToBuffer16(pResponse, wTmp);
    pResponse = FMSTR_ValueToBuffer16(pResponse, (FMSTR_U16) (((0) & 0x3fff) | 0x4000));
#line 432 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"





     
    pStr = (FMSTR_U8*)  "Kxx FreeMASTER";
    for(wTmp = 0U; wTmp < (FMSTR_U8)(25U); wTmp++)
    {
        pResponse = ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)(*pStr)), (((FMSTR_BPTR)(pResponse))+1) );

                 
        if(*pStr)
        {
            pStr ++;
        }
    }

    


    return pResponse;   
}

 








 

FMSTR_BPTR FMSTR_ReadMem(FMSTR_BPTR pMessageIO)
{
    FMSTR_BPTR pResponse = pMessageIO;
    FMSTR_ADDR nAddr;
    FMSTR_U8 nSize;

    pMessageIO = ( ((FMSTR_BPTR)(pMessageIO)) + (2U) );
    pMessageIO = ( (*((FMSTR_U8*)(&nSize)) = *(FMSTR_U8*)(pMessageIO)), (((FMSTR_BPTR)(pMessageIO))+1) );
    pMessageIO = FMSTR_AddressFromBuffer(&nAddr, pMessageIO);

#line 483 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"

     
    if(nSize > (FMSTR_U8)((8)*5+18))
    {
        return ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)(0x84U)), (((FMSTR_BPTR)(pResponse))+1) );
    }
    
     
    pResponse = ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)(0x00U)), (((FMSTR_BPTR)(pResponse))+1) );
    
    return FMSTR_CopyToBuffer(pResponse, nAddr, (FMSTR_SIZE8) nSize);
}   

 








 

FMSTR_BPTR FMSTR_ReadVar(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nSize)
{
    FMSTR_BPTR pResponse = pMessageIO;
    FMSTR_ADDR nAddr;

    pMessageIO = ( ((FMSTR_BPTR)(pMessageIO)) + (1U) );
    pMessageIO = FMSTR_AddressFromBuffer(&nAddr, pMessageIO);

#line 521 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"

     
    pResponse = ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)(0x00U)), (((FMSTR_BPTR)(pResponse))+1) );
    
    return FMSTR_CopyToBuffer(pResponse, nAddr, nSize);
}   

 








 

FMSTR_BPTR FMSTR_WriteMem(FMSTR_BPTR pMessageIO)
{
    FMSTR_BPTR pResponse = pMessageIO;
    FMSTR_ADDR nAddr;
    FMSTR_U8 nSize,nResponseCode;

    pMessageIO = ( ((FMSTR_BPTR)(pMessageIO)) + (2U) );
    pMessageIO = ( (*((FMSTR_U8*)(&nSize)) = *(FMSTR_U8*)(pMessageIO)), (((FMSTR_BPTR)(pMessageIO))+1) );
    pMessageIO = FMSTR_AddressFromBuffer(&nAddr, pMessageIO);

#line 556 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"

     
    FMSTR_CopyFromBuffer(nAddr, pMessageIO, (FMSTR_SIZE8) nSize);
    nResponseCode = 0x00U;

FMSTR_WriteMem_exit:
    return ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)(nResponseCode)), (((FMSTR_BPTR)(pResponse))+1) );
}

 









 

FMSTR_BPTR FMSTR_WriteVar(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nSize)
{
    FMSTR_BPTR pResponse = pMessageIO;
    FMSTR_ADDR nAddr;
    FMSTR_U8 nResponseCode;

    pMessageIO = ( ((FMSTR_BPTR)(pMessageIO)) + (1U) );
    pMessageIO = FMSTR_AddressFromBuffer(&nAddr, pMessageIO);

#line 593 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"

     
    FMSTR_CopyFromBuffer(nAddr, pMessageIO, nSize);
    nResponseCode = 0x00U;

FMSTR_WriteVar_exit:
    return ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)(nResponseCode)), (((FMSTR_BPTR)(pResponse))+1) );
}


 








 

FMSTR_BPTR FMSTR_WriteMemMask(FMSTR_BPTR pMessageIO)
{
    FMSTR_BPTR pResponse = pMessageIO;
    FMSTR_ADDR nAddr;
    FMSTR_U8 nSize,nResponseCode;

    pMessageIO = ( ((FMSTR_BPTR)(pMessageIO)) + (2U) );
    pMessageIO = ( (*((FMSTR_U8*)(&nSize)) = *(FMSTR_U8*)(pMessageIO)), (((FMSTR_BPTR)(pMessageIO))+1) );
    pMessageIO = FMSTR_AddressFromBuffer(&nAddr, pMessageIO);

#line 631 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"

#line 640 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"

     
    FMSTR_CopyFromBufferWithMask(nAddr, pMessageIO, (FMSTR_SIZE8)nSize);
    nResponseCode = 0x00U;

FMSTR_WriteMemMask_exit:
    return ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)(nResponseCode)), (((FMSTR_BPTR)(pResponse))+1) );
}

 









 

FMSTR_BPTR FMSTR_WriteVarMask(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nSize)
{
    FMSTR_BPTR pResponse = pMessageIO;
    FMSTR_ADDR nAddr;
    FMSTR_U8 nResponseCode;
    
    pMessageIO = ( ((FMSTR_BPTR)(pMessageIO)) + (1U) );
    pMessageIO = FMSTR_AddressFromBuffer(&nAddr, pMessageIO);

#line 677 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.c"

     
    FMSTR_CopyFromBufferWithMask(nAddr, pMessageIO, nSize);         
    nResponseCode = 0x00U;

FMSTR_WriteVarMask_exit:
    return ( (*((FMSTR_U8*)(pResponse)) = (FMSTR_U8)(nResponseCode)), (((FMSTR_BPTR)(pResponse))+1) );
}


 



 

FMSTR_U16 FMSTR_StrLen(FMSTR_ADDR nAddr)
{
    const FMSTR_U8* pStr;
    FMSTR_U16 nLen = 0U;






     
    pStr = (const FMSTR_U8*) nAddr;
    
    while(*pStr++)
    {
        nLen++;
    }
        
    return nLen;
}

