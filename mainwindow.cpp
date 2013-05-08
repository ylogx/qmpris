#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), QDBusMessage(),
    ui(new Ui::MainWindow)
{
    //ui->menuBar->setWindowTitle(tr("Shubham Chaudhary"));
    ui->setupUi(this);
    ui->labelPlayer->setText("No Player Selected :( Use combo box");
    ui->checkBoxMute->setChecked(false);    // XXX
    connect(ui->pushButtonKMix, SIGNAL(clicked()),
            this, SLOT(showKMix()));
    //ui->dial->scroll(1,1);
    checkAvailablePlayer();
    connect(ui->comboBox, SIGNAL(activated(int)),// SIGNAL(currentIndexChanged(int)),
            this, SLOT(reconnect()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(reconnect()));
}//end constructor

MainWindow::~MainWindow()
{
    delete ui;
}//end destructor

void MainWindow::reconnect(){
    ui->pushButtonPlay->disconnect();
    ui->pushButtonNext->disconnect();
    ui->pushButtonPrev->disconnect();
    ui->pushButtonShow->disconnect();
    ui->checkBoxMute->disconnect();

    if(ui->comboBox->currentText()=="Amarok"){
        connectAmarok();
    }else if(ui->comboBox->currentText()=="Clementine"){
        connectClementine();
    }else if(ui->comboBox->currentText()=="Audacious"){
        connectAudacious();
    }
}

void MainWindow::checkAvailablePlayer(){
    //Under Progress
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
    for(int i=0;i<mprisList.size();i++){
        QDBusInterface dbusIface(mprisList.value(i),"/org/mpris/mediaPlayer2",
                                 "org.mpris.MediaPlayer2",bus);
        ///qDebug()<<dbusIface.service();
        //qDebug()<<dbusIface.property("Identity");
//        OrgMprisMediaPlayer2Interface obj(mprisList.value(i),"/org/mpris/mediaPlayer2",
//                                          QDBusConnection::sessionBus(),this);
//        qDebug()<<obj.property("Identity");//.toStringList();
//        ui->comboBox->addItem(playerName);
    }
// * * * Amarok * * *
    QDBusInterface *interface=new QDBusInterface("org.mpris.amarok",
                                                 "/org/mpris/MediaPlayer2",
                                                 "org.freedesktop.DBus.Introspectable",
                                                 bus);
    QDBusReply<QString> amarokReply= interface->call("Introspect");
    //qDebug()<<amarokReply;
    if(amarokReply.value()!=""){
        ui->comboBox->addItem("Amarok");
        //qDebug()<<"here";
        connectAmarok();    //by default
    }
}//end checkAvailable

void MainWindow::connectAmarok(){
    QString service="org.mpris.MediaPlayer2.amarok";
    QDBusConnection bus=QDBusConnection::sessionBus();
    QDBusInterface bus_interface(service,"/org/mpris/MediaPlayer2","org.freedesktop.DBus.Properties",bus);
    QDBusReply<QVariant> playerIdentity = bus_interface.call("Get","org.mpris.MediaPlayer2.Player","Identity");
    qDebug()<<"Identity"<<playerIdentity.value().toString();

    ui->labelPlayer->setText("Amarok");
    //***set current volume
    QDBusReply<QVariant> amarokVol = bus_interface.call("Get","org.mpris.MediaPlayer2.Player","Volume");
    qDebug()<<amarokVol.value().toDouble();
    //ui->dial->setValue(100 * amarokVol.value().toDouble());
    ui->volumeSlider->setValue(100 * amarokVol.value().toDouble());
    setMetadata(service);
    setPositionSlider(service);
    connect(ui->pushButtonPlay, SIGNAL(clicked()),
            this, SLOT(pauseAmarok()));
    connect(ui->pushButtonNext, SIGNAL(clicked()),
            this, SLOT(nextAmarok()));
    connect(ui->pushButtonPrev, SIGNAL(clicked()),
            this, SLOT(prevAmarok()));
    connect(ui->checkBoxMute, SIGNAL(stateChanged(int)),
            this, SLOT(muteAmarok()));
    connect(ui->pushButtonShow, SIGNAL(clicked()),
            this, SLOT(showAmarok()));
    connect(ui->volumeSlider, SIGNAL(valueChanged(int)),
            this, SLOT(volumeChanged(int)));
    connect(ui->positionSlider, SIGNAL(valueChanged(int)),
            this, SLOT(positionChanged(int)));
}
void MainWindow::connectClementine(){
    ui->labelPlayer->setText("Clementine");
    connect(ui->pushButtonPlay, SIGNAL(clicked()),
            this, SLOT(pauseClementine()));
    connect(ui->pushButtonNext, SIGNAL(clicked()),
            this, SLOT(nextClementine()));
    connect(ui->pushButtonPrev, SIGNAL(clicked()),
            this, SLOT(prevClementine()));
    connect(ui->checkBoxMute, SIGNAL(stateChanged(int)),
            this, SLOT(muteClementine()));
    connect(ui->pushButtonShow, SIGNAL(clicked()),
            this, SLOT(showClementine()));
}
void MainWindow::connectAudacious(){
    ui->labelPlayer->setText("Audacious");
    connect(ui->pushButtonPlay, SIGNAL(clicked()),
            this, SLOT(pauseAudacious()));
    connect(ui->pushButtonNext, SIGNAL(clicked()),
            this, SLOT(nextAudacious()));
    connect(ui->pushButtonPrev, SIGNAL(clicked()),
            this, SLOT(prevAudacious()));
    connect(ui->checkBoxMute, SIGNAL(toggled(bool muteState)),
            this, SLOT(muteAudacious(muteState)));
    connect(ui->pushButtonShow, SIGNAL(clicked()),
            this, SLOT(showAudacious()));
}
//****************************
//***********SLOTS************
//****************************
void MainWindow::showKMix(){
    //qdbus org.kde.kmix /kmix/KMixWindow com.trolltech.Qt.QWidget.show
    QDBusMessage message= QDBusMessage::createMethodCall("org.kde.kmix",
                                                         "/kmix/KMixWindow",
                                                         "com.trolltech.Qt.QWidget","show");
    QDBusConnection::sessionBus().send(message);
}

void MainWindow::volumeChanged(int sliderVal){
    QString service="org.mpris.MediaPlayer2.amarok";
    //set dial
    double sliderValDouble=sliderVal;
    //qDebug()<<sliderVal<<"sliderval";
    QDBusVariant var;
    var.setVariant(QVariant::fromValue(sliderValDouble/100));
    QDBusConnection bus=QDBusConnection::sessionBus();
    QDBusInterface bus_interface(service,"/org/mpris/MediaPlayer2","org.freedesktop.DBus.Properties",bus);
    QDBusReply<QVariant> amarokVol = bus_interface.call("Set","org.mpris.MediaPlayer2.Player","Volume",QVariant::fromValue(var));

    //qDebug()<<amarokVol.value().toDouble();
    //ui->dial->setValue(100 * amarokVol.value().toDouble());
    //ui->volumeSlider->setValue(100 * amarokVol.value().toDouble());
}
void MainWindow::positionChanged(int sliderVal){
    //set dial
    double sliderValDouble=sliderVal;
//    //qDebug()<<sliderVal<<"sliderval";
//    QDBusVariant var;
//    var.setVariant(QVariant::fromValue(sliderValDouble/100));
    QDBusConnection bus=QDBusConnection::sessionBus();
    QDBusInterface bus_interface("org.mpris.MediaPlayer2.amarok","/org/mpris/MediaPlayer2","org.freedesktop.DBus.Properties",bus);
    QDBusReply<QVariant> amarokVol = bus_interface.call("Seek",(qlonglong)sliderValDouble);
                                                        //"org.mpris.MediaPlayer2.Player","Volume",QVariant::fromValue(var));

    //qDebug()<<amarokVol.value().toDouble();
    //ui->dial->setValue(100 * amarokVol.value().toDouble());
    //ui->volumeSlider->setValue(100 * amarokVol.value().toDouble());
}

//---------------------Amarok-----------------------
void MainWindow::pauseAmarok(){
    //QDBusConnection bus = QDBusConnection::sessionBus();
    //qtdbus org.kde.amarok /Player org.freedesktop.MediaPlayer.Pause
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.amarok",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player","PlayPause");
    QDBusConnection::sessionBus().send(message);
}
void MainWindow::nextAmarok(){
    char str[20]="Next";
    QString service="org.mpris.MediaPlayer2.amarok";
    QDBusMessage message= QDBusMessage::createMethodCall(service,
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player",str);
    //qDebug()<<str<<" mess: "<<message;
    QDBusConnection::sessionBus().send(message);
    setMetadata(service);
}
void MainWindow::prevAmarok(){
    QString service="org.mpris.MediaPlayer2.amarok";
    QDBusMessage message= QDBusMessage::createMethodCall(service,
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player","Previous");
    QDBusConnection::sessionBus().send(message);
    //qDebug()<<" mess: "<<message;
    setMetadata(service);
}
void MainWindow::muteAmarok(){
    // XXX working
    QDBusMessage getVolume= QDBusMessage::createMethodCall("org.mpris.amarok",
                                                         "/Player",
                                                         "org.freedesktop.MediaPlayer","Mute");
    QDBusMessage volumeAmarok=QDBusConnection::sessionBus().call(getVolume);
    //bool queued=QDBusConnection::sessionBus().send(getVolume);
    qDebug()<<"volume: "<<volumeAmarok;
    //ui->checkBoxMute->set
}
void MainWindow::showAmarok(){
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.amarok",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2","Raise");
    QDBusConnection::sessionBus().send(message);
}

//---------------------Clementine-----------------------
void MainWindow::pauseClementine(){
    //QDBusConnection bus = QDBusConnection::sessionBus();
    //qtdbus org.kde.amarok /Player org.freedesktop.MediaPlayer.Pause
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.clementine",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player","PlayPause");
    QDBusConnection::sessionBus().send(message);
}
void MainWindow::nextClementine(){
    char str[20]="Next";
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.clementine",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player",str);
    //qDebug()<<str<<" mess: "<<message;
    QDBusConnection::sessionBus().send(message);
}
void MainWindow::prevClementine(){
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.clementine",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player","Previous");
    QDBusConnection::sessionBus().send(message);
    //qDebug()<<" mess: "<<message;
}
void MainWindow::muteClementine(){
    QDBusMessage getVolume= QDBusMessage::createMethodCall("org.mpris.clementine",
                                                         "/Player",
                                                         "org.freedesktop.MediaPlayer","Mute");
    QDBusConnection::sessionBus().send(getVolume);
}
void MainWindow::showClementine(){
    // xxx not supported
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.clementine",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2","Raise");
    QDBusConnection::sessionBus().send(message);
}


