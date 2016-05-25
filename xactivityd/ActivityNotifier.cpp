/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 * SPDX-License-Identifier:	GPL-2.0
 */

#include "ActivityNotifier.h"

ActivityNotifier::ActivityNotifier(std::chrono::seconds _timeout, IdleGetter _idle, QObject *parent) :
  QObject{parent},
  timeout{_timeout},
  idle{_idle}
{
}

void ActivityNotifier::check()
{
  auto newState = isActive() ? State::Active : State::Inactive;
  setState(newState);
}

bool ActivityNotifier::isActive() const
{
  auto durationSinceLastActivity = idle();
  return durationSinceLastActivity < timeout;
}

void ActivityNotifier::setState(ActivityNotifier::State value)
{
  if (state != value) {
    state = value;
    notifyAboutNewState();
  }
}

void ActivityNotifier::notifyAboutNewState()
{
  switch (state) {
  case State::Boot:
    break;
  case State::Active:
    active();
    break;
  case State::Inactive:
    inactive();
    break;
  }
}
