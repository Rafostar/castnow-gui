#include "messagewindow.h"
#include "ui_messagewindow.h"

#include "mainwindow.h"

MessageWindow::MessageWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Popup);
}

MessageWindow::~MessageWindow()
{
    delete ui;
}

void MessageWindow::EditMessage(QString messageType, QString messageText)
{
    ui->messageType->setText(messageType);
    ui->messageText->setText(messageText);
    this->show();
}
