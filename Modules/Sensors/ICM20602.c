#include "ICM20602.h"

uint8_t ICM20_Init(Sens_ICM20 *handle) {
	Debug_Printf("ICM20602 initial started.\r\n");
	Sys_Delay(10);

	if(Spi_WriteDeviceReg(SPI_ICM, ICM20_PWR_MGMT_1, 0X80)) {
		return 1;
	}
	
	Sys_Delay(50);
	Spi_WriteDeviceReg(SPI_ICM, ICM20_PWR_MGMT_1, 0x01);
	Sys_Delay(50);
	
	uint8_t id,status;
	//status = ICM20_ReadReg(handle, ICM20_WHO_AM_I, &id); 
	status = Spi_ReadDeviceReg(SPI_ICM, ICM20_WHO_AM_I, &id);
	if(id == 0xAF) {
		Debug_Printf("ICM20602 ID=%x\r\n", id);
	}
	else {
		return 1;
	}
	
	Spi_WriteDeviceReg(SPI_ICM, ICM20_SMPLRT_DIV, 0); 
	Spi_WriteDeviceReg(SPI_ICM, ICM20_CONFIG, DLPF_BW_20); 
	Spi_WriteDeviceReg(SPI_ICM, ICM20_ACCEL_CONFIG2, ACCEL_AVER_4 | ACCEL_DLPF_BW_21);
	
	ICM20_SetAccelFullScale(handle, ICM20_ACCEL_FS_8G);
	status = ICM20_SetGytoFullScale(handle, ICM20_GYRO_FS_2000);
	
	Sys_Delay(100);
	if(status == 0) {
		//Debug_Printf("ICM20602 initial succeeded.\r\n\r\n");
	}
	else {
		return 1;
	}
	
	return 0;
}

uint8_t ICM20_SetGytoFullScale(Sens_ICM20 *handle, uint8_t fs) {
	switch(fs) {
		case ICM20_GYRO_FS_250:
				handle->gyro_scale = 1.0f/131.068f;
		break;
		case ICM20_GYRO_FS_500:
				handle->gyro_scale = 1.0f/65.534f;
		break;
		case ICM20_GYRO_FS_1000:
				handle->gyro_scale = 1.0f/32.767f;
		break;
		case ICM20_GYRO_FS_2000:
				handle->gyro_scale = 1.0f/16.4f;
		break;
		default:
			fs = ICM20_GYRO_FS_2000;
			handle->gyro_scale = 1.0f/16.4f;
		break;
	}
	
	return Spi_WriteDeviceReg(SPI_ICM, ICM20_GYRO_CONFIG, fs);
}

uint8_t ICM20_SetAccelFullScale(Sens_ICM20 *handle, uint8_t fs) {
	switch(fs) {
		case ICM20_ACCEL_FS_2G:
				handle->gyro_scale = 1.0f/16348.0f;
		break;
		case ICM20_ACCEL_FS_4G:
				handle->gyro_scale = 1.0f/8192.0f;
		break;
		case ICM20_ACCEL_FS_8G:
				handle->gyro_scale = 1.0f/4096.0f;
		break;
		case ICM20_ACCEL_FS_16G:
				handle->gyro_scale = 1.0f/2048.0f;
		break;
		default:
			fs = ICM20_ACCEL_FS_8G;
			handle->gyro_scale = 1.0f/4096.0f;
		break;
	}
	
	return Spi_WriteDeviceReg(SPI_ICM, ICM20_ACCEL_CONFIG, fs);
}

uint8_t ICM20_GetAccelADC(Sens_ICM20 *handle) {
	uint8_t buf[6];
	
	if(Spi_ReadDeviceBuffer(SPI_ICM, ICM20_ACCEL_XOUT_H, buf, 6)) {
		return 1;
	}
	
	handle->accel_adc[0] = ((int16_t)buf[0]<<8) + buf[1];
	handle->accel_adc[1] = ((int16_t)buf[2]<<8) + buf[3];
	handle->accel_adc[2] = ((int16_t)buf[4]<<8) + buf[5];
	
	return 0;
}

uint8_t ICM20_GetGyroADC(Sens_ICM20 *handle) {
	uint8_t buf[6];
	
	if(Spi_ReadDeviceBuffer(SPI_ICM, ICM20_GYRO_XOUT_H, buf, 6)) {
		return 1;
	}
	
	handle->gyro_adc[0] = ((int16_t)buf[0]<<8) + buf[1];
	handle->gyro_adc[1] = ((int16_t)buf[2]<<8) + buf[3];
	handle->gyro_adc[2] = ((int16_t)buf[4]<<8) + buf[5];
	
	return 0;
}

uint8_t ICM20_GetAccel(Sens_ICM20 *handle) {
	if(ICM20_GetAccelADC(handle)) {
		return 1;
	}
	
	handle->accel[0] = handle->accel_scale * handle->accel_adc[0];
	handle->accel[1] = handle->accel_scale * handle->accel_adc[1];
	handle->accel[2] = handle->accel_scale * handle->accel_adc[2];
	
	return 0;
}

uint8_t ICM20_GetGyro(Sens_ICM20 *handle) {
	if(ICM20_GetGyroADC(handle)) {
		return 1;
	}
	
	handle->gyro[0] = handle->gyro_scale * handle->gyro_adc[0];
	handle->gyro[1] = handle->gyro_scale * handle->gyro_adc[1];
	handle->gyro[2] = handle->gyro_scale * handle->gyro_adc[2];
	
	return 0;
}

uint8_t ICM20_GetTemperatue(Sens_ICM20 *handle) {
	uint16_t temp_adc;
	uint8_t buf[2];
	if(Spi_ReadDeviceBuffer(SPI_ICM, ICM20_TEMP_OUT_H, buf, 2)) {
		return 1;
	}
	temp_adc = (buf[0]<<8) + buf[1];
	Debug_Printf("temp adc:%d\n\r",temp_adc);
	handle->temperature = (25.0f + (float)temp_adc/326.8f);
	
	return 0;
}
