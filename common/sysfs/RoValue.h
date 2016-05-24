// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef SYSFS_ROVALUE_H
#define SYSFS_ROVALUE_H

#include "Reader.h"

#include <QString>

namespace sysfs
{

class RoValue :
    public Reader
{
  public:
    RoValue(QString filename);

    QString read() const override;

  private:
    const QString filename;
};

}

#endif
