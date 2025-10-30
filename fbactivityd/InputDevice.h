/*
 * Input Device Wrapper
 * RAII wrapper for Linux input device monitoring
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <QObject>
#include <QSocketNotifier>
#include <QString>
#include <memory>

/**
 * @brief RAII wrapper for a single input device
 * 
 * Encapsulates file descriptor management and event monitoring.
 * Follows Single Responsibility Principle.
 */
class InputDevice : public QObject
{
    Q_OBJECT

public:
    explicit InputDevice(const QString& devicePath, QObject* parent = nullptr);
    ~InputDevice() override;

    // Delete copy/move
    InputDevice(const InputDevice&) = delete;
    InputDevice& operator=(const InputDevice&) = delete;
    InputDevice(InputDevice&&) = delete;
    InputDevice& operator=(InputDevice&&) = delete;

    bool isValid() const;
    QString devicePath() const;
    QString deviceName() const;

    void startMonitoring();
    void stopMonitoring();

signals:
    void inputEventReceived();

private slots:
    void onReadyRead();

private:
    void open();
    void close();
    static bool isRelevantEvent(const struct input_event& ev);

    QString m_devicePath;
    QString m_deviceName;
    int m_fd;
    std::unique_ptr<QSocketNotifier> m_notifier;
};

#endif // INPUTDEVICE_H