#include "messagewindow.h"
#include "ui_messagewindow.h"

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

void MessageWindow::DisplayMessage(QString messageType, QString messageText)
{
    ui->messageText->setText(messageText);
    this->show();
}
