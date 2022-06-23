/*
 * SpinTimer.h
 *
 *  Created on: 13.08.2013
 *      Author: niklausd
 */

#ifndef SPINTIMER_H_
#define SPINTIMER_H_

#include <memory>
/**
 * Universal Timer.
 *
 * Features:
 * - intended use: encapsulate recurring and non-recurring timed actions with a
 * non-busy wait approach for time spans in a range of 0 to thousands of
 * milliseconds, such as:
 *   - debouncing push-button and switch signals (recommended interval: 50 ms)
 *   - blink some LEDs
 *   - schedule some sequences where time accuracy is not crucial
 * - configurable to be either
 *   - recurring (timer automatically restarts after the interval) or
 *   - non-recurring (timer stops after timeout period is over)
 * - timer interval/timeout time configurable ([ms])
 * - automatically attaches to SpinTimerContext's linked list of SpinTimer
 * objects. As long as the SpinTimerContext::handleTick() will be called , this
 * will periodically update the timers' states and thus perform the timers'
 * expire evaluations
 * - based on system uptime (number of milliseconds since the system began
 * running the current program, i.e. Arduino: millis() function or STM32:
 * HAL_GetTick() function),
 * - handles system time overflows correctly (unsigned long int type, occurring
 * around every 50 hours)
 *
 * Integration:
 *
 * (shown on the basis of a simple Arduino Framework application toggling the
 * board's built-in LED)
 *
 * - Include
 *
 *       #include "SpinTimer.h"
 *       #include "Arduino.h"
 *
 * - Timer interval constant definition
 *
 *       const unsigned int BLINK_TIME_MILLIS = 200;
 *
 * - specific SpinTimerAction implementation, periodically toggling the built-in
 * LED
 *
 *       class BlinkTimerAction : public SpinTimerAction
 *       {
 *       public:
 *         void timeExpired()
 *         {
 *           digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
 *         }
 *       };
 *
 * - Setup: set LED pin to output; create recurring Timer, inject specific
 * TimerAction
 *
 *       // The setup function is called once at startup of the sketch
 *       void setup()
 *       {
 *         pinMode(LED_BUILTIN, OUTPUT);
 *         new SpinTimer(BLINK_TIME_MILLIS, new BlinkTimerAction(),
 * SpinTimer::IS_RECURRING, SpinTimer::IS_AUTOSTART);
 *       }
 *
 * - Loop: call SpinTimerContext::instance()->handleTick();
 *
 *       // The loop function is called in an endless loop
 *       void loop()
 *       {
 *         SpinTimerContext::instance()->handleTick();
 *       }
 *
 * .
 */
class ISpinTimerAction;
class SpinTimer {
   friend class SpinTimerContext;

  public:
   // options
   enum EFrequency {
      /**
       * Constant for frequency parameter of the constructor (@see
       * SpinTimer()), to create a one shot timer.
       */
      SINGLESHOT,
      /**
       * Constant for frequency parameter of the constructor (@see
       * SpinTimer()), to create a recurring timer.
       */
      RECURRING
   };
   enum EStart {
      /**
       * Options for start mode parameter of the constructor (@see SpinTimer()),
       * to create a timer which does start after creation.
       */
      AUTO,
      /**
       * Options for start mode parameter of the constructor (@see SpinTimer()),
       * to create a timer which does not start after creation.
       */
      MANUAL
   };

   /**
    * Timer constructor.
    * @param timeMillis Time out or interval time to be set for the timer [ms];
    * 0 will make the timer expire as soon as possible.
    * @param action SpinTimerAction, is able to emit a timer expired event to
    * any specific listener, default: 0 (no event will be sent)
    * @param freq Operation mode, recurring, singleshot
    * default: singleshot
    * @param start_mode Autostart mode, autostart enabled, autostart disabled,
    * default: disabled
    */
   SpinTimer(unsigned long timeMillis,
             std::unique_ptr<ISpinTimerAction> action = nullptr,
             EFrequency freq = EFrequency::SINGLESHOT,
             EStart start_mode = EStart::MANUAL);

   /**
    * Timer destructor.
    * Will detach itself from TimerContext.
    */
   virtual ~SpinTimer();

   /**
    * reset specific SpinTimerAction, former action can be replaced. Ownership
    * of action is transferred.
    * @param action Specific SpinTimerAction
    */
   void resetAction(std::unique_ptr<ISpinTimerAction> action);

  protected:
   /**
    * Get next SpinTimer object pointer out of the linked list containing
    * timers.
    * @return SpinTimer object pointer or 0 if current object is the trailing
    * list element.
    */
   SpinTimer* next() const;

   /**
    * Set next SpinTimer object of the linked list containing timers.
    * @param timer SpinTimer object pointer to be set as the next element of the
    * list.
    */
   void setNext(SpinTimer* timer);

  public:
   /**
    * Start or restart the timer with a specific time out or interval time.
    * @param timeMillis Time out or interval time to be set for the timer [ms];
    * 0 will make the timer expire as soon as possible.
    */
   void start(unsigned long timeMillis);

   /**
    * Start or restart the timer.
    * The timer will expire after the specified time set with the constructor or
    * start(timeMillis) before.
    */
   void start();

   /**
    * Cancel the timer and stop. No time expired event will be sent out after
    * the specified time would have been elapsed. Subsequent isExpired() queries
    * will return false.
    */
   void cancel();

   /**
    * Poll method to get the timer expire status, recalculates whether the timer
    * has expired before. This method could be used in a pure polling mode,
    * where tick() has not to get called (by the TimerContext::handleTick()
    * method), but also a mixed operation in combination with calling tick()
    * periodically is possible. Subsequent isExpired() queries will return false
    * after the first one returned true, as long as the time did not expire
    * again in case of a recurring timer.
    * @return true if the timer has expired.
    */
   bool isExpired();

   /**
    * Indicates whether the timer is currently running.
    * @return true if timer is running.
    */
   bool isRunning() const;

   /**
    * Returns the current interval of the timer.
    * @return Timer interval/timeout time [ms].
    */
   unsigned long getInterval() const;

   /**
    * Sets the operation mode
    * @param isRecurring Operation mode, true: recurring, false: non-recurring
    */
   void setIsRecurring(bool isRecurring);

   /**
    * Kick the Timer.
    * Recalculates whether the timer has expired.
    */
   void tick();

  private:
   /**
    * Internal tick method, evaluates the expired state.
    */
   void internalTick();

   /**
    * Starts time interval measurement, calculates the expiration trigger time.
    * Manages to avoid unsigned long int overflow issues occurring around every
    * 50 hours.
    */
   void startInterval();

  private:
   bool m_isRunning;  /// Timer is running flag, true: timer is running, false:
                      /// timer is stopped.
   bool m_isRecurring;    /// Timer mode flag, true: timer will automatically
                          /// restart after expiration.
   bool m_isExpiredFlag;  /// Timer expiration flag.
   bool m_willOverflow;   /// UptimeInfo::Instance()->tMillis() will overflow
                          /// during new started interval.
   unsigned long m_currentTimeMillis;  /// interval time measurement base,
                                       /// updated every internalTick(), called
                                       /// either by tick() or by isExpired()
   unsigned long m_triggerTimeMillis;
   unsigned long m_triggerTimeMillisUpperLimit;
   unsigned long m_delayMillis;
   std::unique_ptr<ISpinTimerAction> m_action;
   SpinTimer* m_next;

  private:  // forbidden default functions
   SpinTimer& operator=(const SpinTimer& src) = delete;  // assignment operator
   SpinTimer(const SpinTimer& src) = delete;             // copy constructor
};

#endif /* SPINTIMER_H_ */
