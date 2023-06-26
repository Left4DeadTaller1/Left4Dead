#include "create.h"
#include "ui_create.h"

Create::Create(ClientProtocol& protocol, QWidget *parent) :
    QDialog(parent),
    protocol(protocol),
    ui(new Ui::Create),
    hiloMensajes(nullptr)
{
    ui->setupUi(this);

    // Rectángulo con transparencias
    ui->frame2->setStyleSheet("background-color: transparent;");
    ui->frame2->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");

    // Imagen de fondo
    QPixmap pixmapFondo2("/home/usaurio/Descargas/fondoqt2.jpeg");
    ui->fondo2->setPixmap(pixmapFondo2);
    ui->fondo2->setScaledContents(true);

    // Icono de sonido
    QPixmap pixmapIconoSonido("/home/usaurio/Descargas/images-removebg-preview.png");
    ui->iconoSonido2->setPixmap(pixmapIconoSonido);
    ui->iconoSonido2->setScaledContents(true);

    // Barra de volumen
    ui->slider2->setRange(0, 100);
    ui->slider2->setValue(20);

    connect(ui->startButton, &QPushButton::clicked, this, &Create::startButtonClicked);

    connect(this, &Create::rejected, this, [this]() {
        emit closedWithError(-1);
        close();
    });

    player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile("/home/usaurio/Descargas/18 left for death.mp3"));
    player->setVolume(20);
    player->play();
}

void Create::handleClosed(int exitCode)
{
    emit closedWithError(exitCode);
}

void Create::sliderChanged(int value)
{
    qreal volume = value;
    player->setVolume(volume);
}

Create::~Create()
{
    delete ui;
    if (hiloMensajes) {
        hiloMensajes->join();
        delete hiloMensajes;
    }
}

void Create::handleJoinReceived(const QString& nickname, const QString& weapon)
{
    // Actualizar la interfaz de usuario con los datos recibidos
    ui->textEdit->append("Nickname: " + nickname);
    ui->textEdit->append("Weapon: " + weapon);
    ui->textEdit->append("------------------------------------------------------");
}

void Create::startReceiving()
{
    hiloMensajes = new HiloMensajes(protocol);
    connect(hiloMensajes, &HiloMensajes::joinReceived, this, &Create::handleJoinReceived);
    connect(hiloMensajes, &HiloMensajes::closedWithoutError, this, &Create::handleClosed);
    
    show();
    bool wasClosed = false;
    protocol.receiveTypeMessage(wasClosed);
    protocol.receiveCreate(wasClosed);
    if (hiloMensajes) {
        hiloMensajes->start();
    }
}

void Create::startButtonClicked()
{
    bool wasClosed = false;
    std::shared_ptr<ActionClient> action = std::make_shared<StartGame>();
    protocol.sendAction(std::move(action), wasClosed);
}

void Create::closeEvent(QCloseEvent *event)
{
    emit closedWithError(-1);
}



