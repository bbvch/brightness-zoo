/*
 * Framebuffer Activity Monitor Implementation
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include "FramebufferIdle.h"
#include "InputDevice.h"

#include <QDir>
#include <QDebug>
#include <QFileInfo>

FramebufferIdle::FramebufferIdle(QObject* parent)
    : QObject(parent)
    , m_started(false)
{
    m_idleTimer.start();
    discoverInputDevices();
}

FramebufferIdle::~FramebufferIdle()
{
    stop();
    
    // Clean up devices
    m_devices.clear();
}

void FramebufferIdle::discoverInputDevices()
{
    QDir inputDir("/dev/input");
    
    if (!inputDir.exists()) {
        throw std::runtime_error("Cannot access /dev/input directory");
    }

    // Find all event devices
    const QStringList filters = {"event*"};
    const QFileInfoList entries = inputDir.entryInfoList(
        filters, 
        QDir::System | QDir::Readable
    );

    for (const QFileInfo& entry : entries) {
        InputDevice* device = new InputDevice(entry.absoluteFilePath(), this);

        if (device->isValid()) {
            // Connect device signals to our slot
            connect(device, &InputDevice::inputEventReceived,
                    this, &FramebufferIdle::onInputActivity);

            m_devices.append(device);
        } else {
            delete device;
        }
    }

    if (m_devices.isEmpty()) {
        throw std::runtime_error(
            "No input devices found. "
            "Run with sudo or add user to 'input' group.\n"
            "Alternatively, create udev rule: "
            "/etc/udev/rules.d/99-input.rules\n"
            "SUBSYSTEM==\"input\", MODE=\"0660\", GROUP=\"input\""
        );
    }

    qDebug() << "Found" << m_devices.size() << "input device(s)";
}

void FramebufferIdle::start()
{
    if (m_started) {
        return;
    }

    for (InputDevice* device : m_devices) {
        device->startMonitoring();
    }

    m_started = true;
    qDebug() << "Input monitoring started";
}

void FramebufferIdle::stop()
{
    if (!m_started) {
        return;
    }

    for (InputDevice* device : m_devices) {
        device->stopMonitoring();
    }

    m_started = false;
    qDebug() << "Input monitoring stopped";
}

void FramebufferIdle::onInputActivity()
{
    m_idleTimer.restart();
    emit activityDetected();
}

std::chrono::milliseconds FramebufferIdle::operator()() const
{
    return std::chrono::milliseconds(m_idleTimer.elapsed());
}

qint64 FramebufferIdle::getIdleTimeMs() const
{
    return m_idleTimer.elapsed();
}