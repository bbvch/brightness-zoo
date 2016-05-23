// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef SYSFS_WOVALUE_H
#define SYSFS_WOVALUE_H

#include "Writer.h"

#include <QString>

namespace sysfs
{

class WoValue :
    public Writer
{
  public:
    WoValue(QString filename);

    void write(QString value) override;

  private:
    const QString filename;
};

}

#endif
