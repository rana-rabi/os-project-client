#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    socket->connectToHost("127.0.0.1", 8080);
    ui->chatBox->append("-- Connecting to server...");

    connect(socket, &QTcpSocket::connected, this, [=](){
        ui->chatBox->append("-- Connected to server");
    });

    connect(socket, &QTcpSocket::errorOccurred, this, [=](){
        ui->chatBox->append("-- Connection error: " + socket->errorString());
    });

    ui->sendButton->setEnabled(false);

    auto checkEnable = [=](){
        QString username = ui->usernameInput->text();
        QString message = ui->messageInput->text();
        bool connected = (socket->state() == QAbstractSocket::ConnectedState);

        bool enable = !username.isEmpty() && !message.isEmpty() && connected;
        ui->sendButton->setEnabled(enable);

        if (!enable) {
            if (!connected)
                ui->sendButton->setToolTip("Cannot send: not connected to server");
            else if (username.isEmpty())
                ui->sendButton->setToolTip("Enter a username first");
            else if (message.isEmpty())
                ui->sendButton->setToolTip("Enter a message first");
        } else {
            ui->sendButton->setToolTip("");
        }

        if(!username.isEmpty()){
            this->setWindowTitle("Client - " + username);
        };
    };

    connect(ui->usernameInput, &QLineEdit::textChanged, this, checkEnable);
    connect(ui->messageInput, &QLineEdit::textChanged, this, checkEnable);
    connect(socket, &QTcpSocket::connected, this, checkEnable);
    connect(socket, &QTcpSocket::disconnected, this, checkEnable);

    connect(ui->sendButton, &QPushButton::clicked, this, [=](){
        QString username = ui->usernameInput->text();
        QString message = ui->messageInput->text();
        QString messageToSend = username + ": " + message;

        socket->write(messageToSend.toUtf8());
        ui->messageInput->clear();
    });

    connect(socket, &QTcpSocket::readyRead, this, [=](){
        QString message = socket->readAll();
        ui->chatBox->append(message);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
