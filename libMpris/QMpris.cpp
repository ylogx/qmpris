#include <QtGui>
#include "QMpris.h"

namespace QMpris{

void testDiscovered(){
    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusInterface dbus_iface("org.freedesktop.DBus", "/org/freedesktop/DBus",
                              "org.freedesktop.DBus", bus);
    QVariant list=dbus_iface.call("ListNames").arguments().at(0);
    QRegExp rx("org.mpris.MediaPlayer2.*");
    qDebug()<<"List is: "<<(list.toStringList().filter(rx));
}
QStringList discoveredMprisPlayer(){
    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusInterface dbus_iface("org.freedesktop.DBus", "/org/freedesktop/DBus",
                              "org.freedesktop.DBus", bus);
    QVariant list=dbus_iface.call("ListNames").arguments().at(0);
    QRegExp rx("org.mpris.MediaPlayer2.*");
    return(list.toStringList().filter(rx));
}

void playerOperation(QString destination, QString operation){
    qDebug()<<"Call to "<<destination<<" for operation "<<operation;
    QDBusConnection bus= QDBusConnection::sessionBus();
    QDBusMessage message= QDBusMessage::createMethodCall(destination,
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player",operation);
    QDBusConnection::sessionBus().send(message);
}

void setVolume(QString destination,int sliderVal){
        //set dial
        double sliderValDouble=sliderVal;
        //qDebug()<<sliderVal<<"sliderval";
        QDBusVariant var;
        var.setVariant(QVariant::fromValue(sliderValDouble/100));
        QDBusConnection bus=QDBusConnection::sessionBus();
        QDBusInterface bus_interface(destination,"/org/mpris/MediaPlayer2","org.freedesktop.DBus.Properties",bus);
        QDBusReply<QVariant> amarokVol = bus_interface.call("Set","org.mpris.MediaPlayer2.Player","Volume",QVariant::fromValue(var));

        qDebug()<<amarokVol.value().toDouble();
        //ui->dial->setValue(100 * amarokVol.value().toDouble());
        //ui->volumeSlider->setValue(100 * amarokVol.value().toDouble());
}

void playPause(QString destination){
    QDBusConnection bus= QDBusConnection::sessionBus();
    QDBusMessage message= QDBusMessage::createMethodCall(destination,
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player","PlayPause");
    QDBusConnection::sessionBus().send(message);
}


}//end namespace QMpris

void helloWorldByLib(){
    qDebug()<<"******** Hello World *********";
}
