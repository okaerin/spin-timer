#include "platform/UptimeInfoWin32.h"
#ifdef _WIN32
#include <windows.h>
unsigned long UptimeInfoWin32::tMillis() const {
   return static_cast<unsigned long>(GetTickCount());
}
#endif