/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2010 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   mag3110.c
*
* @brief  Driver for magnetometer MAG3110
*
* @version 1.0.5.0
* 
* @date Apr-25-2012
* 
*******************************************************************************/
#include "mag3110.h"

static Byte MAG3110_enabled = FALSE;
static byte invertor = 0;

byte who_i_am, i, status;
byte temperature;

#ifdef  MAG3110_COMPASS 
  /* roll pitch and yaw angles computed by iecompass */
  static sWord iPhi, iThe, iPsi;
    /* magnetic field readings corrected for hard iron effects and PCB orientation */
  static sWord iBfx, iBfy, iBfz;
    /* hard iron estimate */
  static sWord iVx = 0; 
  static sWord iVy = 0; 
  static sWord iVz = 0;
  static sLWord itmp; /* scratch */
  static sWord iTrig(sLWord ix, sLWord iy);
#endif

sWord result;
sWord test1;
sWord test2;



/**************************************************************************//*!
* @brief    The IIC Initialization for MAG3110
*
* @param    mod - current used module for conection
******************************************************************************/
void MAG3110_Init(MODULES mod)
{
  (void)mod;
 /* 
  MA_GPIO0IRQ_INIT;
  MB_GPIO0IRQ_INIT;        
*/     
  MAG3110_SET_SLAVE_ADDRESS;
  MAG3110_WRITE_REGISTER(MAG3110_CTRL_REG1, 0x01);

  who_i_am = MAG3110_READ_REGISTER(MMA3110_WHOIAM);
	
	if(who_i_am == MMA3110_ID)
	  MAG3110_enabled = TRUE;
}  

/**************************************************************************//*!
* @brief    Deintitialization for purposes of module id driver's
******************************************************************************/
void MAG3110_DeInit(void)
{
  MAG3110_SET_SLAVE_ADDRESS;
  MAG3110_WRITE_REGISTER(MAG3110_CTRL_REG1, 0);

  MAG3110_enabled = FALSE;
}

/**************************************************************************//*!
* @brief    Function reads current data from sensor's register 
*
* @param    *mag3110 - pointer to value buffer 
******************************************************************************/
void MAG3110_ReadRawData(TWR_MAG3110* ptr_mag3110) 
{
  static byte latest_write;
  static byte latest_address; 
  byte ix;
  TWR_MAG3110_DATA xyz_regs[6];


  MAG3110_SET_SLAVE_ADDRESS;
  if(MAG3110_enabled == TRUE)
  {
    (void)MAG3110_READ_REGISTERS(MAG3110_OUT_X_MSB,(Byte*)&(xyz_regs[0].Bytes.hi),8);      
    ptr_mag3110->mag_x = ((sWord)xyz_regs[0].all); 
    ptr_mag3110->mag_y = ((sWord)xyz_regs[1].all); 
    ptr_mag3110->mag_z = ((sWord)xyz_regs[2].all);     
  
    for(ix=0; ix < MAG3110_REGS; ix++)
      ptr_mag3110->registers[ix] = MAG3110_READ_REGISTER(ix);  
 
     // write to sensor register R/W 
    if(latest_write != ptr_mag3110->reg_write || latest_address != ptr_mag3110->reg_addr) 
    {
      MAG3110_WRITE_REGISTER(ptr_mag3110->reg_addr, ptr_mag3110->reg_write);
      latest_write = ptr_mag3110->reg_write;
      latest_address = ptr_mag3110->reg_addr;
    }
  }
  else
  {
    ptr_mag3110->mag_x = 0; 
    ptr_mag3110->mag_y = 0; 
    ptr_mag3110->mag_z = 0;     
  
    for(ix=0; ix < MAG3110_REGS; ix++)
      ptr_mag3110->registers[ix] = 0;
  }
}


