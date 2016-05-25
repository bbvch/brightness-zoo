// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "WoValue.h"

#include <fstream>
#include <QFile>

namespace sysfs
{

WoValue::WoValue(QString aFilename) :
  filename{aFilename}
{
  if (!QFile{filename}.exists()) {
    throw std::runtime_error("file \"" + filename.toStdString() + "\" not found");
  }
}

void WoValue::write(QString value)
{
  const std::string content{value.toStdString()};

  std::ofstream file{filename.toStdString(), std::ifstream::out};

  file.write(content.c_str(), content.size());
}

}
