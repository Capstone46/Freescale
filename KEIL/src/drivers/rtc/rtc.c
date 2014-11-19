/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      rtc.c
 * @version   1.0.3.0
 * @date      Jan-18-2013
 * @brief     Real time clock module driver source code file.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written for Kinetis K
 *  2.	17/01/2013   B34185   Ported to Kinetis L
 ******************************************************************************/
#include "common.h"
#include "rtc.h"

/******************************************************************************
 * VBAT register file definitionn                                             *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	__root __no_init volatile uint8 VbatRegisterFile[32] @ 0x4003E000;
#elif defined(__ARMCC_VERSION)
	volatile uint8 VbatRegisterFile[32] __attribute__((section(".vbatregfile"))) __attribute__((used));
#endif


/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static RTC_CALLBACK volatile pCallbackRTC=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void rtc_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
/***************************************************************************//*!
 * @brief   RTC initialization function.
 * @param   rtc      - RTC module configuration structure passed by value: 
 *                     RTC_MODULE_CONFIG
 * @param   seconds  - number of seconds to initialize seconds register (TSR)
 * @param   ip       - interrupt priority 0..15
 * @param   pCallback- pointer to RTC_CALLBACK function
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
void RTC_Init (tRTC rtc, uint32 seconds, uint8 ip, RTC_CALLBACK pCallback)
{
  if (pCallback != NULL) 
  { 
    pCallbackRTC = pCallback;
    if (rtc.IER&RTC_IER_TSIE_MASK)
    {
      NVIC_SetIsr(INT_RTC_Seconds,ip);
    }
    else
    {
      NVIC_SetIsr(INT_RTC,ip);
    }
  }
  else
  {
    NVIC_ClrIsr(INT_RTC);
    NVIC_ClrIsr(INT_RTC_Seconds);
  }
  // clear lock before configuration
  RTC_LR |= RTC_LR_LRL_MASK;
  RTC_LR |= RTC_LR_SRL_MASK|RTC_LR_CRL_MASK|RTC_LR_TCL_MASK;
  /* run soft reset sequence only if clock doesn't run                        */
  if (!(RTC_SR & RTC_SR_TCE_MASK)) 
  { 
    RTC_CR|= RTC_CR_SWR_MASK; 
    RTC_CR&=~RTC_CR_SWR_MASK; 
  }
  RTC_CR  = rtc.CR;
  if(rtc.SR & RTC_SR_TCE_MASK)
  {
    RTC_SR  &= ~RTC_SR_TCE_MASK;
    if(rtc.CR & RTC_CR_OSCE_MASK) 
      arch_delay(1000l);         /* wait 125ms                                */    
  }
  RTC_TSR = seconds;            /* if clock runs seconds cannot be updated    */
  RTC_TCR = rtc.TCR;
  RTC_TAR = rtc.TAR;
  RTC_IER = rtc.IER;
  RTC_SR  = rtc.SR;
  RTC_LR  = rtc.LR;
}

