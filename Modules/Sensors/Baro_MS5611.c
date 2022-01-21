#include "Baro_MS5611.h"

void MS5611_Reset(Sens_MS5611 *handle) {
	uint8_t temp[1] = {MS5611_CMD_RESET};
	
	Spi_EnableDevice(SPI_BARO);
	Spi_TransmitData(temp, MS5611_CMD_SIZE);
	//Spi_ReceiveData(byte, 1);
	Spi_DisableDevice(SPI_BARO);
}

uint16_t MS5611_Read16Bits(uint8_t cmd) {
	uint8_t temp[1] = {cmd};
	uint8_t byte[3];
	uint16_t value;
	
	uint8_t status;
	
	Spi_EnableDevice(SPI_BARO);
	status = Spi_TransmitData(temp, MS5611_CMD_SIZE);
	HAL_Delay(1);
	status = Spi_ReceiveData(byte, 2);
	Spi_DisableDevice(SPI_BARO);
	
	HAL_Delay(1);
	if(status == 0) {
		value = ((uint16_t)byte[0] << 8) | (byte[1]);
	}
	else {
		value = -1;
	}
	
	return value;
}


uint8_t MS5611_GetPROM(Sens_MS5611 *handle) {
	handle->prom[0] = MS5611_Read16Bits(MS5611_PROM_READ_0);
	handle->prom[1] = MS5611_Read16Bits(MS5611_PROM_READ_1);
	handle->prom[2] = MS5611_Read16Bits(MS5611_PROM_READ_2);
	handle->prom[3] = MS5611_Read16Bits(MS5611_PROM_READ_3);
	handle->prom[4] = MS5611_Read16Bits(MS5611_PROM_READ_4);
	handle->prom[5] = MS5611_Read16Bits(MS5611_PROM_READ_5);
	handle->prom[6] = MS5611_Read16Bits(MS5611_PROM_READ_6);
	handle->prom[7] = MS5611_Read16Bits(MS5611_PROM_READ_7);
	
	Debug_Printf("%d,%d,%d,%d,%d,%d,%d,%d\r\n", handle->prom[0], handle->prom[1], handle->prom[2], handle->prom[3], \
												handle->prom[4], handle->prom[5], handle->prom[6], handle->prom[7]);
}

// void MS5611_GetTemperature(void) {
// 	uint32_t t;
// 	//Debug_Printf("%d\n\r", t);
// }

uint8_t Baro_Init(Sens_MS5611 *handle) {
	//Debug_Printf("MS5611 initial started.\r\n");
	
	Spi_DisableDevice(SPI_BARO);
	MS5611_Reset(handle);
	HAL_Delay(50);
	MS5611_GetPROM(handle);
	if(handle->prom[0] == 0) {
		return 0;
	}
	else {
		return 1;
	}
	
}
