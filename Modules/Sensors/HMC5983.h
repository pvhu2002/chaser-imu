#ifndef __HMC5983_H
#define __HMC5983_H

#include "Spi_Driver.h"

#define HMC5983_ID_A 0x0A

typedef struct {
	uint8_t id_a;
	
} Sens_HMC5983;

uint8_t HMC5983_Init(Sens_HMC5983 *handle);

#endif