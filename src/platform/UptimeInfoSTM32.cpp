#include "platform/UptimeInfoSTM32.h"
#ifdef ESP32
#include <stm32l4xx_hal.h>
unsigned long UptimeInfoSTM32::tMillis() const {
   unsigned long ms = HAL_GetTick();
   return ms;
}
#endif