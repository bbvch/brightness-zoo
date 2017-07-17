#pragma once

#include <QString>
#include <QPair>
#include <array>

class NamedValue
{
public:
  QString name;
  QString value;
};

QString toString(qint32 value);
QString toString(bool value);

QString setText(const NamedValue &destination, const NamedValue &source1, const NamedValue &source2, const NamedValue &source3);

