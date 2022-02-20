#ifndef UPTIMEINFOADAPTERWIN32_h_
#define UPTIMEINFOADAPTERWIN32_h_
#include "IUptimeInfoPlatform.h"

class UptimeInfoWin32 : public IUptimeInfoPlatform {
  public:
   virtual unsigned long tMillis() const override;
};
#endif