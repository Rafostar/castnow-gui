#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include "configdata.h"
#include <QDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <string>

using namespace std;

namespace Ui {
class MessageWindow;
}

class MessageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MessageWindow(QWidget *parent = 0);
    ~MessageWindow();

    void EditMessage(QString messageType, QString messageText);

private:
    Ui::MessageWindow *ui;
};

#endif // MESSAGEWINDOW_H
