#include "TcpClientCommunicator.h"

TcpClientCommunicator::TcpClientCommunicator(const QString& serverIp, QObject *parent)
    : ICommunicator(parent), serverIp(serverIp)
{
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, [=]() {
        emit started();
        emit clientConnected();
    });

    connect(socket, &QTcpSocket::errorOccurred, this, [=]() {
        emit errorOccurred(socket->errorString());
    });

    connect(socket, &QTcpSocket::readyRead, this, [=]() {
        QString message = socket->readAll();
        emit messageReceived(message);
    });

    connect(socket, &QTcpSocket::disconnected, this, [=]() {
        emit clientDisconnected();
    });
}

TcpClientCommunicator::~TcpClientCommunicator() {
    stop();
}

bool TcpClientCommunicator::start() {
    socket->abort();
    socket->connectToHost(serverIp, 8080);
    return true;
}

void TcpClientCommunicator::stop() {
    socket->disconnectFromHost();
}

void TcpClientCommunicator::sendMessage(const QString& msg) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(msg.toUtf8());
    }
}

bool TcpClientCommunicator::isRunning() const {
    return socket->state() == QAbstractSocket::ConnectedState;
}

QString TcpClientCommunicator::getConnectionInfo() const {
    return serverIp + ":8080";
}
