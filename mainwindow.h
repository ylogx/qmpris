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
    void listAvailablePlayers();
    void setPositionSlider(QString);
    void setMetadata(QString);
protected:
    Ui::MainWindow *ui;
    QString currentPlayer();
    void basicConnections();

public slots:
    void reconnect();
    void recheckMediaPlayers();
    void showKMix();

    void pause();
    void next();
    void prev();
    void showPlayer();
    void volumeChanged(int);
    void positionChanged(int);

    void muteAmarok();

    void muteAudacious(bool);

    void muteClementine();
};

#endif // MAINWINDOW_H
