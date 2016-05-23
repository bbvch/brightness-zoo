// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "RoValue.h"

#include <fstream>

namespace sysfs
{

RoValue::RoValue(QString aFilename) :
  filename{aFilename}
{
}

QString RoValue::read() const
{
  QString content{""};

  std::ifstream file{filename.toStdString(), std::ifstream::in};

  while (file.good()) {
    char buffer[100];
    int n = file.readsome(buffer, sizeof(buffer)-1);
    if (n == 0) {
      break;
    }
    buffer[n] = '\0';
    content += buffer;
  }

  return content.trimmed();
}

}
