#include "print.h"



QString toString(qint32 value)
{
  return QString::number(value);
}

QString toString(bool value)
{
  return (value ? "on" : "off");
}

QString valueText(const NamedValue &value)
{
  return value.name + " (" + value.value + ")";
}

QString setText(const NamedValue &destination, const NamedValue &source1, const NamedValue &source2, const NamedValue &source3)
{
  return "set " + valueText(destination) + " based on " + valueText(source1) + ", " + valueText(source2) + " and " + valueText(source3);
}
