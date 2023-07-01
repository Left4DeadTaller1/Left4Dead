#include "join.h"
#include "ui_join.h"

#include <QUrl>

Join::Join(ClientProtocol& protocol, 
                    std::map<QString, QPixmap>& textureIconSoldiers,
                    std::map<QString, QPixmap>& textureMaps, 
                    QWidget *parent) :
    protocol(protocol),
    textureIconSoldiers(textureIconSoldiers),
    textureMaps(textureMaps),
    QDialog(parent),
    ui(new Ui::Join),
    hiloMensajes(nullptr),
    model(this),
    exitCode(-1),
    isConnected(true)
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
    player3->setVolume(0);

    slider2->show();
    player3->play();

    // qlabel titulo map transparente
    QFont font("Arial", 12, QFont::Bold);
    ui->infoGame3->setFont(font);
    ui->infoGame3->setAttribute(Qt::WA_TranslucentBackground);
    ui->infoGame3->setStyleSheet("background-color: transparent;");

    (ui->layout3)->addWidget(ui->listView3);
    (ui->listView3)->setModel(&model);
    (ui->listView3)->setSpacing(10);
    (ui->listView3)->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QString itemStyle = "QListView::item { border-bottom: 1px solid gray; }";
    ui->listView3->setStyleSheet(itemStyle);
}

void Join::sliderChanged(int value)
{
    qreal volume = value;
    player3->setVolume(volume);
}

void Join::startReceiving()
{
    hiloMensajes = new HiloMensajes(protocol, isConnected);
    connect(hiloMensajes, &HiloMensajes::infoGameReceived, this, &Join::handlerInfoGameReceived);
    connect(hiloMensajes, &HiloMensajes::typeMapReceived, this, &Join::handlerTypeMap);
    connect(hiloMensajes, &HiloMensajes::closedWithoutError, this, &Join::handleClosed);
    show();
    if (hiloMensajes) {
        hiloMensajes->start();
    }
}

void Join::handlerTypeMap(const QString& typeMap){
    emit emitTypeMap(typeMap);
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

QPixmap Join::getTextureIconSoldier(QString typeSoldier){
    std::map<QString, QPixmap>::iterator iter = textureIconSoldiers.find(typeSoldier);
    if (iter == textureIconSoldiers.end()) {
        throw std::runtime_error("Error al cargar la textura");
    }
    return iter->second;
}

QPixmap Join::getTextureMap(QString typeMap){
    std::map<QString, QPixmap>::iterator iter = textureMaps.find(typeMap);
    if (iter == textureMaps.end()) {
        throw std::runtime_error("Error al cargar la textura");
    }
    return iter->second;
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

    QString infoMap = "Game map: " + map + "              ";
    QString infoPlayers = "Number of players in the game: " + QString::number(cantidadEntidades) + "\n";

    ui->infoGame3->setText(infoMap);
    ui->infoGame3->insert(infoPlayers);

    ui->map3->setPixmap(getTextureMap(map));
    ui->map3->setScaledContents(true);

    int width = 100;
    int height = 100;

    for (int i = 0; i < cantidadEntidades; i++) {
        QString nickname = message.value(i * 2 + 2);
        QString weapon = message.value(i * 2 + 3);

        QPixmap imageSoldierSmall = getTextureIconSoldier(weapon);

        QStandardItem* item = new QStandardItem;
        QString infoPlayer = "Nickname: " + nickname;
        infoPlayer += "                          ";
        infoPlayer += "Weapon: " + weapon + "\n";
        item->setData(infoPlayer, Qt::DisplayRole);
        item->setData(imageSoldierSmall, Qt::DecorationRole);

        QSize sizeHint(width, height);
        item->setSizeHint(sizeHint);

        model.appendRow(item);
    }
}

void Join::closeEvent(QCloseEvent *event)
{
    if (exitCode == -1){
        isConnected = false;
        protocol.closeSocket();
    }
    emit closedWithError(exitCode);
}

void Join::handleClosed(int _exitCode)
{
    exitCode = _exitCode;
    emit closedWithError(_exitCode);
}

Join::~Join()
{
    player3->setVolume(0);
    player3->stop();
    delete player3;
    delete ui;
    if (hiloMensajes) {
        hiloMensajes->join();
        delete hiloMensajes;
    }
}

