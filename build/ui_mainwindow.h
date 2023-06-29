/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *fondo;
    QFrame *frame;
    QPushButton *createButton;
    QPushButton *joinButton;
    QComboBox *weapons;
    QLineEdit *nickname;
    QLabel *labelNickname;
    QLabel *labelWeapon;
    QLineEdit *code;
    QFrame *horizontalLine;
    QFrame *verticalLine;
    QComboBox *mapas;
    QLabel *labelMap;
    QLabel *labelCode;
    QSlider *slider;
    QLabel *iconoSonido;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1400, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        fondo = new QLabel(centralwidget);
        fondo->setObjectName(QString::fromUtf8("fondo"));
        fondo->setGeometry(QRect(0, 0, 1400, 800));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(250, 150, 900, 450));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 245, 244);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        createButton = new QPushButton(frame);
        createButton->setObjectName(QString::fromUtf8("createButton"));
        createButton->setGeometry(QRect(80, 360, 321, 51));
        createButton->setStyleSheet(QString::fromUtf8("font: 500 14pt \"Ubuntu\";\n"
"border-color: rgb(154, 153, 150);"));
        joinButton = new QPushButton(frame);
        joinButton->setObjectName(QString::fromUtf8("joinButton"));
        joinButton->setGeometry(QRect(510, 360, 321, 51));
        joinButton->setStyleSheet(QString::fromUtf8("font: 500 14pt \"Ubuntu\";\n"
"border-color: rgb(154, 153, 150);"));
        weapons = new QComboBox(frame);
        weapons->setObjectName(QString::fromUtf8("weapons"));
        weapons->setGeometry(QRect(500, 100, 321, 25));
        weapons->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        nickname = new QLineEdit(frame);
        nickname->setObjectName(QString::fromUtf8("nickname"));
        nickname->setGeometry(QRect(80, 100, 321, 25));
        nickname->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        labelNickname = new QLabel(frame);
        labelNickname->setObjectName(QString::fromUtf8("labelNickname"));
        labelNickname->setGeometry(QRect(80, 60, 121, 21));
        labelNickname->setStyleSheet(QString::fromUtf8("font: 500 18pt \"Ubuntu\";"));
        labelWeapon = new QLabel(frame);
        labelWeapon->setObjectName(QString::fromUtf8("labelWeapon"));
        labelWeapon->setGeometry(QRect(500, 60, 101, 31));
        labelWeapon->setStyleSheet(QString::fromUtf8("font: 500 18pt \"Ubuntu\";"));
        code = new QLineEdit(frame);
        code->setObjectName(QString::fromUtf8("code"));
        code->setGeometry(QRect(510, 270, 321, 25));
        code->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        horizontalLine = new QFrame(frame);
        horizontalLine->setObjectName(QString::fromUtf8("horizontalLine"));
        horizontalLine->setGeometry(QRect(50, 170, 811, 16));
        horizontalLine->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"border-color: rgb(0, 0, 0);"));
        horizontalLine->setFrameShape(QFrame::HLine);
        horizontalLine->setFrameShadow(QFrame::Sunken);
        verticalLine = new QFrame(frame);
        verticalLine->setObjectName(QString::fromUtf8("verticalLine"));
        verticalLine->setGeometry(QRect(450, 220, 20, 191));
        verticalLine->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"border-color: rgb(0, 0, 0);"));
        verticalLine->setFrameShape(QFrame::VLine);
        verticalLine->setFrameShadow(QFrame::Sunken);
        mapas = new QComboBox(frame);
        mapas->setObjectName(QString::fromUtf8("mapas"));
        mapas->setGeometry(QRect(80, 270, 321, 25));
        labelMap = new QLabel(frame);
        labelMap->setObjectName(QString::fromUtf8("labelMap"));
        labelMap->setGeometry(QRect(80, 220, 121, 31));
        labelMap->setStyleSheet(QString::fromUtf8("font: 500 18pt \"Ubuntu\";"));
        labelCode = new QLabel(frame);
        labelCode->setObjectName(QString::fromUtf8("labelCode"));
        labelCode->setGeometry(QRect(520, 230, 121, 31));
        labelCode->setStyleSheet(QString::fromUtf8("font: 500 18pt \"Ubuntu\";"));
        createButton->raise();
        joinButton->raise();
        labelNickname->raise();
        nickname->raise();
        labelWeapon->raise();
        weapons->raise();
        code->raise();
        horizontalLine->raise();
        verticalLine->raise();
        mapas->raise();
        labelMap->raise();
        labelCode->raise();
        slider = new QSlider(centralwidget);
        slider->setObjectName(QString::fromUtf8("slider"));
        slider->setGeometry(QRect(1220, 770, 160, 16));
        slider->setOrientation(Qt::Horizontal);
        iconoSonido = new QLabel(centralwidget);
        iconoSonido->setObjectName(QString::fromUtf8("iconoSonido"));
        iconoSonido->setGeometry(QRect(1170, 770, 41, 21));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        fondo->setText(QString());
        createButton->setText(QCoreApplication::translate("MainWindow", "Create", nullptr));
        joinButton->setText(QCoreApplication::translate("MainWindow", "Join", nullptr));
        labelNickname->setText(QCoreApplication::translate("MainWindow", "nickname", nullptr));
        labelWeapon->setText(QCoreApplication::translate("MainWindow", "weapon", nullptr));
        labelMap->setText(QCoreApplication::translate("MainWindow", "map", nullptr));
        labelCode->setText(QCoreApplication::translate("MainWindow", "game code", nullptr));
        iconoSonido->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