#ifdef  MAG3110_COMPASS 
/* function to calculate ir = ix / sqrt(ix*ix+iy*iy) using binary division */
static sWord iTrig(sLWord ix, sLWord iy)
{
  sWord t_ix;
  sWord t_iy;
  
  #define MINDELTATRIG 1
  LWord itmp; /* scratch */
  LWord ixsq; /* ix * ix */
  sWord isignx; /* storage for sign of x. algorithm assumes x >= 0 then corrects later */
  LWord ihypsq; /* (ix * ix) + (iy * iy) */
  sWord ir; /* result = ix / sqrt(ix*ix+iy*iy) range -1, 1 returned as signed Int16 */
  sWord idelta; /* delta on candidate result dividing each stage by factor of 2 */
  /* stack variables */
  /* ix, iy: signed 16 bit integers representing sensor reading in range -32768 to 32767 */
  /* function returns signed Int16 as signed fraction (ie +32767=0.99997, -32768=-1.0000) */
  /* algorithm solves for ir*ir*(ix*ix+iy*iy)=ix*ix */

  /* correct for pathological case: ix==iy==0 */
  if ((ix == 0) && (iy == 0)) ix = iy = 1;
  /* check for -32768 which is not handled correctly */
  if (ix == -32768) 
    ix = -32767;
  if (iy == -32768) 
    iy = -32767;
  /* store the sign for later use. algorithm assumes x is positive for convenience */
  isignx = 1;
  if (ix < 0)
  {
    ix = (sLWord)-ix;
    isignx = -1;
  }
  /* for convenience in the boosting set iy to be positive as well as ix */
  iy = (sLWord)(iy & 0x7fff);
  
  /* to reduce quantization effects, boost ix and iy but keep below maximum signed 16 bit */
  while ((ix < 16384) && (iy < 16384))
  {
    t_ix = ix;
    t_iy = iy;
    ix += t_ix;
    iy += t_iy;
  }
  
  /* calculate ix*ix and the hypotenuse squared */
  ixsq = (ix * ix);/* ixsq=ix*ix: 0 to 32767^2 = 1073676289 */
  ihypsq = (LWord)(ixsq + iy * iy);/* ihypsq=(ix*ix+iy*iy) 0 to 2*32767*32767=2147352578 */
  /* set result r to zero and binary search step to 16384 = 0.5 */
  ir = 0;
  idelta = 16384; /* set as 2^14 = 0.5 */
  /* loop over binary sub-division algorithm */
  do
  {
    /* generate new candidate solution for ir and test if we are too high or too low */
    /* itmp=(ir+delta)^2, range 0 to 32767*32767 = 2^30 = 1073676289 */
    itmp = (LWord)((ir + idelta) * (ir + idelta));
    /* itmp=(ir+delta)^2*(ix*ix+iy*iy), range 0 to 2^31 = 2147221516 */
    itmp >>= 15;
    ihypsq >>= 15;
    
    itmp *= ihypsq; 
    
    
    if (itmp <= ixsq) ir += idelta;
    idelta = (sWord)(idelta >> 1); /* divide by 2 using right shift one bit */
  } while (idelta >= MINDELTATRIG); /* last loop is performed for idelta=MINDELTATRIG */
  /* correct the sign before returning */
  
  return (sWord)(ir * isignx);
}

static sWord iDivide(sWord iy, sWord ix)
{
  #define MINDELTADIV  1 /* final step size for iDivide */
  /* function to calculate ir = iy / ix with iy <= ix, and ix, iy both > 0 */

  
  sWord ir; /* result = iy / ix range 0., 1. returned in range 0 to 32767 */
  sWord idelta; /* delta on candidate result dividing each stage by factor of 2 */
  /* set result r to zero and binary search step to 16384 = 0.5 */
  ir = 0;
  idelta = 16384; /* set as 2^14 = 0.5 */
  /* to reduce quantization effects, boost ix and iy to the maximum signed 16 bit value */
  while ((ix < 16384) && (iy < 16384))
  {
    ix = (sWord)(ix + ix);
    iy = (sWord)(iy + iy);
  }
  /* loop over binary sub-division algorithm solving for ir*ix = iy */
  do
  {
    /* generate new candidate solution for ir and test if we are too high or too low */
    itmp = (ir + idelta);
    itmp = ((itmp * ix)>>15);
    
    if (itmp <= iy) 
      ir += idelta;
    
    idelta = (sWord)(idelta >> 1); /* divide by 2 using right shift one bit */
  }while (idelta >= MINDELTADIV); /* last loop is performed for idelta=MINDELTADIV */
  
  return (ir);
}

static sWord iHundredAtanDeg(sWord iy, sWord ix)
{
  /* coefficients of polynomial expansion for atan function */
  #define K1  -14
  #define K2  6113
  #define K3  -1584
  /* calculates 100*atan(iy/ix) range 0 to 9000 for all ix, iy positive in range 0 to 32767 */

  sWord iAngle; /* angle in degrees times 100 */
  sWord iRatio; /* ratio of iy / ix or vice versa */
  sWord iTmp;   /* temporary variable */
  /* check for pathological cases */
  if ((ix == 0) && (iy == 0)) return (0);
  if ((ix == 0) && (iy != 0)) return (9000);
  /* check for non-pathological cases */
  if (iy <= ix)
    iRatio = iDivide(iy, ix); /* return a fraction in range 0. to 32767 = 0. to 1. */
  else
    iRatio = iDivide(ix, iy); /* return a fraction in range 0. to 32767 = 0. to 1. */
  /* polynomial approximation */
  iAngle = K1;
  iTmp = (sWord)((K2 * iRatio) >> 15);
  iAngle += iTmp;
  iTmp = (sWord)(iRatio * iRatio >> 15);
  iTmp = (sWord)((iTmp * K3) >> 15);
  iAngle += iTmp;
  /* check if above 45 degrees */
  if (iy > ix) 
    iAngle = (sWord)(9000 - iAngle);
  /* for tidiness, limit result to range 0 to 9000 equals 0.0 to 90.0 degrees */
  if (iAngle < 0) 
    iAngle = 0;
  if (iAngle > 9000) 
    iAngle = 9000;
  
  return (iAngle);
}

