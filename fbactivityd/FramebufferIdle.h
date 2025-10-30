/*
 * Framebuffer Activity Monitor
 * Reads directly from /dev/input/event* devices
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef FRAMEBUFFERIDLE_H
#define FRAMEBUFFERIDLE_H

#include <chrono>
#include <vector>
#include <string>
#include <atomic>
#include <thread>
#include <mutex>

class FramebufferIdle final
{
public:
  FramebufferIdle();
  ~FramebufferIdle();

  // Returns milliseconds since last input event
  std::chrono::milliseconds operator()() const;

  // Start monitoring input devices
  void start();
  
  // Stop monitoring
  void stop();

private:
  std::atomic<std::chrono::steady_clock::time_point> lastActivityTime;
  std::vector<int> inputFds;
  std::vector<std::thread> monitorThreads;
  std::atomic<bool> running{false};
  mutable std::mutex timeMutex;

  void discoverInputDevices();
  void monitorDevice(int fd);
  void updateActivityTime();
  std::vector<std::string> findInputDevices();
};

#endif
