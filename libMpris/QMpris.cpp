#include <QtGui>
#include "QMpris.h"

Widget::Widget() : QWidget(){

}

void helloWorldByLib(){
    qDebug()<<"******** Hello World *********";
}

QStringList discoveredMprisPlayer(){
    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusInterface dbus_iface("org.freedesktop.DBus", "/org/freedesktop/DBus",
                              "org.freedesktop.DBus", bus);
    QVariant list=dbus_iface.call("ListNames").arguments().at(0);
    QRegExp rx("org.mpris.MediaPlayer2.*");
    return(list.toStringList().filter(rx));
}

void playPause(char* destination){
    QDBusConnection bus= QDBusConnection::sessionBus();
    QDBusMessage message= QDBusMessage::createMethodCall(destination,
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player","PlayPause");
    QDBusConnection::sessionBus().send(message);
}

void simpleOperation(char* destination, char* op){
    qDebug()<<"Call to "<<destination<<" for operation "<<op;
    QDBusConnection bus= QDBusConnection::sessionBus();
    QDBusMessage message= QDBusMessage::createMethodCall(destination,
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player",op);
    QDBusConnection::sessionBus().send(message);
}
