#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private slots:
    void on_streamButton_clicked();

public:
    Ui::MainWindow *ui;
    int checkFilePath();
    void statusBarCastingMsg();
    void statusBarError();
};

#endif // MAINWINDOW_H
