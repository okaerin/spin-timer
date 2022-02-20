#ifndef UPTIMEINFOCHRONO_H_
#define UPTIMEINFOCHRONO_H_
#include "IUptimeInfoPlatform.h"

#include <chrono>
class UptimeInfoChrono : public IUptimeInfoPlatform {
  public:
   UptimeInfoChrono();
   unsigned long tMillis() const override;

  private:
   std::chrono::time_point<std::chrono::steady_clock> m_start;
};
#endif