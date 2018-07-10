#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "shellfunctions.h"
#include "configdata.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include <QTimer>

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
    void on_openFileButton_clicked();

    void on_castFileButton_clicked();

    void on_castDesktopButton_clicked();

    void on_avStopButton_clicked();

    void on_actionConfig_triggered();

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_actionOpenFile_triggered();

    void on_castLinkButton_clicked();

    void on_castDeviceButton_clicked();

    void on_castCDButton_clicked();

    void EnableCastingButtons(bool state);

    int CheckFilePath(string type);

    void StatusBarCastingMsg();

    void StatusBarFileError();

    void StatusBarLinkError();

    void SetMediaPreview(string mediaType, QString path);

    void PreviewMediaChanged();

    void PreviewStatusChanged();

    QString ConvertProgressTime(double mediaPosition);

    void ChangePreviewProgress();

    void ChangePreviewImage(const char *imgResource);

    void on_avToggleButton_clicked();

    void on_castFolderButton_clicked();

private:
    Ui::MainWindow *ui;

    QMediaPlayer *mediaPlayer = new QMediaPlayer;
};

#endif // MAINWINDOW_H
