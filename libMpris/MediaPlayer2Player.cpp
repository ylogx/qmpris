#include <QtGui>
#include "QMpris.h"
#include "MediaPlayer2Player.h"

namespace QMpris{

MediaPlayer2Player::MediaPlayer2Player(QObject *parent)
    :QObject(parent)
{

}

MediaPlayer2Player::~MediaPlayer2Player()
{
}

bool MediaPlayer2Player::CanGoNext() const{
    // property read QString org.mpris.MediaPlayer2.Identity
    QString service="org.mpris.MediaPlayer2.amarok";    //temporary
    QDBusConnection bus=QDBusConnection::sessionBus();
    QDBusInterface bus_interface(service,"/org/mpris/MediaPlayer2",
                                 "org.freedesktop.DBus.Properties",bus);
    QDBusReply<QVariant> canGoNextVar = bus_interface.call("Get",
                                                           "org.mpris.MediaPlayer2.Player",
                                                           "CanGoNext");
    //qDebug()<<"The Variant canGoNextVar: "<<canGoNextVar;
    return(canGoNextVar.value().toBool());
}

void MediaPlayer2Player::Next() const{
    //method void org.mpris.MediaPlayer2.Player.Next()
    if(CanGoNext()){
        QString service="org.mpris.MediaPlayer2.amarok";    //temp
        QDBusMessage message= QDBusMessage::createMethodCall(service,
                                                             "/org/mpris/MediaPlayer2",
                                                             "org.mpris.MediaPlayer2.Player"
                                                             ,"Next");
        QDBusConnection::sessionBus().send(message);
    }
}

}//end namespace QMpris
