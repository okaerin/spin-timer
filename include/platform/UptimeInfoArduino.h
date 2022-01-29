#ifndef UPTIMEINFOPLATFORMARDUINO_H_
#define UPTIMEINFOPLATFORMARDUINO_H_
#ifdef ARDUINO
#include "IUptimeInfoAdapter.h"

class UptimeInfoPlatformArduino : public IUptimeInfoPlatform
{
public:
  unsigned long tMillis();
};
#endif
#endif