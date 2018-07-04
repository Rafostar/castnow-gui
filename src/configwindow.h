#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>
#include <QAbstractButton>

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

    void UpdateConfigWindowValues();

    void on_buttonBoxConfig_clicked(QAbstractButton *button);

    void UpdateUsedValues();

    void on_doubleSpinBoxFileOffset_valueChanged(const QString &arg1);

private:

    Ui::ConfigWindow *ui;
};

#endif // CONFIGWINDOW_H
