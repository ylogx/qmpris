#include <QtGui>
#include <QStringList>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>

#include "mainwindow.h"
//#include "libMpris/QMpris.h"
#include "QMpris.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.setWindowTitle(QObject::tr("Demo Sound Menu"));
    w.show();
    //Testing
//    QMpris::MediaPlayer2Player playerObj;
//    playerObj.Next();
    return app.exec();
}
//QMPRIS::Player *QMPRIS::discoveredPlayers()
