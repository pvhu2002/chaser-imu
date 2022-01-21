#include "Spi_Driver.h"

static uint8_t tx, rx;
static uint8_t tx_buff[14];

uint8_t Spi_ReceiveData(uint8_t *pData, uint16_t size) {
	HAL_StatusTypeDef status;
	
	status = HAL_SPI_Receive_DMA(&hspi1, pData, size);
	
	return (status == HAL_OK) ? 0 : 1;
}

uint8_t Spi_TransmitData(uint8_t *pData, uint16_t size) {
	HAL_StatusTypeDef status;
	
	status = HAL_SPI_Transmit_DMA(&hspi1, pData, size);
	
	return (status == HAL_OK) ? 0 : 1;
}

uint8_t Spi_TransmitReceiveData(uint8_t *pTxData, uint8_t *pRxData, uint16_t size) {
	HAL_StatusTypeDef status;
	
	status = HAL_SPI_TransmitReceive_DMA(&hspi1, pTxData, pRxData, size);
	
	return (status == HAL_OK) ? 0 : 1;
}

void Spi_EnableDevice(uint8_t device) {
	switch (device) {
		case SPI_BARO:
			HAL_GPIO_WritePin(BARO_CS_GPIO_Port, BARO_CS_Pin, GPIO_PIN_RESET);
			break;
		case SPI_ICM:
			HAL_GPIO_WritePin(ICM_CS_GPIO_Port, ICM_CS_Pin, GPIO_PIN_RESET);
			break;
		case SPI_HMC:
			HAL_GPIO_WritePin(HMC_CS_GPIO_Port, HMC_CS_Pin, GPIO_PIN_RESET);
			break;
		default:
			break;
	}
}

void Spi_DisableDevice(uint8_t device) {
	HAL_GPIO_WritePin(BARO_CS_GPIO_Port, BARO_CS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(ICM_CS_GPIO_Port, ICM_CS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(HMC_CS_GPIO_Port, HMC_CS_Pin, GPIO_PIN_SET);
}

uint8_t Spi_ReadDeviceBuffer(uint8_t device, uint8_t regAddr, uint8_t *pData, uint8_t size) {
	uint8_t status_1,status_2;
	
	Spi_EnableDevice(device);
	tx = regAddr | 0x80;
	tx_buff[0] = tx;
	status_1 = Spi_TransmitReceiveData(&tx, &rx, 1);
	status_2 = Spi_TransmitReceiveData(tx_buff, pData, size);
	Spi_DisableDevice(device);
	
	return status_1 || status_2;
}

uint8_t Spi_ReadDeviceReg(uint8_t device, uint8_t regAddr, uint8_t *pData) {
	return Spi_ReadDeviceBuffer(device, regAddr, pData, 1);
}

uint8_t Spi_WriteDeviceReg(uint8_t device, uint8_t reg, uint8_t value) {
	uint8_t status_1,status_2;
	
	Spi_EnableDevice(device);
	tx = reg & 0x7F;
	status_1 = Spi_TransmitReceiveData(&tx, &rx, 1);
	tx = value;
	status_2 = Spi_TransmitReceiveData(&tx, &rx, 1);
	Spi_DisableDevice(device);
	
	return status_1 || status_2;
}
