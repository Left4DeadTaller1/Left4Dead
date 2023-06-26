#include "join.h"
#include "ui_join.h"

Join::Join(ClientProtocol& protocol, QWidget *parent) :
    protocol(protocol),
    QDialog(parent),
    ui(new Ui::Join),
    hiloMensajes(nullptr)
{
    ui->setupUi(this);

    //rectangulo con transparencias
    ui->frame3->setStyleSheet("background-color: transparent;");
    ui->frame3->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");

    //imagen de fondo
    QPixmap pixmapFondo2(IMAGEN_FONDO_QT);
    ui->fondo3->setPixmap(pixmapFondo2);
    ui->fondo3->setScaledContents(true);

    //icono sonido
    QPixmap pixmapIconoSonido(ICONO_SONIDO_QT);
    ui->iconoSonido3->setPixmap(pixmapIconoSonido);
    ui->iconoSonido3->setScaledContents(true);

    connect(this, &Join::rejected, this, [this]() {
        emit closedWithError(-1);
        close();
    });

    //barra de volumen
    QSlider *slider3 = new QSlider(Qt::Horizontal, this);
    ui->slider3->setRange(0, 100);
    ui->slider3->setValue(20);

    connect(ui->slider3, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));

    player3 = new QMediaPlayer(this);
    player3->setMedia(QUrl::fromLocalFile(SOUND_FONDO_QT));
    player3->setVolume(20);

    slider3->show();
    player3->play();
}

void Join::closeEvent(QCloseEvent *event)
{
    emit closedWithError(-1);
}

void Join::handleClosed(int exitCode)
{
    emit closedWithError(exitCode);
}

void Join::sliderChanged(int value)
{
    qreal volume = value;
    player3->setVolume(volume);
}

Join::~Join()
{
    delete ui;
    if (hiloMensajes) {
        hiloMensajes->join();
        delete hiloMensajes;
    }
}

void Join::startReceiving()
{
    hiloMensajes = new HiloMensajes(protocol);
    connect(hiloMensajes, &HiloMensajes::joinReceived, this, &Join::handleJoinReceived);
    connect(hiloMensajes, &HiloMensajes::closedWithoutError, this, &Join::handleClosed);
    show();
    if (hiloMensajes) {
        hiloMensajes->start();
    }
}

void Join::handleJoinReceived(const QString& nickname, const QString& weapon)
{
    ui->textEdit3->append("Nickname: " + nickname);
    ui->textEdit3->append("Weapon: " + weapon);
    ui->textEdit3->append("------------------------------------------------------");
}


