#include "platform/UptimeInfoPosix.h"
#ifdef __linux__
#include <sys/time.h>
unsigned long UptimeInfoPosix::tMillis() const {
   /**
    * @see http://stackoverflow.com/a/1952423
    */
   struct timeval tp;
   gettimeofday(&tp, 0);
   unsigned long ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
   return ms;
}
#endif