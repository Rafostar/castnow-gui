#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QDialog>

namespace Ui {
class MessageWindow;
}

class MessageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MessageWindow(QWidget *parent = 0);
    ~MessageWindow();

private:
    Ui::MessageWindow *ui;
};

#endif // MESSAGEWINDOW_H
