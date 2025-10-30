/*
 * Framebuffer Activity Monitor
 * Reads directly from /dev/input/event* devices
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include "FramebufferIdle.h"

#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <iostream>
#include <stdexcept>

FramebufferIdle::FramebufferIdle()
{
  lastActivityTime = std::chrono::steady_clock::now();
  discoverInputDevices();
}

FramebufferIdle::~FramebufferIdle()
{
  stop();
}

std::vector<std::string> FramebufferIdle::findInputDevices()
{
  std::vector<std::string> devices;
  DIR* dir = opendir("/dev/input");
  
  if (!dir) {
    throw std::runtime_error("Cannot open /dev/input directory");
  }

  struct dirent* entry;
  while ((entry = readdir(dir)) != nullptr) {
    // Look for event devices (event0, event1, etc.)
    if (strncmp(entry->d_name, "event", 5) == 0) {
      std::string devicePath = std::string("/dev/input/") + entry->d_name;
      devices.push_back(devicePath);
    }
  }

  closedir(dir);
  return devices;
}

void FramebufferIdle::discoverInputDevices()
{
  auto devices = findInputDevices();
  
  for (const auto& device : devices) {
    int fd = open(device.c_str(), O_RDONLY | O_NONBLOCK);
    if (fd >= 0) {
      // Test if we can read from this device
      char name[256] = "Unknown";
      if (ioctl(fd, EVIOCGNAME(sizeof(name)), name) >= 0) {
        std::cout << "Found input device: " << device << " (" << name << ")" << std::endl;
        inputFds.push_back(fd);
      } else {
        close(fd);
      }
    } else {
      std::cerr << "Cannot open " << device << ": " << strerror(errno) << std::endl;
    }
  }

  if (inputFds.empty()) {
    throw std::runtime_error("No input devices found. Run with sudo or add user to 'input' group.");
  }
}

void FramebufferIdle::start()
{
  if (running) {
    return;
  }

  running = true;
  
  // Start a monitoring thread for each input device
  for (int fd : inputFds) {
    monitorThreads.emplace_back([this, fd]() {
      monitorDevice(fd);
    });
  }
}

void FramebufferIdle::stop()
{
  running = false;
  
  // Wait for all monitoring threads to finish
  for (auto& thread : monitorThreads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
  
  monitorThreads.clear();
  
  // Close all file descriptors
  for (int fd : inputFds) {
    close(fd);
  }
  inputFds.clear();
}

void FramebufferIdle::monitorDevice(int fd)
{
  struct input_event ev;
  fd_set readfds;
  struct timeval timeout;

  while (running) {
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    
    // 1 second timeout for select
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    int ret = select(fd + 1, &readfds, nullptr, nullptr, &timeout);
    
    if (ret > 0 && FD_ISSET(fd, &readfds)) {
      ssize_t bytesRead = read(fd, &ev, sizeof(ev));
      
      if (bytesRead == sizeof(ev)) {
        // Filter relevant events (ignore SYN events)
        if (ev.type == EV_KEY || ev.type == EV_REL || 
            ev.type == EV_ABS || ev.type == EV_MSC) {
          updateActivityTime();
        }
      }
    }
  }
}

void FramebufferIdle::updateActivityTime()
{
  std::lock_guard<std::mutex> lock(timeMutex);
  lastActivityTime = std::chrono::steady_clock::now();
}

std::chrono::milliseconds FramebufferIdle::operator()() const
{
  std::lock_guard<std::mutex> lock(timeMutex);
  auto now = std::chrono::steady_clock::now();
  auto idle = std::chrono::duration_cast<std::chrono::milliseconds>(
    now - lastActivityTime.load()
  );
  return idle;
}
