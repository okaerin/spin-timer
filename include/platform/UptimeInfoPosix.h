#ifdef UPTIMEINFOADAPTERPOSIX_H_
#define UPTIMEINFOADAPTERPOSIX_H_
#include "IUptimeInfoPlatform.h"
class UptimeInfoPlatformPosix : public IUptimeInfoPlatform
{
public:
  unsigned long tMillis();
};
#endif