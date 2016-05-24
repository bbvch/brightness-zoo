// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef SYSFS_READER_H
#define SYSFS_READER_H

#include <QString>

namespace sysfs
{

class Reader
{
  public:
    virtual ~Reader() = default;

    virtual QString read() const = 0;
};

}

#endif
