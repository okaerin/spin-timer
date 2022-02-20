/*
 * SpinTimer.cpp
 *
 *  Created on: 13.08.2013
 *      Author: niklausd
 */

#include "SpinTimer.h"
#include "ISpinTimerAction.h"

#include "SpinTimerContext.h"
#include "UptimeInfo.h"

#include <limits.h>

void scheduleTimers() { SpinTimerContext::instance()->handleTick(); }

void delayAndSchedule(unsigned long delayMillis) {
   // create a one-shot timer on the fly
   SpinTimer delayTimer(delayMillis, nullptr, SpinTimer::EFrequency::SINGLESHOT,
                        SpinTimer::EStart::AUTO);

   // wait until the timer expires
   while (!delayTimer.isExpired()) {
      // schedule the timer above and all the other timers, so they will still
      // run in 'parallel'
      scheduleTimers();
   }
}

SpinTimer::SpinTimer(unsigned long timeMillis,
                     std::unique_ptr<ISpinTimerAction> action, EFrequency freq,
                     EStart start_mode)
    : m_isRunning(false),
      m_isRecurring(freq == EFrequency::RECURRING),
      m_isExpiredFlag(false),
      m_willOverflow(false),
      m_currentTimeMillis(0),
      m_triggerTimeMillis(0),
      m_triggerTimeMillisUpperLimit(ULONG_MAX),
      m_delayMillis(timeMillis),
      m_action(std::move(action)),
      m_next(0) {
   SpinTimerContext::instance()->attach(this);

   if (start_mode == EStart::AUTO) {
      start();
   }
}

SpinTimer::~SpinTimer() { SpinTimerContext::instance()->detach(this); }

void SpinTimer::resetAction(std::unique_ptr<ISpinTimerAction> action) {
   m_action.reset(action.release());
}

SpinTimer* SpinTimer::next() const { return m_next; }

void SpinTimer::setNext(SpinTimer* timer) { m_next = timer; }

bool SpinTimer::isExpired() {
   internalTick();
   bool isExpired = m_isExpiredFlag;
   m_isExpiredFlag = false;
   return isExpired;
}

bool SpinTimer::isRunning() const { return m_isRunning; }

unsigned long SpinTimer::getInterval() const { return m_delayMillis; }

void SpinTimer::setIsRecurring(bool isRecurring) {
   m_isRecurring = isRecurring;
}

void SpinTimer::tick() { internalTick(); }

void SpinTimer::cancel() {
   m_isRunning = false;
   m_isExpiredFlag = false;
}

void SpinTimer::start(unsigned long timeMillis) {
   m_isRunning = true;
   m_delayMillis = timeMillis;
   m_currentTimeMillis = UptimeInfo::Instance()->tMillis();
   startInterval();
}

void SpinTimer::start() {
   m_isRunning = true;
   m_currentTimeMillis = UptimeInfo::Instance()->tMillis();
   startInterval();
}

void SpinTimer::startInterval() {
   unsigned long deltaTime = ULONG_MAX - m_currentTimeMillis;
   m_willOverflow = (deltaTime < m_delayMillis);
   if (m_willOverflow) {
      // overflow will occur
      m_triggerTimeMillis = m_delayMillis - deltaTime - 1;
      m_triggerTimeMillisUpperLimit = m_currentTimeMillis;
   } else {
      m_triggerTimeMillis = m_currentTimeMillis + m_delayMillis;
      m_triggerTimeMillisUpperLimit = ULONG_MAX - deltaTime;
   }
}

void SpinTimer::internalTick() {
   bool intervalIsOver = false;

   m_currentTimeMillis = UptimeInfo::Instance()->tMillis();

   // check if interval is over as long as the timer shall be running
   if (m_isRunning) {
      if (m_willOverflow) {
         intervalIsOver =
             ((m_triggerTimeMillis <= m_currentTimeMillis) &&
              (m_currentTimeMillis < m_triggerTimeMillisUpperLimit));
      } else {
         intervalIsOver =
             ((m_triggerTimeMillis <= m_currentTimeMillis) ||
              (m_currentTimeMillis < m_triggerTimeMillisUpperLimit));
      }

      if (intervalIsOver) {
         // interval is over
         if (m_isRecurring) {
            // start next interval
            startInterval();
         } else {
            m_isRunning = false;
         }

         m_isExpiredFlag = true;
         if (0 != m_action) {
            m_action->timeExpired();
         }
      }
   }
}
