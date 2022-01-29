#include "platform/UptimeInfoWin32.h"
#ifdef _WIN32
#include <windows.h>
unsigned long UptimeInfoAdapterWin32::tMillis()
{
    return static_cast<unsigned long>(GetTickCount());
}
#endif