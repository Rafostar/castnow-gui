#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "shellfunctions.h"
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
    void on_streamButton_clicked();

    void on_openFileButton_clicked();

    void on_castDesktopButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
