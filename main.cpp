#include <QtGui>
#include <QStringList>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>

#include "mainwindow.h"
#include "libMpris/QMpris.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.setWindowTitle(QObject::tr("Demo Sound Menu"));
    w.show();

    QLibrary library("libQMpris.so");
    if (!library.load())
        qDebug() << library.errorString();
    if (library.load())
        qDebug() << "library loaded";

    typedef QStringList(*DiscoveredPlayer)(void);
    DiscoveredPlayer disPlr = (DiscoveredPlayer)library.resolve("discoveredMprisPlayer");
    QStringList list;
    if (disPlr) {
        list = disPlr();
        if (!list.isEmpty())
            qDebug()<<"List is: "<<list;
    } else {
        qDebug() << "Could not get list from the loaded library";
    }


    typedef void(*SimpleOperation)(char*,char*);
    SimpleOperation operation=(SimpleOperation)library.resolve("simpleOperation");
    if(operation){
        //operation(list.at(1).toLocal8Bit().data(),"PlayPause");
    }

//    typedef QStringList (*MyPrototype)();
//    MyPrototype myFunction =
//            (MyPrototype) QLibrary::resolve("libQMpris.so","discoveredMprisPlayer");
//    if (myFunction)
//        qDebug()<<"List is: "<<myFunction();

//        typedef QStringList(*DiscoveredPlayer)(void);
//        DiscoveredPlayer disPlr = (DiscoveredPlayer)library.resolve("helloWorldByLib");
//        if (disPlr) {
//            disPlr();
//        } else {
//            qDebug() << "Could not get list from the loaded library";
//        }

    return app.exec();
}
//QMPRIS::Player *QMPRIS::discoveredPlayers()
/*
#include <QtGui/QApplication>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QObject::tr("Demo Sound Menu"));
    w.show();
//    QDBusConnection connection = QDBusConnection::sessionBus();
//    bool ret=connection.registerService("chaudhary");
//    ret=connection.registerObject("/");
    return a.exec();
}
*/
