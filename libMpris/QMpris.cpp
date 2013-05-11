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

QString getIdentity(QString service){
    // property read QString org.mpris.MediaPlayer2.Identity
    QDBusConnection bus=QDBusConnection::sessionBus();
    QDBusInterface bus_interface(service,"/org/mpris/MediaPlayer2","org.freedesktop.DBus.Properties",bus);
    QDBusReply<QVariant> idenVar = bus_interface.call("Get","org.mpris.MediaPlayer2","Identity");
//    qDebug()<<"the variant: "<<idenVar;
    return(idenVar.value().toString());
}

long getTrackLength(QString service){
        QDBusConnection bus=QDBusConnection::sessionBus();
        QDBusInterface bus_interface(service,"/org/mpris/MediaPlayer2","org.freedesktop.DBus.Properties",bus);
        //get track length
        QDBusReply<QVariant> metaVar = bus_interface.call("Get","org.mpris.MediaPlayer2.Player","Metadata");
        QDBusArgument arg = metaVar.value().value<QDBusArgument>();
        QVariantMap metaMap;
        arg>>metaMap;
        long int length = metaMap["mpris:length"].toInt();
        return (length);
}

double getPosition(QString service){
    QDBusConnection bus=QDBusConnection::sessionBus();
    QDBusInterface bus_interface(service,"/org/mpris/MediaPlayer2","org.freedesktop.DBus.Properties",bus);
    //get track length
    long int length = getTrackLength(service);  //metaMap["mpris:length"].toInt();
    //get position
    QDBusReply<QVariant> amarokPos = bus_interface.call("Get","org.mpris.MediaPlayer2.Player","Position");

    return(100*amarokPos.value().toDouble()/length);
}

double getVolume(QString destination){
    QDBusInterface bus_interface(destination,"/org/mpris/MediaPlayer2",
                                 "org.freedesktop.DBus.Properties",
                                 QDBusConnection::sessionBus() );
    //***set current volume
    QDBusReply<QVariant> volumeReply = bus_interface.call("Get",
                                                          "org.mpris.MediaPlayer2.Player",
                                                          "Volume");
    return( 100 * volumeReply.value().toDouble() );
}

void setVolume(QString destination,int sliderVal){
    //set dial
//    qDebug()<<"Slider Value: "<<sliderVal;
    if (sliderVal < 0.0)
        sliderVal = 0.0;
    if (sliderVal > 100.0)
        sliderVal = 100.0;
    double sliderValDouble=sliderVal;
    //qDebug()<<sliderVal<<"sliderval";
    QDBusVariant var;
    var.setVariant(QVariant::fromValue(sliderValDouble/100));
    QDBusConnection bus=QDBusConnection::sessionBus();
    QDBusInterface bus_interface(destination,"/org/mpris/MediaPlayer2","org.freedesktop.DBus.Properties",bus);
    QDBusReply<QVariant> amarokVol = bus_interface.call("Set","org.mpris.MediaPlayer2.Player","Volume",QVariant::fromValue(var));

//    qDebug()<<amarokVol.value().toDouble();
    //ui->dial->setValue(100 * amarokVol.value().toDouble());
    //ui->volumeSlider->setValue(100 * amarokVol.value().toDouble());
}
void raisePlayer(QString destination){
    QDBusMessage message= QDBusMessage::createMethodCall(destination,
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2","Raise");
    QDBusConnection::sessionBus().send(message);
    //    qDebug()<<"raise mess: "<<message;
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
