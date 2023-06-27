#include "join.h"
#include "ui_join.h"

#include <QUrl>

Join::Join(ClientProtocol& protocol, QWidget *parent) :
    protocol(protocol),
    QDialog(parent),
    ui(new Ui::Join),
    hiloMensajes(nullptr),
    model(this)
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
    QSlider *slider2 = new QSlider(Qt::Horizontal, this);
    ui->slider2->setRange(0, 100);
    ui->slider2->setValue(20);

    connect(ui->slider2, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));

    player3 = new QMediaPlayer(this);
    player3->setMedia(QUrl::fromLocalFile(DATA_PATH "/client/render/resources/sounds/fondo3.mp3"));
    player3->setVolume(20);

    slider2->show();
    player3->play();

    (ui->layout3)->addWidget(ui->listView3);
    (ui->listView3)->setModel(&model);
    (ui->listView3)->setSpacing(10);
    (ui->listView3)->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QString itemStyle = "QListView::item { border-bottom: 1px solid gray; }";
    ui->listView3->setStyleSheet(itemStyle);
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

std::string Join::typeWeaponToString(TypeWeapon_t type){
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

std::string Join::getImageSoldier(QString& weapon){
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

std::string Join::getImageMap(QString& map){
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

void Join::handlerInfoGameReceived(const QString& messageInfoGame)
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

    ui->infoGame3->setText(map);

    //imagen de mapa
    std::string mapPath = getImageMap(map);
    QPixmap mapa(QString::fromStdString(mapPath));
    ui->map3->setPixmap(mapa);
    ui->map3->setScaledContents(true);

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


