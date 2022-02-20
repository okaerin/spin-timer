#pragma once

#include <functional>
#include "ISpinTimerAction.h"

class MySpinTimerAction : public ISpinTimerAction {
  private:
   std::function<void(void)> m_callback;

  public:
   MySpinTimerAction(std::function<void(void)> callback);

   void timeExpired() override;
};