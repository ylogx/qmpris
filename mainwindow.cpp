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

void MainWindow::listAvailablePlayers(){
    //Under Progress
    ui->comboBox->clear();
    ui->comboBox->addItem("Select any player here");

    QStringList mprisList = QMpris::discoveredMprisPlayer();

    qDebug() << mprisList << mprisList.count()<<mprisList.value(0);
    for(int i=0;i<mprisList.size();i++){
        ui->comboBox->addItem(QMpris::getIdentity(mprisList.value(i)));
        if(ui->comboBox);
    }
    //TODO automatically connect one
}//end checkAvailable

QString MainWindow::currentPlayer(){
    if(ui->comboBox->currentText()=="Amarok" || ui->comboBox->currentText()=="org.mpris.MediaPlayer2.amarok"){
        return ("org.mpris.MediaPlayer2.amarok");
    }else if(ui->comboBox->currentText()=="Clementine" || ui->comboBox->currentText()=="org.mpris.MediaPlayer2.clementine"){
        return ("org.mpris.MediaPlayer2.clementine");
    }else if(ui->comboBox->currentText()=="Audacious" || ui->comboBox->currentText()=="org.mpris.MediaPlayer2.audacious"){
        return ("org.mpris.MediaPlayer2.audacious");
    }else if(ui->comboBox->currentText()=="Rhythmbox" || ui->comboBox->currentText()=="org.mpris.MediaPlayer2.rhythmbox"){
        return ("org.mpris.MediaPlayer2.rhythmbox");
    }else if(ui->comboBox->currentText()=="JuK" || ui->comboBox->currentText()=="org.mpris.MediaPlayer2.juk"){
        return ("org.mpris.MediaPlayer2.juk");
    }else if(ui->comboBox->currentText()=="Vlc" || ui->comboBox->currentText()=="org.mpris.MediaPlayer2.vlc"){
        return ("org.mpris.MediaPlayer2.vlc");
    }


}

void MainWindow::reconnect(){
    ui->pushButtonPlay->disconnect();
    ui->pushButtonNext->disconnect();
    ui->pushButtonPrev->disconnect();
    ui->pushButtonShow->disconnect();
    ui->checkBoxMute->disconnect();

    QString service = currentPlayer();

    ui->labelPlayer->setText(QMpris::getIdentity(service));
    //***set current volume
    ui->volumeSlider->setValue( QMpris::getVolume(service) );
    setMetadata(service);
    setPositionSlider(service);
    //connections
    basicConnections(); //play,pause,next,prev,showPlayer
    //specific connections
    if(service=="org.mpris.MediaPlayer2.amarok"){
        connect(ui->checkBoxMute, SIGNAL(stateChanged(int)),
                this, SLOT(muteAmarok()));
        connect(ui->volumeSlider, SIGNAL(valueChanged(int)),
                this, SLOT(volumeChanged(int)));
    //    connect(ui->positionSlider, SIGNAL(valueChanged(int)),
    //            this, SLOT(positionChanged(int)));
        connect(ui->positionSlider, SIGNAL(sliderMoved(int)),
                this, SLOT(positionChanged(int)));
    }else if(service=="org.mpris.MediaPlayer2.clementine"){
        connect(ui->checkBoxMute, SIGNAL(stateChanged(int)),
                this, SLOT(muteClementine()));
        connect(ui->volumeSlider, SIGNAL(valueChanged(int)),
                this, SLOT(volumeChanged(int)));
        connect(ui->positionSlider, SIGNAL(sliderMoved(int)),
                this, SLOT(positionChanged(int)));
    }else if(service=="org.mpris.MediaPlayer2.audacious"){
        connect(ui->checkBoxMute, SIGNAL(toggled(bool muteState)),
                this, SLOT(muteAudacious(muteState)));
        connect(ui->volumeSlider, SIGNAL(valueChanged(int)),
                this, SLOT(volumeChanged(int)));
        connect(ui->positionSlider, SIGNAL(sliderMoved(int)),
                this, SLOT(positionChanged(int)));
    }else if(service=="org.mpris.MediaPlayer2.rhythmbox"){
        connect(ui->volumeSlider, SIGNAL(valueChanged(int)),
                this, SLOT(volumeChanged(int)));
        connect(ui->positionSlider, SIGNAL(sliderMoved(int)),
                this, SLOT(positionChanged(int)));
    }//else do nothing, make no connections

}

void MainWindow::basicConnections(){
    connect(ui->pushButtonPlay, SIGNAL(clicked()),
            this, SLOT(pause()));
    connect(ui->pushButtonNext, SIGNAL(clicked()),
            this, SLOT(next()));
    connect(ui->pushButtonPrev, SIGNAL(clicked()),
            this, SLOT(prev()));
    connect(ui->pushButtonShow, SIGNAL(clicked()),
            this, SLOT(showPlayer()));
}

//****************************
//***********SLOTS************
//****************************
void MainWindow::volumeChanged(int sliderVal){
    switch(ui->labelPlayer->text().length()){
    case 6://"Amarok":
        QMpris::setVolume("org.mpris.MediaPlayer2.amarok",sliderVal);
        break;
    case 9://"Audacious":
        QMpris::setVolume("org.mpris.MediaPlayer2.audacious",sliderVal);
        break;
    case 10://"Clementine":
        QMpris::setVolume("org.mpris.MediaPlayer2.clementine",sliderVal);
        break;
    default: break;
    }
}

void MainWindow::positionChanged(int sliderVal){
    double sliderValDouble=sliderVal * 1000 * 10;  //multiple of 1000
    //TODO make it work according to tracklength
    switch(ui->labelPlayer->text().length()){
    case 6://"Amarok":
        QMpris::seek("org.mpris.MediaPlayer2.amarok",sliderValDouble);
        break;
    case 9://"Audacious":
        QMpris::seek("org.mpris.MediaPlayer2.audacious",sliderValDouble);
        break;
    case 10://"Clementine":
        QMpris::seek("org.mpris.MediaPlayer2.clementine",sliderValDouble);
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

void MainWindow::pause(){
    QString service = currentPlayer();
    QMpris::playerOperation(service,"PlayPause");
    setMetadata(service);
}
void MainWindow::next(){
    QString service = currentPlayer();
    QMpris::playerOperation(service,"Next");
    setMetadata(service);
}
void MainWindow::prev(){
    QString service = currentPlayer();
    QMpris::playerOperation(service,"Previous");
    setMetadata(service);
}

void MainWindow::showPlayer(){
    QMpris::raisePlayer(currentPlayer());
}


//---------------------Amarok-----------------------

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

//---------------------Clementine-----------------------
void MainWindow::muteClementine(){
    QDBusMessage getVolume= QDBusMessage::createMethodCall("org.mpris.clementine",
                                                         "/Player",
                                                         "org.freedesktop.MediaPlayer","Mute");
    QDBusConnection::sessionBus().send(getVolume);
}

//---------------------Rhythmbox-----------------------

//--------------Audacious-----------------------------------
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
    //track time
    long length=QMpris::getTrackLength(service);
    long milliseconds   = (long) (length / 1000) % 1000;
    long seconds    = (((long) (length / 1000) - milliseconds)/1000)%60 ;
    long minutes    = (((((long) (length / 1000) - milliseconds)/1000) - seconds)/60) %60 ;
    long hours      = ((((((long) (length / 1000) - milliseconds)/1000) - seconds)/60) - minutes)/60;
    QString formatStr;
    formatStr.append(QString("%1").arg(minutes));
    formatStr.append(":");
    formatStr.append(QString("%1").arg(seconds));
    ui->labelLength->setText(formatStr);
}
