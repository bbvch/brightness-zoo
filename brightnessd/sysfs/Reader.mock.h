// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef SYSFS_READER_MOCK_H
#define SYSFS_READER_MOCK_H

#include "Reader.h"

#include <gmock/gmock.h>

namespace sysfs
{

class Reader_Mock :
    public Reader
{
  public:
    MOCK_CONST_METHOD0(read, QString());
};

}

#endif

