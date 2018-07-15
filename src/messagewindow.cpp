#include "messagewindow.h"
#include "ui_messagewindow.h"

MessageWindow::MessageWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageWindow)
{
    ui->setupUi(this);
    //setModal(true);
    setWindowFlags(Qt::Popup);
}

MessageWindow::~MessageWindow()
{
    delete ui;
}

void MessageWindow::SetMessageText(QString messageType, QString messageText)
{
    ui->messageText->setText(messageText);
}
