#include "platform/UptimeInfoArduino.h"
#ifdef ARDUINO
#include <Arduino.h>
unsigned long UptimeInfoArduino::tMillis() const { return millis(); }
#endif