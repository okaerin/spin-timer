#include "platform/UptimeInfoChrono.h"
UptimeInfoChrono::UptimeInfoChrono() {
   m_start = std::chrono::steady_clock::now();
}
unsigned long UptimeInfoChrono::tMillis() const {
   auto now = std::chrono::steady_clock::now();
   auto elapsed =
       std::chrono::duration_cast<std::chrono::milliseconds>(now - m_start);
   unsigned long ms = elapsed.count();
   return ms;
}