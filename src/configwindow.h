#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigWindow(QWidget *parent = 0);
    ~ConfigWindow();

private slots:

    void on_doubleSpinBoxOffset_valueChanged(const QString &arg1);

    void UpdateConfigValues();

private:

    Ui::ConfigWindow *ui;
};

#endif // CONFIGWINDOW_H
