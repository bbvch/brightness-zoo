/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#include "Xidle.h"

#include "idletime.h"

#include <X11/extensions/scrnsaver.h>

#include <stdexcept>

Xidle::Xidle()
{
  int event_basep, error_basep;

  display = XOpenDisplay(NULL);
  if (display == nullptr) {
    throw std::runtime_error("could not open display");
  }

  if (!XScreenSaverQueryExtension(display, &event_basep, &error_basep)) {
    throw std::runtime_error("screen saver extension not supported");
  }
}

Xidle::~Xidle()
{
  XCloseDisplay(display);
}

std::chrono::milliseconds Xidle::operator()() const
{
  XScreenSaverInfo ssi;

  if (!XScreenSaverQueryInfo(display, DefaultRootWindow(display), &ssi)) {
    throw std::runtime_error("could not get screen saver info");
  }

  auto milliseconds = workaroundCreepyXServer(display, ssi.idle);
  return std::chrono::milliseconds{milliseconds};
}
