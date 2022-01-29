#ifndef UPTIMEINFOSTM32_H_
#define UPTIMEINFOSTM32_H_
#include "IUptimeInfoPlatform.h"
class UptimeInfoSTM32 : public IUptimeInfoPlatform {
public:
unsigned long tMillis() override;
};
#endif