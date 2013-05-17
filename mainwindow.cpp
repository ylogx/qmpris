#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>

#include <QGraphicsView>
#include <QGraphicsScene>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMpris.h"

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
    listAvailablePlayers();
//    connect(ui->comboBox, SIGNAL(activated(int)),// SIGNAL(currentIndexChanged(int)),
//            this, SLOT(reconnect()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(reconnect()));
//    connect(ui->comboBox, SIGNAL(activated(int)),
//            this, SLOT(recheckMediaPlayers()));
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

    if(ui->comboBox->currentText()=="Amarok" || ui->comboBox->currentText()=="org.mpris.MediaPlayer2.amarok"){
        connectAmarok();
    }else if(ui->comboBox->currentText()=="Clementine" || ui->comboBox->currentText()=="org.mpris.MediaPlayer2.clementine"){
        connectClementine();
    }else if(ui->comboBox->currentText()=="Audacious" || ui->comboBox->currentText()=="org.mpris.MediaPlayer2.audacious"){
        connectAudacious();
    }
}

void MainWindow::listAvailablePlayers(){
    //Under Progress
    ui->comboBox->clear();
    ui->comboBox->addItem("Select any player here");

    QStringList mprisList = QMpris::discoveredMprisPlayer();

    qDebug() << mprisList << mprisList.count()<<mprisList.value(0);
    for(int i=0;i<mprisList.size();i++){
        ui->comboBox->addItem(mprisList.value(i));  //TODO use identity
        if(ui->comboBox);
    }
    //TODO automatically connect one
}//end checkAvailable

void MainWindow::connectAmarok(){
    QString service="org.mpris.MediaPlayer2.amarok";
    ui->labelPlayer->setText(QMpris::getIdentity(service));
    //***set current volume
    ui->volumeSlider->setValue( QMpris::getVolume(service) );
    setMetadata(service);
    setPositionSlider(service);
    // album art

    //connections
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
    QString service="org.mpris.MediaPlayer2.clementine";
    ui->labelPlayer->setText(QMpris::getIdentity(service));
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
    QString service="org.mpris.MediaPlayer2.audacious";
    ui->labelPlayer->setText(QMpris::getIdentity(service));
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
void MainWindow::volumeChanged(int sliderVal){
    QMpris::setVolume("org.mpris.MediaPlayer2.amarok",sliderVal);
}

void MainWindow::positionChanged(int sliderVal){
    double sliderValDouble=sliderVal * 100;  //multiple of 1000
//    //qDebug()<<sliderVal<<"sliderval";
//    QDBusVariant var;
//    var.setVariant(QVariant::fromValue(sliderValDouble/100));
    QDBusConnection bus=QDBusConnection::sessionBus();
    QDBusInterface bus_interface("org.mpris.MediaPlayer2.amarok","/org/mpris/MediaPlayer2","org.mpris.MediaPlayer2.Player",bus);
    QDBusReply<QVariant> amarokVol = bus_interface.call("Seek",(qlonglong)sliderValDouble);
                                                        //"org.mpris.MediaPlayer2.Player","Volume",QVariant::fromValue(var));
}

void MainWindow::recheckMediaPlayers(){
    listAvailablePlayers();
}

void MainWindow::showKMix(){
    //qdbus org.kde.kmix /kmix/KMixWindow com.trolltech.Qt.QWidget.show
    QDBusMessage message= QDBusMessage::createMethodCall("org.kde.kmix",
                                                         "/kmix/KMixWindow",
                                                         "com.trolltech.Qt.QWidget","show");
    QDBusConnection::sessionBus().send(message);
}


//---------------------Amarok-----------------------
void MainWindow::pauseAmarok(){
    QString destination="org.mpris.MediaPlayer2.amarok";
    QMpris::playerOperation(destination,"PlayPause");
    //qtdbus org.kde.amarok /Player org.freedesktop.MediaPlayer.Pause
    setMetadata(destination);
}
void MainWindow::nextAmarok(){
    QString str="Next";
    QString service="org.mpris.MediaPlayer2.amarok";
    QMpris::playerOperation(service,str.toLocal8Bit().data());
    setMetadata(service);
}
void MainWindow::prevAmarok(){
    QString service="org.mpris.MediaPlayer2.amarok";
    QMpris::playerOperation(service,"Previous");
    setMetadata(service);
}
void MainWindow::muteAmarok(){
    // XXX working
//    QMpris::simpleOperation("org.mpris.MediaPlayer2.amarok","Mute");
    QDBusMessage getVolume= QDBusMessage::createMethodCall("org.mpris.amarok",
                                                         "/Player",
                                                         "org.freedesktop.MediaPlayer","Mute");
    QDBusMessage volumeAmarok=QDBusConnection::sessionBus().call(getVolume);
//    bool queued=QDBusConnection::sessionBus().send(getVolume);
//    qDebug()<<"volume: "<<volumeAmarok;
//    ui->checkBoxMute->set
}
void MainWindow::showAmarok(){
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.amarok",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2","Raise");
    QDBusConnection::sessionBus().send(message);
}

