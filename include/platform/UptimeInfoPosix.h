#ifndef UPTIMEINFOPLATFORMPOSIX_H_
#define UPTIMEINFOPLATFORMPOSIX_H_
#include "IUptimeInfoPlatform.h"
class UptimeInfoPosix : public IUptimeInfoPlatform {
  public:
   unsigned long tMillis() const override;
};
#endif