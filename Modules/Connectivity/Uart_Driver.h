#ifndef __UART_DRIVER_H
#define __UART_DRIVER_H

#include "usart.h"
#include "string.h"
#include "stdio.h"
#include "stdarg.h"

void Uart_SendString(const char str[]);
void Uart_SendChar(char c);
void Uart_Printf(const char *format,...);
void Debug_Printf(const char *format,...);

#endif