//--------------Audacious-----------------------------------
void MainWindow::pauseAudacious(){
    //QDBusConnection bus = QDBusConnection::sessionBus();
    //qtdbus org.kde.amarok /Player org.freedesktop.MediaPlayer.Pause
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.MediaPlayer2.audacious",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player","PlayPause");
    QDBusConnection::sessionBus().send(message);
    //qDebug()<<"pause mess:"<<message;
}
void MainWindow::nextAudacious(){
    char str[20]="Next";
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.audacious",
                                                         "/Player",
                                                         "org.freedesktop.MediaPlayer",str);
    //qDebug()<<str<<" mess: "<<message;
    QDBusConnection::sessionBus().send(message);
}
void MainWindow::prevAudacious(){
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.audacious",
                                                         "/Player",
                                                         "org.freedesktop.MediaPlayer","Prev");
    QDBusConnection::sessionBus().send(message);
    //qDebug()<<" mess: "<<message;
}
void MainWindow::muteAudacious(bool muteState){
    // XXX working
    QDBusMessage getVolume= QDBusMessage::createMethodCall("org.mpris.audacious",
                                                           "/Player",
                                                           "org.freedesktop.MediaPlayer","VolumeSet");

    QList<QVariant> args;
    if(muteState){
        args<<0;
    }
    getVolume.setArguments(args);
    //QDBusMessage volumeAmarok=QDBusConnection::sessionBus().call(getVolume);
    QDBusConnection::sessionBus().send(getVolume);
    //qDebug()<<"volume: "<<volumeAmarok;
    //ui->checkBoxMute->set
}
void MainWindow::showAudacious(){
    //ui->pushButtonShow->setText("Can't Raise");
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.MediaPlayer2.audacious",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2","Raise");
    QDBusConnection::sessionBus().send(message);
    qDebug()<<"raise mess: "<<message;
    //    QDBusMessage m= QDBusMessage::createMethodCall("org.mpris.amarok",
    //                                                   "/org/mpris/MediaPlayer2",
    //                                                   "org.mpris.MediaPlayer2.Player","SetPosition");
    //    QList<QVariant> args;     // QList of QVariant objects
    //    args.append(7);
    //    args.append(30);
    //    m.setArguments(args);     //can also use overloaded << directly
    //    bool queued=QDBusConnection::sessionBus().send(m);
    //    qDebug()<<queued<<" mess: "<<m;
    //    QDBusMessage m= QDBusMessage::createMethodCall("org.mpris.amarok",
    //                                                   "/Tracklist",
    //                                                   "org.freedesktop.MediaPlayer","GetLength");//"GetCurrentTrack");
    //    QDBusReply<int> response=QDBusConnection::sessionBus().call(m);
    //    qDebug()<<" mess: "<<response;
    //    QList<QVariant> list=response.arguments(); //QDBusMessage::arguments();
    //    qDebug()<<"0: "<<list[0].toInt();
}

