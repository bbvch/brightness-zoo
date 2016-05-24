// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef SYSFS_WRITER_H
#define SYSFS_WRITER_H

#include <QString>

namespace sysfs
{

class Writer
{
  public:
    virtual ~Writer() = default;

    virtual void write(QString value) = 0;

};

}

#endif
