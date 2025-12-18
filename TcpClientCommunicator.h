#ifndef TCPCLIENTCOMMUNICATOR_H
#define TCPCLIENTCOMMUNICATOR_H

#include "ICommunicator.h"
#include <QTcpSocket>

class TcpClientCommunicator : public ICommunicator {
    Q_OBJECT
public:
    explicit TcpClientCommunicator(const QString& serverIp, QObject *parent = nullptr);
    ~TcpClientCommunicator() override;

    bool start() override;
    void stop() override;
    void sendMessage(const QString& msg) override;
    bool isRunning() const override;
    QString getConnectionInfo() const override;

private:
    QTcpSocket *socket;
    QString serverIp;
};

#endif // TCPCLIENTCOMMUNICATOR_H
