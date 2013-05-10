/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu May 9 22:11:35 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QLabel *labelPlayer;
    QPushButton *pushButtonShow;
    QSpacerItem *verticalSpacer_2;
    QSlider *positionSlider;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonKMix;
    QCheckBox *checkBoxMute;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelTitle;
    QLabel *labelArtist;
    QLabel *labelAlbum;
    QHBoxLayout *horButtonLayout;
    QPushButton *pushButtonPrev;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonNext;
    QVBoxLayout *verticalLayout_3;
    QSlider *volumeSlider;
    QCheckBox *checkBoxMute_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(346, 424);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 331, 361));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        comboBox = new QComboBox(horizontalLayoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        labelPlayer = new QLabel(horizontalLayoutWidget);
        labelPlayer->setObjectName(QString::fromUtf8("labelPlayer"));
        labelPlayer->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelPlayer);

        pushButtonShow = new QPushButton(horizontalLayoutWidget);
        pushButtonShow->setObjectName(QString::fromUtf8("pushButtonShow"));
        pushButtonShow->setDefault(true);

        verticalLayout->addWidget(pushButtonShow);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        positionSlider = new QSlider(horizontalLayoutWidget);
        positionSlider->setObjectName(QString::fromUtf8("positionSlider"));
        positionSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(positionSlider);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButtonKMix = new QPushButton(horizontalLayoutWidget);
        pushButtonKMix->setObjectName(QString::fromUtf8("pushButtonKMix"));

        verticalLayout->addWidget(pushButtonKMix);

        checkBoxMute = new QCheckBox(horizontalLayoutWidget);
        checkBoxMute->setObjectName(QString::fromUtf8("checkBoxMute"));

        verticalLayout->addWidget(checkBoxMute);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labelTitle = new QLabel(horizontalLayoutWidget);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));

        verticalLayout_2->addWidget(labelTitle);

        labelArtist = new QLabel(horizontalLayoutWidget);
        labelArtist->setObjectName(QString::fromUtf8("labelArtist"));

        verticalLayout_2->addWidget(labelArtist);

        labelAlbum = new QLabel(horizontalLayoutWidget);
        labelAlbum->setObjectName(QString::fromUtf8("labelAlbum"));

        verticalLayout_2->addWidget(labelAlbum);

        horButtonLayout = new QHBoxLayout();
        horButtonLayout->setSpacing(6);
        horButtonLayout->setObjectName(QString::fromUtf8("horButtonLayout"));
        pushButtonPrev = new QPushButton(horizontalLayoutWidget);
        pushButtonPrev->setObjectName(QString::fromUtf8("pushButtonPrev"));

        horButtonLayout->addWidget(pushButtonPrev);

        pushButtonPlay = new QPushButton(horizontalLayoutWidget);
        pushButtonPlay->setObjectName(QString::fromUtf8("pushButtonPlay"));

        horButtonLayout->addWidget(pushButtonPlay);

        pushButtonNext = new QPushButton(horizontalLayoutWidget);
        pushButtonNext->setObjectName(QString::fromUtf8("pushButtonNext"));

        horButtonLayout->addWidget(pushButtonNext);


        verticalLayout_2->addLayout(horButtonLayout);


        horizontalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        volumeSlider = new QSlider(horizontalLayoutWidget);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setOrientation(Qt::Vertical);

        verticalLayout_3->addWidget(volumeSlider);

        checkBoxMute_2 = new QCheckBox(horizontalLayoutWidget);
        checkBoxMute_2->setObjectName(QString::fromUtf8("checkBoxMute_2"));

        verticalLayout_3->addWidget(checkBoxMute_2);


        horizontalLayout_4->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 346, 21));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        labelPlayer->setText(QApplication::translate("MainWindow", "Current Player", 0, QApplication::UnicodeUTF8));
        pushButtonShow->setText(QApplication::translate("MainWindow", "&Show Player", 0, QApplication::UnicodeUTF8));
        pushButtonKMix->setText(QApplication::translate("MainWindow", "Show KMi&x", 0, QApplication::UnicodeUTF8));
        checkBoxMute->setText(QApplication::translate("MainWindow", "&Mute", 0, QApplication::UnicodeUTF8));
        labelTitle->setText(QApplication::translate("MainWindow", "Sorry,", 0, QApplication::UnicodeUTF8));
        labelArtist->setText(QApplication::translate("MainWindow", "Unable to fetch data", 0, QApplication::UnicodeUTF8));
        labelAlbum->setText(QApplication::translate("MainWindow", "from the music player", 0, QApplication::UnicodeUTF8));
        pushButtonPrev->setText(QApplication::translate("MainWindow", "&Previous", 0, QApplication::UnicodeUTF8));
        pushButtonPlay->setText(QApplication::translate("MainWindow", "Play/Pa&use", 0, QApplication::UnicodeUTF8));
        pushButtonNext->setText(QApplication::translate("MainWindow", "&Next", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        volumeSlider->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        volumeSlider->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        volumeSlider->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        checkBoxMute_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
