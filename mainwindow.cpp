#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "TcpClientCommunicator.h"
#include "SharedMemoryClientCommunicator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , communicator(nullptr)
{
    ui->setupUi(this);

    ui->sendButton->setEnabled(false);

    connect(ui->connectButton, &QPushButton::clicked, this, [=]() {
        bool useTCP = ui->tcpRadioButton->isChecked();

        if(ui->usernameInput->text().isEmpty()){
            ui->chatBox->append("-- Please enter your name before connecting to the server");
            return;
        }

        if (useTCP) {
            QString ip = ui->serverIP->text().trimmed();
            if (ip.isEmpty()) {
                ui->chatBox->append("-- Please enter a server IP");
                return;
            }
            ui->chatBox->append("-- Connecting to " + ip + ":8080 ...");
            communicator = new TcpClientCommunicator(ip, this);
        } else {
            ui->chatBox->append("-- Connecting to shared memory...");
            communicator = new SharedMemoryClientCommunicator(this);
        }

        connect(communicator, &ICommunicator::started, this, [=]() {
            ui->chatBox->append("-- Connected");
            ui->connectButton->setEnabled(false);

            ui->tcpRadioButton->setEnabled(false);
            ui->sharedMemoryRadioButton->setEnabled(false);
            ui->serverIP->setEnabled(false);
            ui->usernameInput->setEnabled(false);

            checkEnableSendButton();
        });

        connect(communicator, &ICommunicator::errorOccurred, this, [=](QString error) {
            ui->chatBox->append("-- Error: " + error);
        });

        connect(communicator, &ICommunicator::messageReceived, this, [=](QString msg) {
            ui->chatBox->append(msg);
        });

        connect(communicator, &ICommunicator::clientDisconnected, this, [=]() {
            ui->chatBox->append("-- Disconnected from server");
            ui->connectButton->setEnabled(true);

            ui->tcpRadioButton->setEnabled(true);
            ui->sharedMemoryRadioButton->setEnabled(true);
            ui->serverIP->setEnabled(true);
            ui->usernameInput->setEnabled(true);

            checkEnableSendButton();
        });

        communicator->start();
    });

    connect(ui->usernameInput, &QLineEdit::textChanged, this, &MainWindow::checkEnableSendButton);
    connect(ui->messageInput, &QLineEdit::textChanged, this, &MainWindow::checkEnableSendButton);

    connect(ui->sendButton, &QPushButton::clicked, this, [=](){
        QString username = ui->usernameInput->text();
        QString message = ui->messageInput->text();
        QString messageToSend = username + ": " + message;

        if (communicator) {
            communicator->sendMessage(messageToSend);
        }
        ui->messageInput->clear();
    });
}

MainWindow::~MainWindow()
{
    if (communicator) {
        communicator->stop();
    }
    delete ui;
}

void MainWindow::checkEnableSendButton() {
    QString username = ui->usernameInput->text();
    QString message = ui->messageInput->text();
    bool connected = (communicator && communicator->isRunning());
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
    }
}
