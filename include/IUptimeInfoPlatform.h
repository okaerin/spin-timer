#ifndef IUPTIMEINFOADAPTER_H_
#define IUPTIMEINFOADAPTER_H_
/**
 * Adapter Interface, will call-out the platform specific up-time info time in
 * milliseconds.
 */
class IUptimeInfoPlatform {
  public:
   virtual ~IUptimeInfoPlatform() {}
   /**
    * Up-time query call-out. To be implemented according to platform specific
    * circumstances.
    * @return Number of milliseconds since the program started.
    */
   virtual unsigned long tMillis() const = 0;
};
#endif