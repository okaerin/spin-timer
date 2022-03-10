/**
 ******************************************************************************
 * @file           : main.cpp
 * @brief          : Simple counter example to demonstrate the use of the
 *                   SpinTimer library
 ******************************************************************************
 */

#include <chrono>
#include <iostream>
#include <thread>

#include "MySpinTimerAction.h"
#include "SpinTimer.h"
#include "SpinTimerContext.h"

bool run_app = true;
#ifdef _WIN32
#include <windows.h>
BOOL WINAPI consoleHandler(DWORD signal) {
   if (signal == CTRL_C_EVENT) {
      run_app = false;  // do cleanup
   }
   return TRUE;
}
#else
#include <signal.h>
void signal_handler(int sig) {
   if (sig == SIGINT) {
      run_app = false;  // do cleanup
   }
}
#endif
int main(void) {
// setup signal/console handlers
#ifdef _WIN32
   if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
      std::cerr << std::endl
                << "ERROR: Could not set console control handler" << std::endl;
      return 1;
   }
#else
   signal(SIGINT, signal_handler);
#endif
   constexpr int spinTimer_1s_millis = 1000;
   constexpr int spinTimer_2s_millis = 2000;
   constexpr int spinTimer_5s_millis = 5000;

   uint32_t count1 = 0;
   uint32_t count2 = 0;
   uint32_t count3 = 0;

   SpinTimer spinTimer1sec(
       spinTimer_1s_millis,
       std::unique_ptr<MySpinTimerAction>{
           new MySpinTimerAction([&count1]() { count1++; })},
       SpinTimer::EFrequency::RECURRING, SpinTimer::EStart::AUTO);
   SpinTimer spinTimer2sec(
       spinTimer_2s_millis,
       std::unique_ptr<MySpinTimerAction>{
           new MySpinTimerAction([&count2]() { count2++; })},
       SpinTimer::EFrequency::RECURRING, SpinTimer::EStart::AUTO);
   SpinTimer spinTimer5sec(
       spinTimer_5s_millis,
       std::unique_ptr<MySpinTimerAction>{
           new MySpinTimerAction([&count3]() { count3++; })},
       SpinTimer::EFrequency::RECURRING, SpinTimer::EStart::AUTO);

   // Forever Loop
   while (run_app) {
      std::cout << "SpinTimer_1s: " << count1 << std::endl;
      std::cout << "SpinTimer_2s: " << count2 << std::endl;
      std::cout << "SpinTimer_5s: " << count3 << "\e[A\e[A\r" << std::endl;

      SpinTimerContext::instance()->handleTick();

      std::this_thread::sleep_for(std::chrono::milliseconds(100));
   }

   return 0;
}