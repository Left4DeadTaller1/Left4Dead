#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMediaPlayer>
#include <QGraphicsEffect>
#include <QGraphicsColorizeEffect>
#include <QUrl>

#define VOLUMEN_DEFAULT 20

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
    
{
    ui->setupUi(this);

    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::createButtonClicked);
    connect(ui->joinButton, &QPushButton::clicked, this, &MainWindow::joinButtonClicked);

    //rectangulo con transparencias
    ui->frame->setStyleSheet("background-color: transparent;");
    ui->frame->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");

    //imagen de fondo
    QPixmap pixmap(IMAGEN_FONDO_QT);
    ui->fondo->setPixmap(pixmap);
    ui->fondo->setScaledContents(true);

    //barra de volumen
    QSlider *slider = new QSlider(Qt::Horizontal, this);
    ui->slider->setRange(0, 100);
    ui->slider->setValue(20);

    connect(ui->slider, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));

    player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile(FONDO_QT));
    player->setVolume(20);

    slider->show();
    player->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createButtonClicked()
{
    QString name = ui->namePlayer->text();

    inicialActionType = "create";
    namePlayer = name.toStdString();
    close();
}

void MainWindow::joinButtonClicked()
{
    QString name = ui->namePlayer->text();
    QString code = ui->numeroPartida->text();

    inicialActionType = "join";
    namePlayer = name.toStdString();
    codeGame = code.toStdString();
    close();
}

void MainWindow::sliderChanged(int value)
{
    qreal volume = value;
    player->setVolume(volume);
}

std::string MainWindow::getInicialActionType(){
    return inicialActionType;
}

std::string MainWindow::getNamePlayer(){
    return namePlayer;
}

std::string MainWindow::getCodeGame(){
    return codeGame;
}