//---------------------Clementine-----------------------
void MainWindow::pauseClementine(){
    QMpris::playerOperation("org.mpris.clementine","PlayPause");
}
void MainWindow::nextClementine(){
    QMpris::playerOperation("org.mpris.clementine","Next");
}
void MainWindow::prevClementine(){
    QMpris::playerOperation("org.mpris.clementine","Previous");
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
    QMpris::playerOperation("org.mpris.MediaPlayer2.audacious","PlayPause");
}
void MainWindow::nextAudacious(){
    QMpris::playerOperation("org.mpris.MediaPlayer2.audacious","Next");
}
void MainWindow::prevAudacious(){
    QMpris::playerOperation("org.mpris.MediaPlayer2.audacious","Previous");
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
    QMpris::raisePlayer("org.mpris.MediaPlayer2.audacious");
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
    ui->positionSlider->setValue( QMpris::getPosition(service) );
}
void MainWindow::setMetadata(QString service){
    QDBusConnection bus=QDBusConnection::sessionBus();
    QDBusInterface bus_interface(service,"/org/mpris/MediaPlayer2","org.freedesktop.DBus.Properties",bus);

    QDBusReply<QVariant> metaVar = bus_interface.call("Get","org.mpris.MediaPlayer2.Player","Metadata");
    QDBusArgument arg = metaVar.value().value<QDBusArgument>();
    QVariantMap metaMap;
    arg>>metaMap;
    QString title  = metaMap["xesam:title"].toString();
    QString artist = metaMap["xesam:artist"].toString();
    QString album  = metaMap["xesam:album"].toString();
    qDebug()<<title<<album<<artist;
    //set here
    ui->labelTitle->setText(title);
    ui->labelArtist->setText(artist);
    ui->labelAlbum->setText(album);
    // Album Art
    //    QGraphicsScene scene;
    //    QGraphicsPixmapItem item(QPixmap(QMpris::getArtUrl(service)));
    //    scene.addItem(&item);
    //    ui->graphicsView->setScene(&scene);

    //    QImage artImage;
    //    artImage.load(QMpris::getArtUrl(service));
    //    artImage.scaled(100,100);
    //    ui->label->setPixmap(QPixmap::fromImage(artImage));

    QPixmap pm(QMpris::getArtUrl(service));
    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(pm));
//    pm.scaled ( 100, 100, Qt::KeepAspectRatio, Qt::FastTransformation );
    ui->labelArt->setScaledContents(true);
    ui->labelArt->setPixmap(pm);
    //    ui->label->show();

    //    QImage imageObject;
    //    imageObject.load(QMpris::getArtUrl(service));
    //    ui->label->setPixmap(QPixmap::fromImage(imageObject));
}