static Word iHundredAtan2Deg(sWord iy, sWord ix)
{
  Word iResult; /* angle in degrees times 100 */
  /* check for -32768 which is not handled correctly */
  if (ix == -32768) ix = -32767;
  if (iy == -32768) iy = -32767;
  
  /* check for quadrants */
  if ((ix >= 0) && (iy >= 0)) /* range 0 to 90 degrees */
    iResult = iHundredAtanDeg(iy, ix);
  else if ((ix <= 0) && (iy >= 0)) /* range 90 to 180 degrees */
    iResult = (Word)(18000 - (Word)iHundredAtanDeg(iy, (Word)-ix));
  else if ((ix <= 0) && (iy <= 0)) /* range -180 to -90 degrees */
    iResult = (Word)((Word)-18000 + iHundredAtanDeg((Word)-iy, (Word)-ix));
  else /* ix >=0 and iy <= 0 giving range -90 to 0 degrees */
    iResult = (Word)(-iHundredAtanDeg((Word)-iy, ix));

  return (iResult);
}


void MAG3110_IE_compass(sWord iBpx, sWord iBpy, sWord iBpz, sWord iGpx, sWord iGpy, sWord iGpz)
{
  /* stack variables */
  /* iBpx, iBpy, iBpz: the three components of the magnetometer sensor */
  /* iGpx, iGpy, iGpz: the three components of the accelerometer sensor */
  /* local variables */
  sWord iSin, iCos; /* sine and cosine */
 
  /* subtract the hard iron offset */
  iBpx -= iVx; /* see Eq 16 */
  iBpy -= iVy; /* see Eq 16 */
  iBpz -= iVz; /* see Eq 16 */
  /* calculate current roll angle Phi */
  iPhi = iHundredAtan2Deg(iGpy, iGpz);/* Eq 13 */
  /* calculate sin and cosine of roll angle Phi */
  iSin = iTrig(iGpy, iGpz); /* Eq 13: sin = opposite / hypoteneuse */
  iCos = iTrig(iGpz, iGpy); /* Eq 13: cos = adjacent / hypoteneuse */
  /* de-rotate by roll angle Phi */
  iBfy = (sWord)((iBpy * iCos - iBpz * iSin) >> 15);/* Eq 19 y component */
  iBpz = (sWord)((iBpy * iSin + iBpz * iCos) >> 15);/* Bpy*sin(Phi)+Bpz*cos(Phi)*/
  iGpz = (sWord)((iGpy * iSin + iGpz * iCos) >> 15);/* Eq 15 denominator */
  /* calculate current pitch angle Theta */
  iThe = iHundredAtan2Deg((sWord)-iGpx, iGpz);/* Eq 15 */
  /* restrict pitch angle to range -90 to 90 degrees */
  if (iThe > 9000) 
    iThe = (sWord) (18000 - iThe);
  if (iThe < -9000) 
    iThe = (sWord) (-18000 - iThe);
  /* calculate sin and cosine of pitch angle Theta */
  iSin = (sWord)-iTrig(iGpx, iGpz); /* Eq 15: sin = opposite / hypoteneuse */
  iCos = iTrig(iGpz, iGpx); /* Eq 15: cos = adjacent / hypoteneuse */
  /* correct cosine if pitch not in range -90 to 90 degrees */
  if (iCos < 0) 
    iCos = (sWord)-iCos;
  /* de-rotate by pitch angle Theta */
  iBfx = (sWord)((iBpx * iCos + iBpz * iSin) >> 15);/* Eq 19: x component */
  iBfz = (sWord)((-iBpx * iSin + iBpz * iCos) >> 15);/* Eq 19: z component */
  /* calculate current yaw = e-compass angle Psi */
  iPsi = iHundredAtan2Deg((sWord)-iBfy, iBfx); /* Eq 22 */
}
#endif

