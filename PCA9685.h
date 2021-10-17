
#ifndef _PCA9685_H_
#define _PCA9685_H_

#include <stdint.h>

/* Registers of the PCA9685 */
#define R_PCA9685_MODE1        		0x00
#define R_PCA9685_MODE1_RESTART			0x80
#define R_PCA9685_MODE1_EXTCLK			0x40
#define R_PCA9685_MODE1_AUTOINCREMENT	0x20
#define R_PCA9685_MODE1_SLEEP			0x10
#define R_PCA9685_MODE1_SUB1			0x08
#define R_PCA9685_MODE1_SUB2			0x04
#define R_PCA9685_MODE1_SUB3			0x02
#define R_PCA9685_MODE1_ALLCALL			0x01
#define R_PCA9685_MODE2        		0x01
#define R_PCA9685_MODE2_INVERT			0x10
#define R_PCA9685_MODE2_OCH				0x08
#define R_PCA9685_MODE2_OUTDRV			0x04
#define R_PCA9685_MODE2_OUTNE1			0x02
#define R_PCA9685_MODE2_OUTNE0			0x01
#define R_PCA9685_SUBADR1           0x02
#define R_PCA9685_SUBADR2           0x03
#define R_PCA9685_SUBADR3           0x04
#define R_PCA9685_ALLCALLADR        0x05
#define R_PCA9685_LED0_ON_L         0x06
#define R_PCA9685_LED0_ON_H         0x07
#define R_PCA9685_LED0_OFF_L        0x08
#define R_PCA9685_LED0_OFF_H        0x09
#define R_PCA9685_LED1_ON_L         0x0A
#define R_PCA9685_LED1_ON_H         0x0B
#define R_PCA9685_LED1_OFF_L        0x0C
#define R_PCA9685_LED1_OFF_H        0x0D
#define R_PCA9685_LED2_ON_L         0x0E
#define R_PCA9685_LED2_ON_H         0x0F
#define R_PCA9685_LED2_OFF_L        0x10
#define R_PCA9685_LED2_OFF_H        0x11
#define R_PCA9685_LED3_ON_L         0x12
#define R_PCA9685_LED3_ON_H         0x13
#define R_PCA9685_LED3_OFF_L        0x14
#define R_PCA9685_LED3_OFF_H        0x15
#define R_PCA9685_LED4_ON_L         0x16
#define R_PCA9685_LED4_ON_H         0x17
#define R_PCA9685_LED4_OFF_L        0x18
#define R_PCA9685_LED4_OFF_H        0x19
#define R_PCA9685_LED5_ON_L         0x1A
#define R_PCA9685_LED5_ON_H         0x1B
#define R_PCA9685_LED5_OFF_L        0x1C
#define R_PCA9685_LED5_OFF_H        0x1D
#define R_PCA9685_LED6_ON_L         0x1E
#define R_PCA9685_LED6_ON_H         0x1F
#define R_PCA9685_LED6_OFF_L        0x20
#define R_PCA9685_LED6_OFF_H        0x21
#define R_PCA9685_LED7_ON_L         0x22
#define R_PCA9685_LED7_ON_H         0x23
#define R_PCA9685_LED7_OFF_L        0x24
#define R_PCA9685_LED7_OFF_H        0x25
#define R_PCA9685_LED8_ON_L         0x26
#define R_PCA9685_LED8_ON_H         0x27
#define R_PCA9685_LED8_OFF_L        0x28
#define R_PCA9685_LED8_OFF_H        0x29
#define R_PCA9685_LED9_ON_L         0x2A
#define R_PCA9685_LED9_ON_H         0x2B
#define R_PCA9685_LED9_OFF_L        0x2C
#define R_PCA9685_LED9_OFF_H        0x2D
#define R_PCA9685_LED10_ON_L        0x2E
#define R_PCA9685_LED10_ON_H        0x2F
#define R_PCA9685_LED10_OFF_L       0x30
#define R_PCA9685_LED10_OFF_H       0x31
#define R_PCA9685_LED11_ON_L        0x32
#define R_PCA9685_LED11_ON_H        0x33
#define R_PCA9685_LED11_OFF_L       0x34
#define R_PCA9685_LED11_OFF_H       0x35
#define R_PCA9685_LED12_ON_L        0x36
#define R_PCA9685_LED12_ON_H        0x37
#define R_PCA9685_LED12_OFF_L       0x38
#define R_PCA9685_LED12_OFF_H       0x39
#define R_PCA9685_LED13_ON_L        0x3A
#define R_PCA9685_LED13_ON_H        0x3B
#define R_PCA9685_LED13_OFF_L       0x3C
#define R_PCA9685_LED13_OFF_H       0x3D
#define R_PCA9685_LED14_ON_L        0x3E
#define R_PCA9685_LED14_ON_H        0x3F
#define R_PCA9685_LED14_OFF_L       0x40
#define R_PCA9685_LED14_OFF_H       0x41
#define R_PCA9685_LED15_ON_L        0x42
#define R_PCA9685_LED15_ON_H        0x43
#define R_PCA9685_LED15_OFF_L       0x44
#define R_PCA9685_LED15_OFF_H       0x45
#define R_PCA9685_ALL_LED_ON_L		0xFA
#define R_PCA9685_ALL_LED_ON_H		0xFB
#define R_PCA9685_ALL_LED_OFF_L		0xFC
#define R_PCA9685_ALL_LED_OFF_H		0xFE
#define R_PCA9685_PRE_SCALE			0xFF

