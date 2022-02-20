/*
 * UptimeInfo.h
 *
 *  Created on: 01.10.2013
 *      Author: niklausd
 */

#ifndef UPTIMEINFO_H_
#define UPTIMEINFO_H_
#include <memory>
class IUptimeInfoPlatform;
/**
 * Helper class to use the appropriate time base depending on framework.
 * Supported default frameworks:
 * - Arduino (AVR and SAM)
 * - POSIX
 */
class UptimeInfo {
  public:
   static UptimeInfo* Instance();

  protected:
  public:
   virtual ~UptimeInfo() = default;

   void setStrategy(std::shared_ptr<IUptimeInfoPlatform> adapter);

   std::shared_ptr<IUptimeInfoPlatform> adapter();

   /**
    * Returns the number of milliseconds since the program started.
    * @return Number of milliseconds since the program started.
    */
   unsigned long tMillis();

  private:
   std::shared_ptr<IUptimeInfoPlatform> m_adapter;

   UptimeInfo();
   std::shared_ptr<IUptimeInfoPlatform> defaultStrategy() const;
// forbidden member functions
#if __cplusplus >= 201103L  // at least C++11
  private:
   UptimeInfo& operator=(const UptimeInfo& src) =
       delete;                                  // assignment operator
   UptimeInfo(const UptimeInfo& src) = delete;  // copy constructor
#else
  private:
   UptimeInfo& operator=(const UptimeInfo& src);  // assignment operator
   UptimeInfo(const UptimeInfo& src);             // copy constructor
#endif
};

#endif /* UPTIMEINFO_H_ */
