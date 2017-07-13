/*
 * (C) Copyright 2017
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#pragma once

#include <QObject>


class ProblemHandler : public QObject
{
  Q_OBJECT
public:

public slots:
  void error(QString message);

};
