#ifndef __BARO_MS5611_H
#define __BARO_MS5611_H

#include "Spi_Driver.h"

#ifdef DEBUG
#include "Uart_Driver.h"
#include "stdio.h"
#endif

#define MS5611_CMD_SIZE 1
#define MS5611_PROM_SIZE 8
#define MS5611_CMD_RESET 0x1E
#define MS5611_CMD_ADC_READ 0x00
#define MS5611_CMD_D1 0x40
#define MS5611_PROM_READ_0 0XA0
#define MS5611_PROM_READ_1 0XA2
#define MS5611_PROM_READ_2 0XA4
#define MS5611_PROM_READ_3 0XA6
#define MS5611_PROM_READ_4 0XA8
#define MS5611_PROM_READ_5 0XAA
#define MS5611_PROM_READ_6 0XAC
#define MS5611_PROM_READ_7 0XAE

typedef struct {
	uint8_t id_a;
    uint16_t prom[MS5611_PROM_SIZE];
} Sens_MS5611;

uint16_t MS5611_Read16Bits(uint8_t cmd);
void MS5611_Reset(Sens_MS5611 *handle);
uint8_t MS5611_GetPROM(Sens_MS5611 *handle);

uint8_t Baro_Init(Sens_MS5611 *handle);

#endif
