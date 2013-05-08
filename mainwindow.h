#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>

//#include "amarok.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, QDBusMessage
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void checkAvailablePlayer();
    void setPositionSlider(QString);
    void setMetadata(QString);
protected:
    Ui::MainWindow *ui;
    void connectAmarok();
    void connectClementine();
    void connectAudacious();

public slots:
    void reconnect();
    void showKMix();

    void volumeChanged(int);
    void positionChanged(int);
    void pauseAmarok();
    void nextAmarok();
    void prevAmarok();
    void muteAmarok();
    void showAmarok();


    void pauseAudacious();
    void nextAudacious();
    void prevAudacious();
    void muteAudacious(bool);
    void showAudacious();

    void pauseClementine();
    void nextClementine();
    void prevClementine();
    void muteClementine();
    void showClementine();
};

#endif // MAINWINDOW_H
