/*
 * Framebuffer Activity Monitor
 * Qt-based implementation with proper RAII and thread safety
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef FRAMEBUFFERIDLE_H
#define FRAMEBUFFERIDLE_H

#include <QObject>
#include <QElapsedTimer>
#include <QList>
#include <memory>

class InputDevice;

/**
 * @brief Monitors user input activity from Linux input devices
 * 
 * Uses Qt's event loop for efficient, non-blocking I/O monitoring.
 * Thread-safe and follows RAII principles.
 */
class FramebufferIdle : public QObject
{
    Q_OBJECT

public:
    explicit FramebufferIdle(QObject* parent = nullptr);
    ~FramebufferIdle() override;

    // Delete copy/move to ensure single ownership of resources
    FramebufferIdle(const FramebufferIdle&) = delete;
    FramebufferIdle& operator=(const FramebufferIdle&) = delete;
    FramebufferIdle(FramebufferIdle&&) = delete;
    FramebufferIdle& operator=(FramebufferIdle&&) = delete;

    /**
     * @brief Start monitoring input devices
     * @throws std::runtime_error if no devices can be opened
     */
    void start();

    /**
     * @brief Stop monitoring (called automatically in destructor)
     */
    void stop();

    /**
     * @brief Get idle time since last input activity
     * @return Milliseconds since last activity
     */
    std::chrono::milliseconds operator()() const;
    
    qint64 getIdleTimeMs() const;

signals:
    /**
     * @brief Emitted whenever user input is detected
     */
    void activityDetected();

private slots:
    void onInputActivity();

private:
    void discoverInputDevices();

    QList<InputDevice*> m_devices;
    QElapsedTimer m_idleTimer;
    bool m_started = false;
};

#endif // FRAMEBUFFERIDLE_H