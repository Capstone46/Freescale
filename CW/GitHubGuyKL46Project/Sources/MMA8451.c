/*
 * MMA8451.c
 *
 *  Created on: Nov 13, 2014
 *      Author: nicho_000
 */

#include "MMA8451.h"
#include "I2C2.h"
#include "FMSTR1.h"
#include <stdlib.h>
#include "SW1.h"
#include "PTC.h"
#include "BitIoLdd3.h" 

//value to delay output by so its easier to see in freemaster
#define OUTPUTDELAY 5

/* External 3-axis accelerometer control register addresses */
#define MMA8451_CTRL_REG_1 0x2A
/* MMA8451 3-axis accelerometer control register bit masks */
#define MMA8451_ACTIVE_BIT_MASK 0x01  //TRUE = ACTIVE MODE, FALSE = STANDBY
#define MMA8451_F_READ_BIT_MASK 0x02  //TRUE = fast read (single byte) mode, FALSE = normal mode
#define MMA8451_NORMAL_100Hz_MASK 0x1B

/* External 3-axis accelerometer data register addresses */
#define MMA8451_OUT_X_MSB 0x01
#define MMA8451_OUT_X_LSB 0x02
#define MMA8451_OUT_Y_MSB 0x03
#define MMA8451_OUT_Y_LSB 0x04
#define MMA8451_OUT_Z_MSB 0x05
#define MMA8451_OUT_Z_LSB 0x06

// Accelerometer resolution mode select register address
#define MMA8451_XYZ_DATA_CFG 0x0E
// Values for selecting accelerometer resolution mode
#define MMA8451_2gMODE 0x00
#define MMA8451_4gMODE 0x01
#define MMA8451_8gMODE 0x02

// Max number of samples to record to SRAM max 15000
#define UPLIM	15000

// Something from the tutorial
static MMA8451_TDataState deviceData;

// Capstone 46 variables
int8_t AccelX, AccelY, AccelZ;
uint16_t vectorSum = 0;
uint16_t vectorSumDataStreamOut = 0;
uint16_t vectorSumData[UPLIM];
uint16_t counter = 0;
uint16_t loopcounter = 0;
uint16_t ndcounter = 0;
uint8_t currentState = 0;

//Capstone 46 variables
static int8_t xMSB;
static int8_t yMSB;
static int8_t zMSB;


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


//MAIN FUNCTION
void MMA8451_Run(void) {
	
  //Error checking variable	
  uint8_t res;
  //sampling delay counter
  uint8_t delayCounter = 0;
  
  //Initialize pull up on SW1
  PTC_Init();
  
  //Initialize accelerometer I2C
  deviceData.handle = I2C2_Init(&deviceData);
  
  //Inital LED settings
  LEDG_On();
  LEDR_Off();
 
  //Set the accelerometer to 8g mode
  res = MMA8451_WriteReg(MMA8451_XYZ_DATA_CFG, MMA8451_8gMODE);
  /* F_READ: Fast read mode, data format limited to single byte (auto increment counter will skip LSB)
   * ACTIVE: Full scale selection
   */
  res = MMA8451_WriteReg(MMA8451_CTRL_REG_1,  MMA8451_F_READ_BIT_MASK|MMA8451_ACTIVE_BIT_MASK|MMA8451_NORMAL_100Hz_MASK);
   
  //MAIN LOOP
  if (res==ERR_OK) {
    for(;;) {
    	
    	//read accelerometer values
		res = MMA8451_ReadReg(MMA8451_OUT_X_MSB, (uint8_t*)&xMSB, 1);
		res = MMA8451_ReadReg(MMA8451_OUT_Y_MSB, (uint8_t*)&yMSB, 1);
		res = MMA8451_ReadReg(MMA8451_OUT_Z_MSB, (uint8_t*)&zMSB, 1);
		//Reading accelerometer values to the variables that freemaster looks at         
		AccelX = xMSB;
		AccelY = yMSB;
		AccelZ = zMSB;
		//calculating the vector sum of the XY and Z directions      
		
 
    	//State 0: ready to record (idle)
		if (currentState == 0){
			if(!SW1_GetVal()) {
				currentState  = 1;
				LEDR_On();
				LEDG_Off();
			}
		}
		
		//State 1: recording
		if (currentState == 1){
			//loop to record data
									
			delayCounter++;
			if(delayCounter >= OUTPUTDELAY){
				vectorSum = (abs(AccelX) + abs(AccelY) + abs(AccelZ));    	
				vectorSumData[counter] = vectorSum;
				counter++;
				delayCounter = 0;
				if (counter >= UPLIM) {
					currentState = 2;
					counter = 0;
					LEDR_Off();
					LEDG_Off();
				}
			}
		}
    
		//State 2: done recording (idle)
		if (currentState == 2){
			if(!SW1_GetVal()) {
				currentState  = 3;
				LEDR_On();
				LEDG_On();
			}
		}
    
		//State 3: replaying data
		if (currentState == 3){
			
			delayCounter++;
			if(delayCounter >= OUTPUTDELAY){
				vectorSumDataStreamOut = vectorSumData[counter];
				counter++;
				delayCounter = 0;
				if(counter >= UPLIM){
					currentState = 0;
					vectorSum = 0;
					vectorSumDataStreamOut = 0;
					counter = 0;
					LEDG_On();
					LEDR_Off();
				}
			}
		}
    	      
    	//Functions that must be called for freemaster to work
		FMSTR1_Poll();
		FMSTR1_Recorder();
		   
     }
  }
  
  //from tutorial
  I2C2_Deinit(deviceData.handle); 
  LEDR_Off();
  LEDG_Off();
 }











