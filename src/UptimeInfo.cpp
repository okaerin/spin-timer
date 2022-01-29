/*
 * UptimeInfo.cpp
 *
 *  Created on: 01.10.2013
 *      Author: niklausd
 */
#include "UptimeInfo.h"
#include "platform/UptimeInfoArduino.h"
#include "platform/UptimeInfoPosix.h"
#include "platform/UptimeInfoWin32.h"

#include <stdexcept>

UptimeInfo* UptimeInfo::Instance(){
  static UptimeInfo instance;
  return &instance;
}

UptimeInfo::UptimeInfo()
{
  m_adapter = nullptr;
#if defined(ARDUINO)
  s_adapter = new UptimeInfoAdapterArduino();
#elif defined(__linux__)
  s_adapter = new UptimeInfoAdapterPosix();
#elif _WIN32
  m_adapter = new UptimeInfoAdapterWin32();
#else
  throw std::runtime_error("missing platform implementation");
#endif
}

UptimeInfo::~UptimeInfo()
{
  delete m_adapter;
  m_adapter = nullptr;
}

void UptimeInfo::setAdapter(IUptimeInfoPlatform* adapter)
{
  m_adapter = adapter;
}

IUptimeInfoPlatform* UptimeInfo::adapter(){
  return m_adapter;
}
unsigned long UptimeInfo::tMillis(){
  unsigned long ms = 0;
  IUptimeInfoPlatform* local_adapter = adapter();
  if (local_adapter)
  {
    ms = local_adapter->tMillis();
  }
  return ms;
}