enum pca8685_e {
	PCA_LED0 = 0,
	PCA_LED1,
	PCA_LED2,
	PCA_LED3,
	PCA_LED4,
	PCA_LED5,
	PCA_LED6,
	PCA_LED7,
	PCA_LED8,
	PCA_LED9,
	PCA_LED10,
	PCA_LED11,
	PCA_LED12,
	PCA_LED13,
	PCA_LED14,
	PCA_LED15
};

/* Data struct */
typedef struct{
	uint8_t i2cAddr;
	uint8_t err;
	void *ioInterface;					// InterfacePointer of the IO/Interface Library
	uint8_t (*startTransaction)(void*);	// Prepare the IO/Peripheral Interface for a transaction
	uint8_t (*sendBytes)(void*,			// Send data to the interface: InterfacePointer
						uint8_t,		// I2C Address of the PWM chip (8-Bit format!)
						uint8_t*,		// Pointer to the buffer to send
						uint16_t);		// length of the buffer
	uint8_t (*getBytes)(void*,			// Get data from the interface: InterfacePointer
						uint8_t,		// I2C Address of the PWM chip (8-Bit format!)
						uint8_t*,		// Pointer to the buffer to receive
						uint16_t);		// length of the buffer
	uint8_t (*endTransaction)(void*);	// Finish the transaction & release the IO / Peripheral
} pca9685_t;

/* Just to initialise the struct if one doesn't want to initialise it themself in the declaration */
void pca9685_initStruct(pca9685_t* inst, uint8_t i2cAddr, void* io, uint8_t (*startTrans)(void*), uint8_t (*sendBytes)(void*,uint8_t,uint8_t*,uint16_t),uint8_t (*getBytes)(void*,uint8_t,uint8_t*,uint16_t),uint8_t (*endTrans)(void*));

uint8_t pca9685_initChip(pca9685_t* inst);

void pca9685_writeReg(pca9685_t* inst, uint8_t regAddr, uint8_t value);
uint8_t pca9685_readReg(pca9685_t* inst, uint8_t regAddr);

/* Set the prescaler register
 *
 * Sets the prescaler register as 8bit value. With the default clock of ~25MHz
 * a output frequency of 24Hz to 1526Hz can be achived ((clock / (4 * 4096)) / prescaler)
 */
void pca9685_setPrescaler(pca9685_t* inst, uint8_t prescaler);

uint8_t pca9685_getPrescaler(pca9685_t* inst);

/* Set the PWM LED Registers
 *
 * Sets the PWM on and off value of the led register
 */
void pca9685_setPWM(pca9685_t* inst, enum pca8685_e led, uint16_t on, uint16_t off);

#endif