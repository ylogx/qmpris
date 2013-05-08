#include <QtGui>
#include "QMpris.h"

Widget::Widget() : QWidget(){

}

QStringList discoveredMprisPlayer(){
    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusInterface dbus_iface("org.freedesktop.DBus", "/org/freedesktop/DBus",
                              "org.freedesktop.DBus", bus);
    //    QVariantList list;
    //    list.append( dbus_iface.call("ListNames").arguments().at(0));
    QVariant list=dbus_iface.call("ListNames").arguments().at(0);
    QStringList mprisList;
    QRegExp rx("org.mpris.MediaPlayer2.*");
    mprisList=list.toStringList().filter(rx);
    qDebug() << mprisList << mprisList.count()<<mprisList.value(0);
//    for(int i=0;i<mprisList.size();i++){
//        QDBusInterface dbusIface(mprisList.value(i),"/org/mpris/mediaPlayer2",
//                                 "org.mpris.MediaPlayer2",bus);
//        qDebug()<<dbusIface.service();
//        qDebug()<<dbusIface.property("Identity");
    return (mprisList);
}
void helloWorldByLib(){
    qDebug()<<"******** Hello World *********";
}
