/*
 * MMA8451.c
 *
 *  Created on: Nov 13, 2014
 *      Author: nicho_000
 */

#include "MMA8451.h"
#include "I2C2.h"
#include "FMSTR1.h"
//#include "LED1.h"
//#include "LED2.h"
//#include "LED3.h"
 
/* External 3-axis accelerometer control register addresses */
#define MMA8451_CTRL_REG_1 0x2A
/* MMA8451 3-axis accelerometer control register bit masks */
#define MMA8451_ACTIVE_BIT_MASK 0x01
#define MMA8451_F_READ_BIT_MASK 0x02
 
/* External 3-axis accelerometer data register addresses */
#define MMA8451_OUT_X_MSB 0x01
#define MMA8451_OUT_X_LSB 0x02
#define MMA8451_OUT_Y_MSB 0x03
#define MMA8451_OUT_Y_LSB 0x04
#define MMA8451_OUT_Z_MSB 0x05
#define MMA8451_OUT_Z_LSB 0x06
#define MMA8451_XYZ_DATA_CFG 0x0E
#define MMA8451_2gMODE 0x00
#define MMA8451_4gMODE 0x01
#define MMA8451_8gMODE 0x02


static MMA8451_TDataState deviceData;
 

int8_t AccelX, AccelY, AccelZ;
uint8_t aOutputRangeByte;

uint8_t MMA8451_ReadReg(uint8_t addr, uint8_t *data, short dataSize) {
  uint8_t res;
 
  /* Send I2C address plus register address to the I2C bus *without* a stop condition */
  res = I2C2_MasterSendBlock(deviceData.handle, &addr, 1U, LDD_I2C_NO_SEND_STOP);
  if (res!=ERR_OK) {
    return ERR_FAILED;
  }
  while (!deviceData.dataTransmittedFlg) {} /* Wait until data is sent */
  deviceData.dataTransmittedFlg = FALSE;
 
  /* Receive InpData (1 byte) from the I2C bus and generates a stop condition to end transmission */
  res = I2C2_MasterReceiveBlock(deviceData.handle, data, dataSize, LDD_I2C_SEND_STOP);
  if (res!=ERR_OK) {
    return ERR_FAILED;
  }
  while (!deviceData.dataReceivedFlg) {} /* Wait until data is received received */
  deviceData.dataReceivedFlg = FALSE;
  return ERR_OK;
}

uint8_t MMA8451_WriteReg(uint8_t addr, uint8_t val) {
  uint8_t buf[2], res;
 
  buf[0] = addr;
  buf[1] = val;
  res = I2C2_MasterSendBlock(deviceData.handle, &buf, 2U, LDD_I2C_SEND_STOP); /* Send OutData (3 bytes with address) on the I2C bus and generates not a stop condition to end transmission */
  if (res!=ERR_OK) {
    return ERR_FAILED;
  }
  while (!deviceData.dataTransmittedFlg) {}  /* Wait until date is sent */
  deviceData.dataTransmittedFlg = FALSE;
  return ERR_OK;
}

static int8_t xyz[3];
static int8_t xMSB;
static int8_t yMSB;
static int8_t zMSB;
static int8_t xLSB;
static int8_t yLSB;
static int8_t zLSB;
static int32_t count;
static int32_t loopcount;

static uint8_t rangeByte;

void MMA8451_Run(void) {
  uint8_t res;
 
  count = 0;
  loopcount = 0;
  
  deviceData.handle = I2C2_Init(&deviceData);
  /* F_READ: Fast read mode, data format limited to single byte (auto increment counter will skip LSB)
  * ACTIVE: Full scale selection
  */
  res = MMA8451_WriteReg(MMA8451_XYZ_DATA_CFG, MMA8451_8gMODE);
  res = MMA8451_WriteReg(MMA8451_CTRL_REG_1,  MMA8451_F_READ_BIT_MASK|MMA8451_ACTIVE_BIT_MASK);
  res = MMA8451_WriteReg(MMA8451_XYZ_DATA_CFG, MMA8451_8gMODE);
  if (res==ERR_OK) {
    for(;;) {
      
    	
     //res = MMA8451_ReadReg(MMA8451_OUT_X_MSB, (uint8_t*)&xyz, 3);
       
    	res = MMA8451_ReadReg(MMA8451_OUT_X_MSB, (uint8_t*)&xMSB, 1);
    	res = MMA8451_ReadReg(MMA8451_OUT_Y_MSB, (uint8_t*)&yMSB, 1);
    	res = MMA8451_ReadReg(MMA8451_OUT_Z_MSB, (uint8_t*)&zMSB, 1);
    	res = MMA8451_ReadReg(MMA8451_OUT_X_LSB, (uint8_t*)&xLSB, 1);
		res = MMA8451_ReadReg(MMA8451_OUT_Y_LSB, (uint8_t*)&yLSB, 1);
    	res = MMA8451_ReadReg(MMA8451_OUT_Z_LSB, (uint8_t*)&zLSB, 1);
    	res = MMA8451_ReadReg(MMA8451_XYZ_DATA_CFG, (uint8_t*)&rangeByte, 1);
      
     /* START OF CODE FOR BLINKING THING*/ 
     /* if (xyz[2] < -115 || xyz[2] > 115 || xyz[1] < -115 || xyz[1] > 115 || xyz[0] < -115 || xyz[0] > 115) {
    	  
    	  LEDG_Neg();
    	  WAIT1_Waitms(500);
    	  for(loopcount = 0; loopcount <= count ; loopcount++){
    	        		LEDR_Neg();
    	        		WAIT1_Waitms(200);
    	        		LEDR_Neg();
    	        		WAIT1_Waitms(200);
    	  }
    	  if(count < 25) count++;
    	  if(count >=25) count = 0;
    	  LEDG_Neg();
      
      }*/
      /*END OF CODE FOR BLINKING THING*/
      
      
      /*START OF CODE FOR FREEMASTER*/
      FMSTR1_Poll();
      FMSTR1_Recorder();
          
      //AccelX = xyz[0];
      //AccelY = xyz[1];
      //AccelZ = xyz[2];
      
      AccelX = xMSB;
      AccelY = yMSB;
      AccelZ = zMSB;
      aOutputRangeByte = rangeByte;
      
      /*END OF CODE FOR FREEMASTER*/
    
    }
  }
  
  I2C2_Deinit(deviceData.handle); //*****!!!!!!ORIGINALLY Deinit????
  LEDR_Off();
  LEDG_Off();
 }











