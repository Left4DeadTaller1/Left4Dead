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
    QPixmap pixmapFondo2(DATA_PATH "/client/render/resources/fondoqt2.jpeg");
    ui->fondo2->setPixmap(pixmapFondo2);
    ui->fondo2->setScaledContents(true);

    // Icono de sonido
    QPixmap pixmapIconoSonido(DATA_PATH "/client/render/resources/icono_sonido.png");
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
    player->setMedia(QUrl::fromLocalFile(DATA_PATH "/client/render/resources/sounds/fondo3.mp3"));
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

std::string Create::typeWeaponToString(TypeWeapon_t type){
    if (type == P90){
        return "P90";
    }
    if (type == RIFLE){
        return "Rifle";
    }
    if (type == SNIPER){
        return "Sniper";
    }
    return "";
}

void Create::handlerInfoGameReceived(TypeMap_t typeMap, int amountPlayers, 
                            std::vector<infoPlayerDTO_t>& infoPlayers)
{

    ui->textEdit->clear();
    ui->textEdit->append("Amount players in game: " + QString::number(amountPlayers));

    for (auto &player : infoPlayers){
        QString nickname = QString::fromStdString(player.nickname);
        QString weapon = QString::fromStdString(typeWeaponToString(player.typeWeapon));

        ui->textEdit->append("Nickname: " + nickname);
        ui->textEdit->append("Weapon: " + weapon);
        ui->textEdit->append("------------------------------------------------------");
    }
}

void Create::startReceiving()
{
    hiloMensajes = new HiloMensajes(protocol);
    connect(hiloMensajes, &HiloMensajes::infoGameReceived, this, &Create::handlerInfoGameReceived);
    connect(hiloMensajes, &HiloMensajes::closedWithoutError, this, &Create::handleClosed);
    
    show();
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



