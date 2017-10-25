/*
 * (C) Copyright 2017
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "sysfs/RoValue.h"

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QProcess>
#include <QThread>
#include <iostream>

struct Configuration
{
  QString device;
  QString command;
};

struct Brightness
{
  QString expected;
  QString actual;
};


static Configuration parseCmdline(const QStringList &arguments);
static Brightness readBrightness(const QString &device);
static bool verifyAndAction(const Brightness &brightness, const QString &errorCommand);
static bool execute(const QString &command);


int main(int argc, char *argv[])
{
  QCoreApplication::setOrganizationName("brightness-zoo");
  QCoreApplication::setApplicationName("checkbrightnessd");
  QCoreApplication app(argc, argv);
  const Configuration configuration = parseCmdline(app.arguments());

  const auto brightness = readBrightness(configuration.device);

  if (brightness.actual == brightness.expected) {
    return 0;
  }

  QThread::msleep(100);

  const auto brightnessVerification = readBrightness(configuration.device);
  const auto ok = verifyAndAction(brightnessVerification, configuration.command);

  return ok ? 0 : 1;
}


static bool verifyAndAction(const Brightness &brightness, const QString &errorCommand)
{
  if (brightness.expected != brightness.actual) {
    std::cout << "Read brightness " << brightness.actual.toStdString() << ", expected " << brightness.expected.toStdString() << std::endl;

    return execute(errorCommand);
  }

  return true;
}

static bool execute(const QString &command)
{
  const auto result = QProcess::execute(command);

  if (result != 0) {
    std::cerr << "command execution failed: " << command.toStdString() << std::endl;
    return false;
  }

  return true;
}


static Brightness readBrightness(const QString &device)
{
  const sysfs::RoValue expectedBrightnessFile{device + "/brightness"};
  const sysfs::RoValue actualBrightnessFile{device + "/actual_brightness"};
  const auto expected = expectedBrightnessFile.read();
  const auto actual = actualBrightnessFile.read();

  return {expected, actual};
}

static Configuration parseCmdline(const QStringList &arguments)
{
  QCommandLineParser parser;
  parser.addHelpOption();

  QCommandLineOption device{"device", "the root sysfs folder of the brightness device", "path"};
  parser.addOption(device);

  QCommandLineOption command{"command", "the command to execute when the actual and expected brightness do not match", "command"};
  parser.addOption(command);

  parser.process(arguments);

  const auto allSet = parser.isSet(device) && parser.isSet(command);
  if (!allSet) {
    parser.showHelp(-1);
  }

  Configuration result;
  result.device = parser.value(device);
  result.command = parser.value(command);

  return result;
}

