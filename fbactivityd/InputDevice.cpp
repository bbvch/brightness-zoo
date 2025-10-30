/*
 * Input Device Wrapper Implementation
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include "InputDevice.h"

#include <QDebug>

#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cerrno>
#include <cstring>

InputDevice::InputDevice(const QString& devicePath, QObject* parent)
    : QObject(parent)
    , m_devicePath(devicePath)
    , m_fd(-1)
    , m_notifier(nullptr)
{
    open();
}

InputDevice::~InputDevice()
{
    close();
}

bool InputDevice::isValid() const
{
    return m_fd >= 0;
}

QString InputDevice::devicePath() const
{
    return m_devicePath;
}

QString InputDevice::deviceName() const
{
    return m_deviceName;
}

void InputDevice::startMonitoring()
{
    if (!isValid() || m_notifier) {
        return;
    }

    // Qt's QSocketNotifier integrates with event loop - no threads needed!
    m_notifier = std::make_unique<QSocketNotifier>(
        m_fd, 
        QSocketNotifier::Read, 
        this
    );

    connect(m_notifier.get(), &QSocketNotifier::activated,
            this, &InputDevice::onReadyRead);

    m_notifier->setEnabled(true);
}

void InputDevice::stopMonitoring()
{
    if (m_notifier) {
        m_notifier->setEnabled(false);
        m_notifier.reset();
    }
}

void InputDevice::onReadyRead()
{
    struct input_event ev;
    
    while (::read(m_fd, &ev, sizeof(ev)) == sizeof(ev)) {
        // Filter relevant events
        if (isRelevantEvent(ev)) {
            emit inputEventReceived();
        }
    }
}

void InputDevice::open()
{
    m_fd = ::open(m_devicePath.toLocal8Bit().constData(), 
                  O_RDONLY | O_NONBLOCK | O_CLOEXEC);

    if (m_fd < 0) {
        qWarning() << "Cannot open" << m_devicePath 
                  << ":" << strerror(errno);
        return;
    }

    // Get device name
    char name[256] = "Unknown";
    if (::ioctl(m_fd, EVIOCGNAME(sizeof(name)), name) >= 0) {
        m_deviceName = QString::fromLocal8Bit(name);
        qDebug() << "Opened input device:" << m_devicePath 
                << "(" << m_deviceName << ")";
    } else {
        qWarning() << "Cannot get device name for" << m_devicePath;
        close();
    }
}

void InputDevice::close()
{
    stopMonitoring();

    if (m_fd >= 0) {
        ::close(m_fd);
        m_fd = -1;
    }
}

bool InputDevice::isRelevantEvent(const input_event& ev)
{
    // Only care about actual user input, not sync/metadata events
    return ev.type == EV_KEY ||  // Keyboard/button
           ev.type == EV_REL ||  // Relative movement (mouse)
           ev.type == EV_ABS;    // Absolute movement (touchscreen)
}