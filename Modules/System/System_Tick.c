#include "System_Tick.h"

/**
  * @brief This function provides accurate delay (in milliseconds) based 
  *        on variable incremented.
  * @param delay specifies the delay time length, in milliseconds.
  * @retval None
  */
void Sys_Delay(uint16_t delay) {
	HAL_Delay(delay);
}