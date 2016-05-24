// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef SYSFS_WRITER_MOCK_H
#define SYSFS_WRITER_MOCK_H

#include "Writer.h"

#include <gmock/gmock.h>

namespace sysfs
{

class Writer_Mock :
    public Writer
{
  public:
    MOCK_METHOD1(write, void(QString));
};

}

#endif

