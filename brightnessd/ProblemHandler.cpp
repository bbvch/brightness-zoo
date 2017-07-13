/*
 * (C) Copyright 2017
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "ProblemHandler.h"

#include <QCoreApplication>
#include <iostream>


ProblemHandler::ProblemHandler(bool _verbose) :
  verbose{_verbose}
{
}

void ProblemHandler::error(QString message)
{
  std::cerr << message.toStdString() << std::endl;
  QCoreApplication::exit(-6);
}

void ProblemHandler::info(QString message)
{
  if (verbose) {
    std::cout << message.toStdString() << std::endl;
  }
}
