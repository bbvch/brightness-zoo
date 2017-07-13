/*
 * (C) Copyright 2017
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "ProblemHandler.h"

#include <QCoreApplication>
#include <iostream>


void ProblemHandler::error(QString message)
{
  std::cerr << message.toStdString() << std::endl;
  QCoreApplication::exit(-6);
}

