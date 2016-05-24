/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include <QCoreApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  QTimer::singleShot(100, &a, SLOT(quit()));

  return a.exec();
}
