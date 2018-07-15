#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QDialog>
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

    void DisplayMessage(QString messageType, QString messageText);

private:
    Ui::MessageWindow *ui;
};

#endif // MESSAGEWINDOW_H
