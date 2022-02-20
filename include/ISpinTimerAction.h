#ifndef ISPINTIMERACTION_H_
#define ISPINTIMERACTION_H_
/**
 * Action Interface, will notify timeExpired() event.
 * Implementations derived from this interface can be injected into a Timer
 * object. The Timer then will call out the specific action's timeExpired()
 * method.
 */
class ISpinTimerAction {
  public:
   ISpinTimerAction() = default;
   virtual ~ISpinTimerAction() {}

   /**
    * Time expired event. To be implemented by specific Timer Action class.
    */
   virtual void timeExpired() = 0;

  private:  // forbidden functions
   ISpinTimerAction(const ISpinTimerAction& src) = delete;  // copy constructor
   ISpinTimerAction& operator=(const ISpinTimerAction& src) =
       delete;  // assignment operator
};
#endif