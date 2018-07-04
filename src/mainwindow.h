#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "shellfunctions.h"
#include "configdata.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int checkFilePath();
    void statusBarCastingMsg();
    void statusBarError();

private slots:
    void on_openFileButton_clicked();

    void on_castFileButton_clicked();

    void on_castDesktopButton_clicked();

    void on_stopCastingButton_clicked();

    void enableCastingButtons(bool state);

    void on_actionConfig_triggered();

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_actionOpenFile_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
