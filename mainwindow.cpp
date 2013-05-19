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
    connect(ui->pushButtonRefresh, SIGNAL(clicked()),
            this, SLOT(recheckMediaPlayers()));
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
        ui->comboBox->addItem(QMpris::getIdentity(mprisList.value(i)));  //TODO use identity
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
//    connect(ui->positionSlider, SIGNAL(valueChanged(int)),
//            this, SLOT(positionChanged(int)));
    connect(ui->positionSlider, SIGNAL(sliderMoved(int)),
            this, SLOT(positionChanged(int)));
}
void MainWindow::connectAudacious(){
    QString service="org.mpris.MediaPlayer2.audacious";
    ui->labelPlayer->setText(QMpris::getIdentity(service));
    //***set current volume
    ui->volumeSlider->setValue( QMpris::getVolume(service) );
    setMetadata(service);
    setPositionSlider(service);
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
    connect(ui->volumeSlider, SIGNAL(valueChanged(int)),
            this, SLOT(volumeChanged(int)));
    connect(ui->positionSlider, SIGNAL(sliderMoved(int)),
            this, SLOT(positionChanged(int)));
}
void MainWindow::connectClementine(){
    QString service="org.mpris.MediaPlayer2.clementine";
    ui->labelPlayer->setText(QMpris::getIdentity(service));
    //***set current volume
    ui->volumeSlider->setValue( QMpris::getVolume(service) );
    setMetadata(service);
    setPositionSlider(service);
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
    connect(ui->volumeSlider, SIGNAL(valueChanged(int)),
            this, SLOT(volumeChanged(int)));
    connect(ui->positionSlider, SIGNAL(sliderMoved(int)),
            this, SLOT(positionChanged(int)));
}

//****************************
//***********SLOTS************
//****************************
void MainWindow::volumeChanged(int sliderVal){
    switch(ui->labelPlayer->text().length()){
    case 7://"Amarok":
        QMpris::setVolume("org.mpris.MediaPlayer2.amarok",sliderVal);
        break;
    case 9://"Audacious":
        QMpris::setVolume("org.mpris.MediaPlayer2.audacious",sliderVal);
        break;
    case 10://"Clementine":
        QMpris::setVolume("org.mpris.MediaPlayer2.audacious",sliderVal);
        break;
    default: break;
    }
}

void MainWindow::positionChanged(int sliderVal){
    double sliderValDouble=sliderVal * 1000 * 10;  //multiple of 1000
//    //qDebug()<<sliderVal<<"sliderval";
    //TODO make it work according to tracklength
    switch(ui->labelPlayer->text().length()){
    case 7://"Amarok":
        QMpris::seek("org.mpris.MediaPlayer2.amarok",sliderValDouble);
        break;
    case 9://"Audacious":
        QMpris::seek("org.mpris.MediaPlayer2.audacious",sliderValDouble);
        break;
    case 10://"Clementine":
        QMpris::seek("org.mpris.MediaPlayer2.audacious",sliderValDouble);
        break;
    default: break;
    }
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
    QString service="org.mpris.MediaPlayer2.clementine";
    QMpris::playerOperation(service,"PlayPause");
    setMetadata(service);
}
void MainWindow::nextClementine(){
    QString service="org.mpris.MediaPlayer2.clementine";
    QMpris::playerOperation(service,"Next");
    setMetadata(service);
}
void MainWindow::prevClementine(){
    QString service="org.mpris.MediaPlayer2.clementine";
    QMpris::playerOperation(service,"Previous");
    setMetadata(service);
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
    QString service="org.mpris.MediaPlayer2.audacious";
    QMpris::playerOperation(service,"PlayPause");
    setMetadata(service);
}
void MainWindow::nextAudacious(){
    QString str="Next";
    QString service="org.mpris.MediaPlayer2.audacious";
    QMpris::playerOperation(service,str);
    setMetadata(service);
}
void MainWindow::prevAudacious(){
    QString service="org.mpris.MediaPlayer2.audacious";
    QMpris::playerOperation(service,"Previous");
    setMetadata(service);
}
void MainWindow::showAudacious(){
    //ui->pushButtonShow->setText("Can't Raise");
    QMpris::raisePlayer("org.mpris.MediaPlayer2.audacious");
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

//******Other functions
void MainWindow::setPositionSlider(QString service){
    ui->positionSlider->setValue( QMpris::getPosition(service) );
}
void MainWindow::setMetadata(QString service){
    QStringList strList(QMpris::getMetadata(service));
    ui->labelTitle->setText(strList.at(0));
    ui->labelArtist->setText(strList.at(1));
    ui->labelAlbum->setText(strList.at(2));
//    ui->labelTitle->setText(title);
//    ui->labelArtist->setText(artist);
//    ui->labelAlbum->setText(album);
    // --- Album Art ---
    QString artUrl=QMpris::getArtUrl(service);
    if(artUrl != ""){
        QPixmap pm(artUrl);
        setAutoFillBackground(true);
        QPalette palette;
        palette.setBrush(QPalette::Window, QBrush(pm));
        //    pm.scaled ( 100, 100, Qt::KeepAspectRatio, Qt::FastTransformation );
        ui->labelArt->setScaledContents(true);
        ui->labelArt->setPixmap(pm);

        //    QGraphicsScene scene;
        //    QGraphicsPixmapItem item(QPixmap(QMpris::getArtUrl(service)));
        //    scene.addItem(&item);
        //    ui->graphicsView->setScene(&scene);

        //    QImage artImage;
        //    artImage.load(QMpris::getArtUrl(service));
        //    artImage.scaled(100,100);
        //    ui->label->setPixmap(QPixmap::fromImage(artImage));


        //    QImage imageObject;
        //    imageObject.load(QMpris::getArtUrl(service));
        //    ui->label->setPixmap(QPixmap::fromImage(imageObject));
    }else{
        ui->labelArt->setText("No Art");
    }
}
