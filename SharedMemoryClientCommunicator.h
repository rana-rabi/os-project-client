#ifndef SHAREDMEMORYCLIENTCOMMUNICATOR_H
#define SHAREDMEMORYCLIENTCOMMUNICATOR_H

#include "ICommunicator.h"
#include <QSharedMemory>
#include <QSystemSemaphore>
#include <QTimer>

class SharedMemoryClientCommunicator : public ICommunicator {
    Q_OBJECT
public:
    explicit SharedMemoryClientCommunicator(QObject *parent = nullptr);
    ~SharedMemoryClientCommunicator() override;

    bool start() override;
    void stop() override;
    void sendMessage(const QString& msg) override;
    bool isRunning() const override;
    int lastMessageId = -1;
    QString getConnectionInfo() const override;

private:
    void checkForMessages();

    QSharedMemory *sharedMemory;
    QSystemSemaphore *semaphore;
    QTimer *pollTimer;
    bool running;

    static const QString SHARED_MEMORY_KEY;
    static const QString SEMAPHORE_KEY;
    static const int BUFFER_SIZE = 4096;
};

#endif // SHAREDMEMORYCLIENTCOMMUNICATOR_H
