#include "SharedMemoryClientCommunicator.h"
#include <QThread>

const QString SharedMemoryClientCommunicator::SHARED_MEMORY_KEY = "ChatAppSharedMemory";
const QString SharedMemoryClientCommunicator::SEMAPHORE_KEY = "ChatAppSemaphore";

SharedMemoryClientCommunicator::SharedMemoryClientCommunicator(QObject *parent)
    : ICommunicator(parent), running(false)
{
    semaphore = new QSystemSemaphore(SEMAPHORE_KEY, 1, QSystemSemaphore::Open);
    sharedMemory = new QSharedMemory(SHARED_MEMORY_KEY, this);

    pollTimer = new QTimer(this);
    connect(pollTimer, &QTimer::timeout, this, &SharedMemoryClientCommunicator::checkForMessages);
}

SharedMemoryClientCommunicator::~SharedMemoryClientCommunicator() {
    stop();
    delete semaphore;
}

bool SharedMemoryClientCommunicator::start() {
    if (!sharedMemory->attach()) {
        emit errorOccurred("Failed to attach to shared memory. Is the server running?");
        return false;
    }

    running = true;
    pollTimer->start(100);

    emit started();
    emit clientConnected();
    return true;
}

void SharedMemoryClientCommunicator::stop() {
    running = false;
    pollTimer->stop();

    if (sharedMemory->isAttached()) {
        sharedMemory->detach();
    }
}

void SharedMemoryClientCommunicator::sendMessage(const QString& msg) {
    if (!running || !sharedMemory->isAttached())
        return;

    semaphore->acquire();

    char *data = static_cast<char*>(sharedMemory->data());

    data[0] = 1;

    QByteArray msgBytes = msg.toUtf8();
    int len = qMin(msgBytes.size(), BUFFER_SIZE - 2);
    memcpy(data + 1, msgBytes.constData(), len);
    data[len + 1] = '\0';

    semaphore->release();
}

bool SharedMemoryClientCommunicator::isRunning() const {
    return running;
}

QString SharedMemoryClientCommunicator::getConnectionInfo() const {
    return "Shared Memory Key: " + SHARED_MEMORY_KEY;
}

void SharedMemoryClientCommunicator::checkForMessages() {
    if (!running || !sharedMemory->isAttached())
        return;

    semaphore->acquire();

    char *data = static_cast<char*>(sharedMemory->data());

    if (data[0] != 2) {
        semaphore->release();
        return;
    }

    int msgId;
    memcpy(&msgId, data + 1, sizeof(int));

    if (msgId == lastMessageId) {
        semaphore->release();
        return;
    }

    lastMessageId = msgId;

    QString message = QString::fromUtf8(
        data + 1 + sizeof(int)
        );

    semaphore->release();
    emit messageReceived(message);
}
