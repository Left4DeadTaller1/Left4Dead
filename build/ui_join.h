/********************************************************************************
** Form generated from reading UI file 'join.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOIN_H
#define UI_JOIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Join
{
public:
    QFrame *frame3;
    QLineEdit *infoGame3;
    QListView *listView3;
    QLabel *map3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *layout3;
    QSlider *slider2;
    QLabel *iconoSonido3;
    QLabel *fondo3;

    void setupUi(QDialog *Join)
    {
        if (Join->objectName().isEmpty())
            Join->setObjectName(QString::fromUtf8("Join"));
        Join->resize(1400, 800);
        frame3 = new QFrame(Join);
        frame3->setObjectName(QString::fromUtf8("frame3"));
        frame3->setGeometry(QRect(100, 60, 1181, 541));
        frame3->setFrameShape(QFrame::StyledPanel);
        frame3->setFrameShadow(QFrame::Raised);
        infoGame3 = new QLineEdit(frame3);
        infoGame3->setObjectName(QString::fromUtf8("infoGame3"));
        infoGame3->setGeometry(QRect(50, 20, 641, 71));
        listView3 = new QListView(frame3);
        listView3->setObjectName(QString::fromUtf8("listView3"));
        listView3->setGeometry(QRect(210, 220, 256, 192));
        listView3->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 245, 244);"));
        map3 = new QLabel(frame3);
        map3->setObjectName(QString::fromUtf8("map3"));
        map3->setGeometry(QRect(720, 20, 131, 71));
        verticalLayoutWidget = new QWidget(frame3);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(50, 110, 1071, 391));
        layout3 = new QVBoxLayout(verticalLayoutWidget);
        layout3->setObjectName(QString::fromUtf8("layout3"));
        layout3->setContentsMargins(0, 0, 0, 0);
        map3->raise();
        infoGame3->raise();
        verticalLayoutWidget->raise();
        listView3->raise();
        slider2 = new QSlider(Join);
        slider2->setObjectName(QString::fromUtf8("slider2"));
        slider2->setGeometry(QRect(1230, 770, 160, 16));
        slider2->setOrientation(Qt::Horizontal);
        iconoSonido3 = new QLabel(Join);
        iconoSonido3->setObjectName(QString::fromUtf8("iconoSonido3"));
        iconoSonido3->setGeometry(QRect(1180, 770, 31, 20));
        fondo3 = new QLabel(Join);
        fondo3->setObjectName(QString::fromUtf8("fondo3"));
        fondo3->setGeometry(QRect(0, 0, 1400, 800));
        fondo3->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 245, 244);"));
        fondo3->raise();
        frame3->raise();
        slider2->raise();
        iconoSonido3->raise();

        retranslateUi(Join);

        QMetaObject::connectSlotsByName(Join);
    } // setupUi

    void retranslateUi(QDialog *Join)
    {
        Join->setWindowTitle(QCoreApplication::translate("Join", "Dialog", nullptr));
        map3->setText(QString());
        iconoSonido3->setText(QString());
        fondo3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Join: public Ui_Join {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOIN_H
