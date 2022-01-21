#ifndef __SPI_DRIVER_H
#define __SPI_DRIVER_H

#include "spi.h"

#ifdef DEBUG
#include "Uart_Driver.h"
#include "stdio.h"
#endif

#define SPI_BARO 0
#define SPI_ICM 1
#define SPI_HMC 2

uint8_t Spi_ReceiveData(uint8_t *pData, uint16_t size);
uint8_t Spi_TransmitData(uint8_t *pData, uint16_t size);
uint8_t Spi_TransmitReceiveData(uint8_t *pTxData, uint8_t *pRxData, uint16_t size);
void Spi_EnableDevice(uint8_t device);
void Spi_DisableDevice(uint8_t device);

uint8_t Spi_ReadDeviceBuffer(uint8_t device, uint8_t regAddr, uint8_t *pData, uint8_t size);
uint8_t Spi_ReadDeviceReg(uint8_t device, uint8_t regAddr, uint8_t *pData);
uint8_t Spi_WriteDeviceReg(uint8_t device, uint8_t reg, uint8_t value);

#endif
