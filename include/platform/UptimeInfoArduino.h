#ifndef UPTIMEINFOPLATFORMARDUINO_H_
#define UPTIMEINFOPLATFORMARDUINO_H_
#include "IUptimeInfoPlatform.h"

class UptimeInfoArduino : public IUptimeInfoPlatform {
  public:
   unsigned long tMillis() const override;
};

#endif