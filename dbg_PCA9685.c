#include "dbg_PCA9685.h"

static PCA9685_t *pList;
static uint8_t pcaCnt;
static uint8_t selPCA;

static void gshell_cmd_dbgpca(uint8_t argc, char *argv[])
{
	PCA9685_t *pca;
	// Generic temporary variables
	uint8_t u8RegVal, u8RegAddr;

	if (pcaCnt == 0)
	{
		gshell_putString_f("Not properly initialised - pcaCount = 0!"G_CRLF);
		return;
	}
	else
	{
		pca = (pList + selPCA);
	}
	
	pca->errors = PCA9685_NO_ERROR;

	if ((pcaCnt > 1) && (argc > 1) && (strncmp(argv[1], "select", 20) == 0))
	{
		if (argc > 2)
		{
			u8RegVal = (uint8_t)strtol(argv[2], NULL, 0);

			if (u8RegVal < pcaCnt)
			{
				gshell_printf_f("PWM-Chip %u deselected and %u selected!"G_CRLF, selPCA, u8RegVal);
				selPCA = u8RegVal;
			}
			else
			{
				gshell_printf_f("Value too high, choose a PWM-Chip between 0 and %u!"G_CRLF, pcaCnt);
			}
		}
		else
		{
			gshell_printf_f("%u PWM Chips to select from, Chip %u currently selected."G_CRLF, pcaCnt, selPCA);
		}
	}
	else if ((argc > 3) && (strncmp(argv[1], "write", 20) == 0))
	{
		u8RegAddr = (uint8_t)strtol(argv[2], NULL, 0);
		u8RegVal = (uint8_t)strtol(argv[3], NULL, 0);

		pca9685_writeReg(pca, u8RegAddr, u8RegVal);

		gshell_printf_f("Value 0x%02X (%u) written into register 0x%02X."G_CRLF, u8RegVal, u8RegVal, u8RegAddr);
	}
	else if ((argc > 2) && (strncmp(argv[1], "read", 20) == 0))
	{
		u8RegAddr = (uint8_t)strtol(argv[2], NULL, 0);

		u8RegVal = pca9685_readReg(pca, u8RegAddr);

		gshell_printf_f("Register 0x%02X contains the value 0x%02X (%u)."G_CRLF, u8RegAddr, u8RegVal, u8RegVal);
	}
	else
	{
		// Hilfe / Befehlsübersicht
		gshell_putString_f(G_TEXTBOLD G_TEXTUNDERL "PCA9865 Debug Module" G_TEXTNORMAL G_CRLF
		"select <val>      Select the PWM chip (if there are multiple) or"G_CRLF
		"                  returns the amount of PWM chips and the currently selected one."G_CRLF
		"write <reg> <val> Writes into the register <reg> the value <val>"G_CRLF
		"read <reg>        Reads the value of the register <reg> and prints it"G_CRLF);
	}
}

static gshell_cmd_t dbg_pca = 
{
	G_XARR("pca9685"),
	gshell_cmd_dbgpca,
	G_XARR("PCA9685 Debugging and Monitoring"),
	NULL
};

gshell_cmd_t* dbg_pca9685_init(PCA9685_t *pArr, uint8_t pcaCount)
{
	pList = pArr;
	pcaCnt = pcaCount;
	selPCA = 0;

	return &dbg_pca;
}
