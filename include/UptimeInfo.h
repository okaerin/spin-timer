/*
 * UptimeInfo.h
 *
 *  Created on: 01.10.2013
 *      Author: niklausd
 */

#ifndef UPTIMEINFO_H_
#define UPTIMEINFO_H_

class IUptimeInfoPlatform;
/**
 * Helper class to use the appropriate time base depending on framework.
 * Supported default frameworks:
 * - Arduino (AVR and SAM)
 * - POSIX
 */
class UptimeInfo
{
public:
  static UptimeInfo* Instance(); 

protected:
  

public:
  virtual ~UptimeInfo();

  void setAdapter(IUptimeInfoPlatform* adapter);

  IUptimeInfoPlatform* adapter();

  /**
   * Returns the number of milliseconds since the program started.
   * @return Number of milliseconds since the program started.
   */
  unsigned long tMillis();

private:
  IUptimeInfoPlatform* m_adapter;
  IUptimeInfoPlatform* defaultStrategy() const;
  
  UptimeInfo();
// forbidden member functions
#if __cplusplus >=201103L // at least C++11
private:
  
  UptimeInfo& operator = (const UptimeInfo& src) = delete; // assignment operator
  UptimeInfo(const UptimeInfo& src) = delete;              // copy constructor
#else
private:
  UptimeInfo& operator = (const UptimeInfo& src); // assignment operator
  UptimeInfo(const UptimeInfo& src);              // copy constructor
#endif
};

#endif /* UPTIMEINFO_H_ */
