#include "PCA9685.h"

static const float _freqCalc = 6103.515625f;

void pca9685_initStruct(PCA9685_t* inst, uint8_t i2cAddr, void* io, uint8_t (*startTrans)(void*), uint8_t (*sendBytes)(void*,uint8_t,uint8_t*,uint16_t),uint8_t (*getBytes)(void*,uint8_t,uint8_t*,uint16_t),uint8_t (*endTrans)(void*))
{
	inst->errors = PCA9685_NO_ERROR;
	inst->i2cAddr = i2cAddr;
	inst->ioInterface = io;
	inst->startTransaction = startTrans;
	inst->sendBytes = sendBytes;
	inst->getBytes = getBytes;
	inst->endTransaction = endTrans;
}

uint8_t pca9685_initChip(PCA9685_t* inst)
{
	inst->errors = PCA9685_NO_ERROR;

	inst->on = 0xFFF;
	inst->off = 0;

	/* Just try to read a valid register and see if a io error happens */
	pca9685_readReg(inst, R_PCA9685_MODE2);

	return inst->errors;
}

void pca9685_writeReg(PCA9685_t* inst, uint8_t regAddr, uint8_t value)
{
	uint8_t dataPackage[2] = {regAddr, value};

	inst->startTransaction(inst->ioInterface);
	inst->errors |= inst->sendBytes(inst->ioInterface, inst->i2cAddr, dataPackage, 2);
	inst->endTransaction(inst->ioInterface);
}

uint8_t pca9685_readReg(PCA9685_t* inst, uint8_t regAddr)
{
	uint8_t dataPackage = regAddr;

	inst->startTransaction(inst->ioInterface);

	/* Point to the internal register... */
	inst->errors |= inst->sendBytes(inst->ioInterface, inst->i2cAddr, &dataPackage, 1);
	/* ... and read the value back */
	inst->errors |= inst->getBytes(inst->ioInterface, inst->i2cAddr, &dataPackage, 1);
	
	inst->endTransaction(inst->ioInterface);

	return dataPackage;
}

void pca9685_setFrequency(PCA9685_t* inst, float frequency)
{
	uint8_t freqVal;
	inst->errors = PCA9685_NO_ERROR;

	if (frequency < 23.935f)	frequency = 23.935f;
	if (frequency > 1600.0f)	frequency = 1600;
	
	freqVal = _freqCalc / frequency;
	
	pca9685_writeReg(inst, R_PCA9685_PRE_SCALE, freqVal);
}

void pca9685_setPrescaler(PCA9685_t* inst, uint8_t prescaler)
{
	inst->errors = PCA9685_NO_ERROR;

	if (prescaler < 3)	prescaler = 3;

	pca9685_writeReg(inst, R_PCA9685_PRE_SCALE, prescaler);
}

float pca9685_getFrequency(PCA9685_t* inst)
{
	uint8_t freqVal;
	float freqCalc;
	inst->errors = PCA9685_NO_ERROR;

	freqVal = pca9685_readReg(inst, R_PCA9685_PRE_SCALE);

	freqCalc = _freqCalc / (float)freqVal;

	return freqCalc;
}

uint8_t pca9685_getPrescaler(PCA9685_t* inst)
{
	inst->errors = PCA9685_NO_ERROR;

	return pca9685_readReg(inst, R_PCA9685_PRE_SCALE);
}

void pca9685_setPWM(PCA9685_t* inst, enum PCA9685_LED led, uint16_t on, uint16_t off)
{
	uint8_t dataPackage[5];
	inst->errors = PCA9685_NO_ERROR;

	on &= 0xFFF;
	off &= 0xFFF;

	dataPackage[0] = led * 4 + R_PCA9685_LED0_ON_L;
	dataPackage[1] = on;
	dataPackage[2] = on >> 8;
	dataPackage[3] = off;
	dataPackage[4] = off >> 8;

	inst->startTransaction(inst->ioInterface);
	inst->errors |= inst->sendBytes(inst->ioInterface, inst->i2cAddr, dataPackage, 5);
	inst->endTransaction(inst->ioInterface);
/*
	pca9685_writeReg(inst, led * 4 + R_PCA9685_LED0_ON_L, on);
	pca9685_writeReg(inst, led * 4 + R_PCA9685_LED0_ON_H, on >> 8);
	pca9685_writeReg(inst, led * 4 + R_PCA9685_LED0_OFF_L, off);
	pca9685_writeReg(inst, led * 4 + R_PCA9685_LED0_OFF_H, off >> 8);
*/
}

void pca9685_setAllPWM(PCA9685_t* inst, uint16_t on, uint16_t off)
{
	uint8_t dataPackage[5];
	inst->errors = PCA9685_NO_ERROR;

	pca9685_writeReg(inst, R_PCA9685_ALL_LED_ON_L, on);
	pca9685_writeReg(inst, R_PCA9685_ALL_LED_ON_H, on >> 8);
	pca9685_writeReg(inst, R_PCA9685_ALL_LED_OFF_L, off);
	pca9685_writeReg(inst, R_PCA9685_ALL_LED_OFF_H, off >> 8);
}

void pca9685_configureONOFF(PCA9685_t* inst, uint16_t on, uint16_t off)
{
	inst->on = on & 0xFFF;
	inst->off = off & 0xFFF;
}

void pca9685_fullyON(PCA9685_t* inst, enum PCA9685_LED led)
{
	inst->errors = PCA9685_NO_ERROR;

	pca9685_writeReg(inst, led * 4 + R_PCA9685_LED0_OFF_L, inst->on);
	pca9685_writeReg(inst, led * 4 + R_PCA9685_LED0_OFF_H, inst->on >> 8);
}

void pca9685_fullyOFF(PCA9685_t* inst, enum PCA9685_LED led)
{
	inst->errors = PCA9685_NO_ERROR;

	pca9685_writeReg(inst, led * 4 + R_PCA9685_LED0_OFF_L, inst->off);
	pca9685_writeReg(inst, led * 4 + R_PCA9685_LED0_OFF_H, inst->off >> 8);
}