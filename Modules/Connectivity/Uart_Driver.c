#include "Uart_Driver.h"

void Uart_SendString(const char str[]) {
	HAL_UART_Transmit_DMA(&huart1, (uint8_t *)str, strlen(str));
	HAL_Delay(1);
}

void Uart_SendChar(char c) {
	uint8_t temp[1] = {c};
	HAL_UART_Transmit_DMA(&huart1, temp, 1);
	HAL_Delay(1);
}

void Debug_Printf(const char *format,...) {
	#ifdef DEBUG
	char dat[36] = {0};
	char buf[30] = {0};
	va_list ap;
	va_start(ap, format);
	
	vsprintf(buf, format, ap);
	Uart_SendString(buf);
	
	va_end(ap);
	#endif
}

// void Uart_Printf(const char *format,...) {
// 	char dat[24] = {0};
// 	char buf[20] = {0};
// 	va_list ap;
// 	va_start(ap, format);
	
// 	vsprintf(buf, format, ap);
// 	Uart_SendString(buf);
	
// 	va_end(ap);
// }