/**
 * PCA9685 Debugging Module
 * 
 * Additional debugging library to link the PWM-Chip command to the gshell terminal library.
 * Allows direct access via the terminal library to the PCA9685's registers.
 */

#ifndef _DBG_PCA9685_H_
#define _DBG_PCA9685_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "PCA9685.h"
#include "gshell.h"

/* Initialise the debugging module a pointer to an array of PCA9685 structs together with the amount of 
 * PCA9685's within that list. Returns a gshell_cmd_t pointer to initialise the command for it. */
gshell_cmd_t* dbg_pca9685_init(PCA9685_t *pArr, uint8_t pcaCount);

#endif