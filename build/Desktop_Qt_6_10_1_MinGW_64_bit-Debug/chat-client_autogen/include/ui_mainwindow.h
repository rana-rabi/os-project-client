/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *chatBox;
    QLineEdit *messageInput;
    QPushButton *sendButton;
    QLineEdit *usernameInput;
    QLineEdit *serverIP;
    QPushButton *connectButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(450, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        chatBox = new QTextEdit(centralwidget);
        chatBox->setObjectName("chatBox");
        chatBox->setGeometry(QRect(10, 80, 430, 341));
        chatBox->setReadOnly(true);
        messageInput = new QLineEdit(centralwidget);
        messageInput->setObjectName("messageInput");
        messageInput->setGeometry(QRect(10, 430, 430, 48));
        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(170, 490, 271, 40));
        usernameInput = new QLineEdit(centralwidget);
        usernameInput->setObjectName("usernameInput");
        usernameInput->setGeometry(QRect(10, 10, 430, 28));
        serverIP = new QLineEdit(centralwidget);
        serverIP->setObjectName("serverIP");
        serverIP->setGeometry(QRect(10, 40, 431, 28));
        connectButton = new QPushButton(centralwidget);
        connectButton->setObjectName("connectButton");
        connectButton->setGeometry(QRect(10, 490, 151, 40));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 450, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Client Chat", nullptr));
        chatBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Messages will appear here...", nullptr));
        messageInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter your message...", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        usernameInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter your name...", nullptr));
        serverIP->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        serverIP->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter Server IP", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect To Server", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
