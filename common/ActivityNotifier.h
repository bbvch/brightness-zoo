/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef ACTIVITYNOTIFIER_H
#define ACTIVITYNOTIFIER_H

#include <QObject>
#include <chrono>
#include <functional>

class ActivityNotifier :
    public QObject
{
  Q_OBJECT
public:
  typedef std::function<std::chrono::milliseconds()> IdleGetter;

  ActivityNotifier(std::chrono::seconds timeout, IdleGetter idle, QObject *parent = 0);

signals:
  void active();
  void inactive();

public slots:
  void check();

private:
  enum class State {
    Boot,
    Active,
    Inactive
  };

  std::chrono::seconds timeout{5};
  IdleGetter idle;
  State state{State::Boot};

  bool isActive() const;
  void setState(State value);
  void notifyAboutNewState();

};

#endif