//******Other functions
void MainWindow::setPositionSlider(QString service){
    QDBusConnection bus=QDBusConnection::sessionBus();
    QDBusInterface bus_interface(service,"/org/mpris/MediaPlayer2","org.freedesktop.DBus.Properties",bus);

    QDBusReply<QVariant> metaVar = bus_interface.call("Get","org.mpris.MediaPlayer2.Player","Metadata");
    QDBusArgument arg = metaVar.value().value<QDBusArgument>();
    QVariantMap metaMap;
    arg>>metaMap;
    QString title = metaMap["xesam:title"].toString();
    QString album = metaMap["xesam:album"].toString();
    QString artist = metaMap["xesam:artist"].toString();
    long int length = metaMap["mpris:length"].toInt();
    //qDebug()<<title<<album<<artist<<length;
    //***set current track position
    QDBusReply<QVariant> amarokPos = bus_interface.call("Get","org.mpris.MediaPlayer2.Player","Position");
    //qDebug()<<amarokPos;
    //ui->dial->setValue(100 * amarokVol.value().toDouble());
    ui->positionSlider->setValue(100*amarokPos.value().toDouble()/length);

}
void MainWindow::setMetadata(QString service){
    QDBusConnection bus=QDBusConnection::sessionBus();
    QDBusInterface bus_interface(service,"/org/mpris/MediaPlayer2","org.freedesktop.DBus.Properties",bus);

    QDBusReply<QVariant> metaVar = bus_interface.call("Get","org.mpris.MediaPlayer2.Player","Metadata");
    QDBusArgument arg = metaVar.value().value<QDBusArgument>();
    QVariantMap metaMap;
    arg>>metaMap;
    QString title = metaMap["xesam:title"].toString();
    QString artist = metaMap["xesam:artist"].toString();
    QString album = metaMap["xesam:album"].toString();
    qDebug()<<title<<album<<artist;
    //set here
    ui->labelTitle->setText(title);
    ui->labelArtist->setText(artist);
    ui->labelAlbum->setText(album);
}
