/********************************************************************************
** Form generated from reading UI file 'create.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATE_H
#define UI_CREATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Create
{
public:
    QLabel *fondo2;
    QSlider *slider2;
    QLabel *iconoSonido2;
    QFrame *frame2;
    QLineEdit *infoGame;
    QListView *listView;
    QLabel *map;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *layout;
    QPushButton *startButton;

    void setupUi(QDialog *Create)
    {
        if (Create->objectName().isEmpty())
            Create->setObjectName(QString::fromUtf8("Create"));
        Create->resize(1400, 800);
        fondo2 = new QLabel(Create);
        fondo2->setObjectName(QString::fromUtf8("fondo2"));
        fondo2->setGeometry(QRect(0, 0, 1400, 800));
        fondo2->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 245, 244);"));
        slider2 = new QSlider(Create);
        slider2->setObjectName(QString::fromUtf8("slider2"));
        slider2->setGeometry(QRect(1230, 770, 160, 16));
        slider2->setOrientation(Qt::Horizontal);
        iconoSonido2 = new QLabel(Create);
        iconoSonido2->setObjectName(QString::fromUtf8("iconoSonido2"));
        iconoSonido2->setGeometry(QRect(1180, 770, 31, 20));
        frame2 = new QFrame(Create);
        frame2->setObjectName(QString::fromUtf8("frame2"));
        frame2->setGeometry(QRect(100, 60, 1181, 541));
        frame2->setFrameShape(QFrame::StyledPanel);
        frame2->setFrameShadow(QFrame::Raised);
        infoGame = new QLineEdit(frame2);
        infoGame->setObjectName(QString::fromUtf8("infoGame"));
        infoGame->setGeometry(QRect(50, 20, 641, 71));
        listView = new QListView(frame2);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(210, 220, 256, 192));
        listView->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 245, 244);"));
        map = new QLabel(frame2);
        map->setObjectName(QString::fromUtf8("map"));
        map->setGeometry(QRect(720, 20, 131, 71));
        verticalLayoutWidget = new QWidget(frame2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(50, 110, 891, 391));
        layout = new QVBoxLayout(verticalLayoutWidget);
        layout->setObjectName(QString::fromUtf8("layout"));
        layout->setContentsMargins(0, 0, 0, 0);
        startButton = new QPushButton(frame2);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(980, 460, 161, 41));
        startButton->setStyleSheet(QString::fromUtf8("font: 500 14pt \"Ubuntu\";\n"
"border-color: rgb(154, 153, 150);"));
        map->raise();
        infoGame->raise();
        verticalLayoutWidget->raise();
        listView->raise();
        startButton->raise();
        fondo2->raise();
        frame2->raise();
        slider2->raise();
        iconoSonido2->raise();

        retranslateUi(Create);

        QMetaObject::connectSlotsByName(Create);
    } // setupUi

    void retranslateUi(QDialog *Create)
    {
        Create->setWindowTitle(QCoreApplication::translate("Create", "Dialog", nullptr));
        fondo2->setText(QString());
        iconoSonido2->setText(QString());
        map->setText(QString());
        startButton->setText(QCoreApplication::translate("Create", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Create: public Ui_Create {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATE_H
