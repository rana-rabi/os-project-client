#ifndef ICOMMUNICATOR_H
#define ICOMMUNICATOR_H

#include <QObject>
#include <QString>

class ICommunicator : public QObject {
    Q_OBJECT
public:
    explicit ICommunicator(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~ICommunicator() = default;

    virtual bool start() = 0;

    virtual void stop() = 0;

    virtual void sendMessage(const QString& msg) = 0;

    virtual bool isRunning() const = 0;

    virtual QString getConnectionInfo() const = 0;

signals:
    void messageReceived(const QString& msg);
    void clientConnected();
    void clientDisconnected();
    void errorOccurred(const QString& error);
    void started();
};

#endif // ICOMMUNICATOR_H
