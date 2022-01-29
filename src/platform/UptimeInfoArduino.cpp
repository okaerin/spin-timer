#include "platform/UptimeInfoArduino.h"
#ifdef ARDUINO
#include <Arduino.h>
unsigned long UptimeInfoPlatformArduino::tMillis(){
    return millis();
}
#endif