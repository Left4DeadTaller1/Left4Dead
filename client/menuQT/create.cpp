#include "create.h"
#include "ui_create.h"

Create::Create(ClientProtocol& protocol, QWidget *parent) :
    QDialog(parent),
    protocol(protocol),
    ui(new Ui::Create),
    hiloMensajes(nullptr),
    model(this)
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

    (ui->layout)->addWidget(ui->listView);
    (ui->listView)->setModel(&model);
    (ui->listView)->setSpacing(10);
    (ui->listView)->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QString itemStyle = "QListView::item { border-bottom: 1px solid gray; }";
    ui->listView->setStyleSheet(itemStyle);
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

std::string Create::getImageSoldier(QString& weapon){
    if (weapon == "P90"){
        return DATA_PATH "/client/render/resources/iconSoldier1.png";
    }
    if (weapon == "Rifle"){
        return DATA_PATH "/client/render/resources/iconSoldier2.png";
    }
    if (weapon == "Sniper"){
        return DATA_PATH "/client/render/resources/iconSoldier3.png";
    }
    return "";
}

std::string Create::getImageMap(QString& map){
    if (map == "War 1 Bright"){
        return DATA_PATH "/client/render/resources/backgrounds/War1/Bright/War.png";
    }
    if (map == "War 1 Pale"){
        return DATA_PATH "/client/render/resources/backgrounds/War1/Pale/War.png";
    }
    if (map == "War 2 Bright"){
        return DATA_PATH "/client/render/resources/backgrounds/War2/Bright/War.png";
    }
    if (map == "War 2 Pale"){
        return DATA_PATH "/client/render/resources/backgrounds/War2/Pale/War.png";
    }
    if (map == "War 3 Bright"){
        return DATA_PATH "/client/render/resources/backgrounds/War3/Bright/War.png";
    }
    if (map == "War 2 Pale"){
        return DATA_PATH "/client/render/resources/backgrounds/War3/Pale/War.png";
    }
    if (map == "War 4 Bright"){
        return DATA_PATH "/client/render/resources/backgrounds/War4/Bright/War.png";
    }
    if (map == "War 4 Pale"){
        return DATA_PATH "/client/render/resources/backgrounds/War4/Pale/War.png";
    }
    return "";
}

void Create::handlerInfoGameReceived(const QString& messageInfoGame)
{
    int rowCount = model.rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QStandardItem* item = model.item(i);
        if (item) {
            delete item;
        }
    }
    model.clear();

    QStringList message = messageInfoGame.split(';');
    QString map = message.value(0);
    int cantidadEntidades = message.value(1).toInt();

    ui->infoGame->setText(map);

    //imagen de mapa
    std::string mapPath = getImageMap(map);
    QPixmap mapa(QString::fromStdString(mapPath));
    ui->map->setPixmap(mapa);
    ui->map->setScaledContents(true);

    for (int i = 0; i < cantidadEntidades; i++) {
        QString nickname = message.value(i * 2 + 2);
        QString weapon = message.value(i * 2 + 3);

        std::string imageSoldierPath = getImageSoldier(weapon);
        QPixmap imageSoldier(QString::fromStdString(imageSoldierPath));

        int width = 100;
        int height = 100;
        QPixmap imageSoldierSmall = imageSoldier.scaled(width, height, Qt::KeepAspectRatio);

        QStandardItem* item = new QStandardItem;
        QString infoPlayer = "Nickname: " + nickname + "\n\n" + "Weapon: " + weapon + "\n";
        item->setData(infoPlayer, Qt::DisplayRole);
        item->setData(imageSoldierSmall, Qt::DecorationRole);

        QSize sizeHint(width, height);
        item->setSizeHint(sizeHint);

        model.appendRow(item);
    }
}

void Create::startReceiving()
{
    hiloMensajes = new HiloMensajes(protocol);
    connect(hiloMensajes, &HiloMensajes::infoGameReceived, this, &Create::handlerInfoGameReceived);
    connect(hiloMensajes, &HiloMensajes::closedWithoutError, this, &Create::handleClosed);
    
    show();
    if (hiloMensajes) {
        std::cout << "antes de lanzar el hilo\n";
        hiloMensajes->start();
        std::cout << "despues de lanzar el hilo\n";
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



