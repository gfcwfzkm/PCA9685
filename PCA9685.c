#include "PCA9685.h"

void pca9685_initStruct(pca9685_t* inst, uint8_t i2cAddr, void* io, uint8_t (*startTrans)(void*), uint8_t (*sendBytes)(void*,uint8_t,uint8_t*,uint16_t),uint8_t (*getBytes)(void*,uint8_t,uint8_t*,uint16_t),uint8_t (*endTrans)(void*))
{

}

uint8_t pca9685_initChip(pca9685_t* inst)
{

}

void pca9685_writeReg(pca9685_t* inst, uint8_t regAddr, uint8_t value)
{

}

uint8_t pca9685_readReg(pca9685_t* inst, uint8_t regAddr)
{

}

void pca9685_setPrescaler(pca9685_t* inst, uint8_t prescaler)
{

}

uint8_t pca9685_getPrescaler(pca9685_t* inst)
{

}

void pca9685_setPWM(pca9685_t* inst, enum pca8685_e led, uint16_t on, uint16_t off)
{

}
