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

    void UpdateConfigWindowValues();

private slots:
    void on_doubleSpinBoxFileOffset_valueChanged(const QString &arg1);

    void on_doubleSpinBoxDesktopOffset_valueChanged(const QString &arg1);

    void on_buttonBoxConfig_clicked(QAbstractButton *button);

    void UpdateUsedValues();

    void RestoreDefaultValues();

private:
    Ui::ConfigWindow *ui;
};

#endif // CONFIGWINDOW_H
