#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMediaPlayer>
#include <QGraphicsEffect>
#include <QGraphicsColorizeEffect>
#include <QUrl>

#define VOLUMEN_DEFAULT 20

MainWindow::MainWindow(std::shared_ptr<ActionClient>& startAction, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    startAction(startAction)
{
    ui->setupUi(this);

    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::createButtonClicked);
    connect(ui->joinButton, &QPushButton::clicked, this, &MainWindow::joinButtonClicked);

    //rectangulo con transparencias
    ui->frame->setStyleSheet("background-color: transparent;");
    ui->frame->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");

    //imagen de fondo
    QPixmap pixmap("/home/usaurio/Descargas/fondoqt2.jpeg");
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

    std::cout << "Se ha presionado el botón 'Create'" << std::endl;
    std::cout << "name: " << name.toStdString() << std::endl;
    startAction = std::make_shared<Create>(name.toStdString());
    close();
}

void MainWindow::joinButtonClicked()
{
    QString name = ui->namePlayer->text();
    QString code = ui->numeroPartida->text();

    std::cout << "Se ha presionado el botón 'Join'" << std::endl;
    std::cout << "name: " << name.toStdString() << std::endl;
    std::cout << "code: " << code.toStdString() << std::endl;
    close();
}

void MainWindow::sliderChanged(int value)
{
    qreal volume = value;
    player->setVolume(volume);
}

unsigned int MainWindow::getWinId() const {
	QWidget* centralWidget = findChild<QWidget*>("centralWidget");
	// winId devuelve un unsigned int, lo devuelvo
	// casteado listo para que lo use SDL
	return centralWidget->winId();
}