#define YEAR0           1970 
#define EPOCH_YR        1970
#define LONG_MAX        2147483647l
#define TIME_MAX        4294967296l
#define SECS_DAY        (24l * 60l * 60l)
#define LEAPYEAR(year)  (!((year) % 4) && (((year) % 100) || !((year) % 400))) 
#define YEARSIZE(year)  (LEAPYEAR(year) ? 366 : 365)
static const int16 _ytab[2][12] = 
{
  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
  { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};
/***************************************************************************//*!
 * @brief   Converts calendar time to number of seconds.
 * @param   timep   - pointer to calendar structure
 * @return  number of seconds
 * @note    Implemented as function call.
 ******************************************************************************/
uint32 RTC_MkTime (tTIME *timep)
/* Courtesy of: http://www.raspberryginger.com/jbailey/minix/html/gmtime_8c.html*/ 
{
  register int32  day, year;
  register int16  tm_year, yday, month, overflow;
  register uint32 seconds;
  
  timep->tm_min += timep->tm_sec / 60; 
  timep->tm_sec %= 60;
  if (timep->tm_sec < 0) { timep->tm_sec += 60; timep->tm_min--; }
  timep->tm_hour += timep->tm_min / 60;
  timep->tm_min = timep->tm_min % 60;
  if (timep->tm_min < 0) { timep->tm_min += 60; timep->tm_hour--; }
  day = timep->tm_hour / 24;
  timep->tm_hour= timep->tm_hour % 24;
  if (timep->tm_hour < 0) { timep->tm_hour += 24; day--; }
  timep->tm_year += timep->tm_mon / 12;
  timep->tm_mon %= 12;
  if (timep->tm_mon < 0) { timep->tm_mon += 12; timep->tm_year--; }
  day += (timep->tm_mday - 1);
  while (day < 0) 
  {
    if(--timep->tm_mon < 0) { timep->tm_year--; timep->tm_mon = 11; }  
    day += _ytab[LEAPYEAR(YEAR0 + timep->tm_year)][timep->tm_mon];
  }
  while (day >= _ytab[LEAPYEAR(YEAR0 + timep->tm_year)][timep->tm_mon]) 
  {
    day -= _ytab[LEAPYEAR(YEAR0 + timep->tm_year)][timep->tm_mon];
    if (++(timep->tm_mon) == 12) { timep->tm_mon = 0; timep->tm_year++; }
  }
  timep->tm_mday = day + 1;
  year = EPOCH_YR;
  seconds = 0;
  day = 0;                        /* means days since day 0 now */
  overflow = 0;
  tm_year = timep->tm_year;
  if (LONG_MAX / 365 < tm_year - year) overflow++;
  day = (tm_year - year) * 365;
  if (LONG_MAX - day < (tm_year - year) / 4 + 1) overflow++;
  day += (tm_year - year) / 4 + ((tm_year % 4) && tm_year % 4 < year % 4);
  day -= (tm_year - year) / 100 + ((tm_year % 100) && tm_year % 100 < year % 100);
  day += (tm_year - year) / 400 + ((tm_year % 400) && tm_year % 400 < year % 400);
  yday = month = 0;
  while (month < timep->tm_mon){ yday += _ytab[LEAPYEAR(tm_year)][month]; month++; }
  yday += (timep->tm_mday - 1);
  if (day + yday < 0) overflow++;
  day += yday;
  timep->tm_yday = yday;
  timep->tm_wday = (day + 4) % 7;         /* day 0 was thursday (4) */
  seconds = ((timep->tm_hour * 60L) + timep->tm_min) * 60L + timep->tm_sec;
  if ((TIME_MAX - seconds) / SECS_DAY < day) overflow++;
  seconds += day * SECS_DAY;
  
  return seconds;
}

/***************************************************************************//*!
 * @brief   Converts number of seconds to calendar time.
 * @param   numSeconds - number of seconds
 * @param   timep      - pointer to calendar time
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
void RTC_GmTime (uint32 numSeconds, tTIME *timep)
/* Courtesy of: http://www.raspberryginger.com/jbailey/minix/html/gmtime_8c.html*/ 
{
  register uint32 dayclock, dayno;
  register int16  year = EPOCH_YR;
  
  dayclock = (uint32)numSeconds % SECS_DAY;
  dayno = (uint32)numSeconds / SECS_DAY;
  timep->tm_sec = dayclock % 60;
  timep->tm_min = (dayclock % 3600) / 60;
  timep->tm_hour = dayclock / 3600;
  timep->tm_wday = (dayno + 4) % 7;       /* day 0 was a thursday */
  while (dayno >= YEARSIZE(year)) { dayno -= YEARSIZE(year); year++; }
  timep->tm_year = year;
  timep->tm_yday = dayno;
  timep->tm_mon = 0;
  while (dayno >= _ytab[LEAPYEAR(year)][timep->tm_mon]) 
  {
    dayno -= _ytab[LEAPYEAR(year)][timep->tm_mon];
    timep->tm_mon++;
  }
  timep->tm_mday = dayno + 1;
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void rtc_isr (void) 
{  
  if (pCallbackRTC != (RTC_CALLBACK)NULL)
  {
    if (RTC_SR & RTC_SR_TAF_MASK) { /* set alarm */ pCallbackRTC(TAF_CALLBACK); }
    if (RTC_SR & RTC_SR_TOF_MASK) { RTC_SetTime(0); pCallbackRTC(TOF_CALLBACK); }
    if (RTC_SR & RTC_SR_TIF_MASK) { RTC_SetTime(0); pCallbackRTC(TIF_CALLBACK); }
    if (__get_IPSR() == INT_RTC_Seconds) 
    { 
      pCallbackRTC(TSF_CALLBACK); 
    }
  }
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
