/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef XIDLE_H
#define XIDLE_H

#include <X11/Xlib.h>
#include <chrono>

class Xidle final
{
public:
  Xidle();
  ~Xidle();

  std::chrono::milliseconds operator()() const;

private:
  Display *display;

};

#endif
