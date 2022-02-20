/*
 * UptimeInfo.cpp
 *
 *  Created on: 01.10.2013
 *      Author: niklausd
 */
#include "UptimeInfo.h"
#include "platform/UptimeInfoArduino.h"
#include "platform/UptimeInfoPosix.h"
#include "platform/UptimeInfoSTM32.h"
#include "platform/UptimeInfoWin32.h"

UptimeInfo::UptimeInfo() { m_adapter = defaultStrategy(); }
UptimeInfo* UptimeInfo::Instance() {
   static UptimeInfo instance;
   return &instance;
}
std::shared_ptr<IUptimeInfoPlatform> UptimeInfo::defaultStrategy() const {
   std::shared_ptr<IUptimeInfoPlatform> local_adapter;
#if defined(ARDUINO)
   local_adapter = std::make_shared<UptimeInfoArduino>();
#elif defined(ESP32)
   local_adapter = std::make_shared<UptimeInfoSTM32>();
#elif defined(__linux__)
   local_adapter = std::make_shared<UptimeInfoPosix>();
#elif defined _WIN32
   local_adapter = std::make_shared<UptimeInfoWin32>();
#else
#pragma message( \
    "warning no default Uptime provider. Please provide one to UptimeInfo::setStrategy")
#endif
   return local_adapter;
}
void UptimeInfo::setStrategy(std::shared_ptr<IUptimeInfoPlatform> adapter) {
   m_adapter = adapter;
}

std::shared_ptr<IUptimeInfoPlatform> UptimeInfo::adapter() { return m_adapter; }
unsigned long UptimeInfo::tMillis() {
   unsigned long ms = 0;
   auto local_adapter = adapter();
   if (local_adapter.get()) {
      ms = local_adapter->tMillis();
   }
   return ms;
}
