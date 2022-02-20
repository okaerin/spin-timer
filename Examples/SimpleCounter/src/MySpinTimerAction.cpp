#include "MySpinTimerAction.h"

MySpinTimerAction::MySpinTimerAction(std::function<void(void)> callback)
    : m_callback(callback){};

void MySpinTimerAction::timeExpired() { m_callback(); }