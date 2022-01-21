#include "HMC5983.h"

uint8_t HMC5983_Init(Sens_HMC5983 *handle) {
	//Debug_Printf("HMC5983 initial started.\r\n");
	uint8_t id[3];
	Spi_DisableDevice(SPI_HMC);
	HAL_Delay(50);
	Spi_ReadDeviceReg(SPI_HMC, HMC5983_ID_A, id);
	Spi_ReadDeviceReg(SPI_HMC, HMC5983_ID_A + 1, id + 1);
	Spi_ReadDeviceReg(SPI_HMC, HMC5983_ID_A + 2, id + 2);
	
	Debug_Printf("HMC5983 ID=%x %x %x\r\n", id[0], id[1], id[2]);
	//Debug_Printf("HMC5983 initial succeeded.\r\n\r\n");
	if(id[0] == 0x48 && id[1] == 0x34 && id[2] == 0x33) {
		return 0;
	}
	else {
		return 1;
	}
}