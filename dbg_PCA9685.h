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

/** @brief Debugging Module for the PCA9685
 *
 * Initialises the debugging module with a pointer to one (or an array) or PCA9685 structs,
 * together with the amount of structs pointed at.
 * Returns a pointer to an gshell command, which can be passed over to the gshell library 
 * to access it.
 *
 * This allows one or multiple PCA9685 chips to be directly manipulated via a terminal.
 * 
 * @params pArr		Pointer to the PCA9685 struct(s)
 * @params pcaCount	Amount of structures pointed to
 * @returns			gshell command instance
 */
gshell_cmd_t* dbg_pca9685_init(PCA9685_t *pArr, uint8_t pcaCount);

#endif
