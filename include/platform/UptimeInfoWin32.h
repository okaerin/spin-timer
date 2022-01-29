#ifndef UPTIMEINFOADAPTERWIN32_h_
#define UPTIMEINFOADAPTERWIN32_h_
#ifdef _WIN32
#include "IUptimeInfoPlatform.h"

class UptimeInfoAdapterWin32 : public IUptimeInfoPlatform
{
public:
  virtual unsigned long tMillis() override;
};
#endif
#endif