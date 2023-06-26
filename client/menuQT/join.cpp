#include "join.h"
#include "ui_join.h"

#include <QUrl>

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
    QPixmap pixmapFondo2(DATA_PATH "/client/render/resources/fondoqt2.jpeg");
    ui->fondo3->setPixmap(pixmapFondo2);
    ui->fondo3->setScaledContents(true);

    //icono sonido
    QPixmap pixmapIconoSonido(DATA_PATH "/client/render/resources/icono_sonido.png");
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
    player3->setMedia(QUrl::fromLocalFile(DATA_PATH "/client/render/resources/sounds/fondo3.mp3"));
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
    connect(hiloMensajes, &HiloMensajes::infoGameReceived, this, &Join::handlerInfoGameReceived);
    connect(hiloMensajes, &HiloMensajes::closedWithoutError, this, &Join::handleClosed);
    show();
    if (hiloMensajes) {
        hiloMensajes->start();
    }
}

void Create::handlerInfoGameReceived(TypeMap_t typeMap, int amountPlayers, 
                            std::vector<infoPlayerDTO_t>& infoPlayers)
{

    ui->textEdit->clear();
    ui->textEdit->append("Amount players in game: " + QString::number(amountPlayers));

    for (auto player& : infoPlayers){
        QString nickname = QString::fromStdString(player.nickname);
        QString weapon = QString::fromStdString(typeWeaponToString(player.typeWeapon));

        ui->textEdit->append("Nickname: " + nickname);
        ui->textEdit->append("Weapon: " + weapon);
        ui->textEdit->append("------------------------------------------------------");
    }
}


