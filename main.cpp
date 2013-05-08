#include <QtGui>
#include "libMpris/QMpris.h"
#include <QStringList>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLibrary library("libQMpris.so");
    if (!library.load())
        qDebug() << library.errorString();
    if (library.load())
        qDebug() << "library loaded";

//    typedef QStringList(*DiscoveredPlayer)(void);
//    DiscoveredPlayer disPlr = (DiscoveredPlayer)library.resolve("helloWorldByLib");
//    if (disPlr) {
//        disPlr();
//    } else {
//        qDebug() << "Could not get list from the loaded library";
//    }
    typedef QStringList(*DiscoveredPlayer)(void);
    DiscoveredPlayer disPlr = (DiscoveredPlayer)library.resolve("discoveredMprisPlayer");
    if (disPlr) {
        QStringList list = disPlr();
        if (!list.isEmpty())
            qDebug()<<"List is: "<<list;
    } else {
        qDebug() << "Could not get list from the loaded library";
    }

//    typedef QStringList (*MyPrototype)();
//    MyPrototype myFunction =
//            (MyPrototype) QLibrary::resolve("libQMpris.so","discoveredMprisPlayer");
//    if (myFunction)
//        qDebug()<<"List is: "<<myFunction();

//    QStringList (*DiscoveredPlayer)(void);
//    DiscoveredPlayer = library.resolve("discoveredMprisPlayer");
//    QStringList list = DiscoveredPlayer();
//    if (!list.isEmpty())
//        qDebug()<<"List is: "<<list;

    return app.exec();
    // QApplication a(argc, argv);
    // Widget w;
    // w.resize(100,100);
    // w.show();
    // return a.exec();
}
//QMPRIS::Player *QMPRIS::discoveredPlayers()
