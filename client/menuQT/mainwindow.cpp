#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "client/actions/action_create.h"
#include "client/actions/action_join.h"
#include "client/actions/action_client.h"

MainWindow::MainWindow(ClientProtocol& protocol, QWidget *parent)
    : protocol(protocol),
    QMainWindow(parent), 
    ui(new Ui::MainWindow),
    returnCode(-1)
{
    ui->setupUi(this);
    loadTextures();

    //rectangulo con transparencias
    ui->frame->setStyleSheet("background-color: transparent;");
    ui->frame->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");

    //imagen de fondo
    QPixmap pixmapFondo(DATA_PATH "/client/render/resources/fondoqt2.jpeg");
    ui->fondo->setPixmap(pixmapFondo);
    ui->fondo->setScaledContents(true);

    //icono sonido
    QPixmap pixmapIconoSonido(DATA_PATH "/client/render/resources/icono_sonido.png");
    ui->iconoSonido->setPixmap(pixmapIconoSonido);
    ui->iconoSonido->setScaledContents(true);

    ui->horizontalLine->setFrameShape(QFrame::HLine);
    ui->horizontalLine->setStyleSheet("background-color: transparent; border: none; border-top: 1px solid black;");

    ui->verticalLine->setFrameShape(QFrame::VLine);
    ui->verticalLine->setStyleSheet("background-color: transparent; border: none; border-left: 1px solid black;");

    // qlabel nickname transparente
    QFont font("Arial", 16, QFont::Bold);
    ui->labelNickname->setFont(font);
    ui->labelNickname->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelNickname->setStyleSheet("background-color: transparent;");

    // qlabel map transparente
    ui->labelMap->setFont(font);
    ui->labelMap->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelMap->setStyleSheet("background-color: transparent;");

    // qlabel weapon transparente
    ui->labelWeapon->setFont(font);
    ui->labelWeapon->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelWeapon->setStyleSheet("background-color: transparent;");

    // qlabel code transparente
    ui->labelCode->setFont(font);
    ui->labelCode->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelCode->setStyleSheet("background-color: transparent;");

    //opciones de armas
    ui->weapons->addItem("P90");
    ui->weapons->addItem("Rifle");
    ui->weapons->addItem("Sniper");

    //opciones de mapas
    ui->mapas->addItem("War 1 Bright");
    ui->mapas->addItem("War 1 Pale");
    ui->mapas->addItem("War 2 Bright");
    ui->mapas->addItem("War 2 Pale");
    ui->mapas->addItem("War 3 Bright");
    ui->mapas->addItem("War 3 Pale");
    ui->mapas->addItem("War 4 Bright");
    ui->mapas->addItem("War 4 Pale");

    c = new Create(protocol, textureIconSoldiers, textureMaps, this);
    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::createButtonClicked);
    connect(c, &Create::closedWithError, this, &MainWindow::handleCreateClosed);

    j = new Join(protocol, textureIconSoldiers, textureMaps, this);
    connect(ui->joinButton, &QPushButton::clicked, this, &MainWindow::joinButtonClicked);
    connect(j, &Join::closedWithError, this, &MainWindow::handleJoinClosed);

    ui->slider->setRange(0, 100);
    ui->slider->setValue(20);

    connect(ui->slider, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));

    player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile(DATA_PATH "/client/render/resources/sounds/fondo3.mp3"));
    player->setVolume(50);

    ui->slider->show();
    player->play();

    connect(c, &Create::emitTypeMap, this, &MainWindow::handlerTypeMap);
    connect(j, &Join::emitTypeMap, this, &MainWindow::handlerTypeMap);
}

void MainWindow::loadTextures(void) {
    textureMaps.emplace("War 1 Bright", QPixmap(DATA_PATH "/client/render/resources/backgrounds/War1/Bright/War.png"));
    textureMaps.emplace("War 1 Pale", QPixmap(DATA_PATH "/client/render/resources/backgrounds/War1/Pale/War.png"));
    textureMaps.emplace("War 2 Bright", QPixmap(DATA_PATH "/client/render/resources/backgrounds/War2/Bright/War2.png"));
    textureMaps.emplace("War 2 Pale", QPixmap(DATA_PATH "/client/render/resources/backgrounds/War2/Pale/War2.png"));
    textureMaps.emplace("War 3 Bright", QPixmap(DATA_PATH "/client/render/resources/backgrounds/War3/Bright/War3.png"));
    textureMaps.emplace("War 3 Pale", QPixmap(DATA_PATH "/client/render/resources/backgrounds/War3/Pale/War3.png"));
    textureMaps.emplace("War 4 Bright", QPixmap(DATA_PATH "/client/render/resources/backgrounds/War4/Bright/War4.png"));
    textureMaps.emplace("War 4 Pale", QPixmap(DATA_PATH "/client/render/resources/backgrounds/War4/Pale/War4.png"));

    int width = 100;
    int height = 100;
    QPixmap imageSoldier1(DATA_PATH "/client/render/resources/iconSoldier1.png");
    QPixmap imageSoldier2(DATA_PATH "/client/render/resources/iconSoldier2.png");
    QPixmap imageSoldier3(DATA_PATH "/client/render/resources/iconSoldier3.png");
    textureIconSoldiers.emplace("P90", imageSoldier1.scaled(width, height, Qt::KeepAspectRatio));
    textureIconSoldiers.emplace("Rifle", imageSoldier2.scaled(width, height, Qt::KeepAspectRatio));
    textureIconSoldiers.emplace("Sniper", imageSoldier3.scaled(width, height, Qt::KeepAspectRatio));
}

TypeMap_t MainWindow::StringToTypeMap(const std::string& map) {
    if (map == "War 1 Bright") {
        return WAR1_BRIGHT;
    }
    if (map == "War 1 Pale") {
        return WAR1_PALE;
    }
    if (map == "War 2 Bright") {
        return WAR2_BRIGHT;
    }
    if (map == "War 2 Pale") {
        return WAR2_PALE;
    }
    if (map == "War 3 Bright") {
        return WAR3_BRIGHT;
    }
    if (map == "War 3 Pale") {
        return WAR3_PALE;
    }
    if (map == "War 4 Bright") {
        return WAR4_BRIGHT;
    }
    if (map == "War 4 Pale") {
        return WAR4_PALE;
    }
}

TypeWeapon_t MainWindow::StringToTypeWeapon(const std::string& weaponPlayer) {
    if (weaponPlayer == "P90"){
        return P90;
    }
    if (weaponPlayer == "Rifle"){
        return RIFLE;
    }
    if (weaponPlayer == "Sniper"){
        return SNIPER;
    }
}

void MainWindow::handlerTypeMap(const QString& typeMap_){
    typeMap = StringToTypeMap(typeMap_.toStdString());
}

void MainWindow::createButtonClicked()
{
    QString nickname = ui->nickname->text();

    int indiceWeapon = ui->weapons->currentIndex();
    QString weapon = ui->weapons->currentText();

    int indiceMapa = ui->mapas->currentIndex();
    QString mapa = ui->mapas->currentText();

    if (indiceWeapon != -1 && !nickname.isEmpty() && indiceMapa != -1) {
        bool wasClosed = false;
        namePlayer = nickname.toStdString();
        std::string weaponPlayer = weapon.toStdString();
        std::string map = mapa.toStdString();
        std::shared_ptr<ActionClient> action = std::make_shared<CreateAction>(namePlayer,
                                                                StringToTypeWeapon(weaponPlayer),
                                                                StringToTypeMap(map));
        protocol.sendAction(std::move(action), wasClosed);
        player->setVolume(0);
        player->stop();
        hide();
        c->startReceiving();
    } else {
        QMessageBox::warning(this, "Campos vacíos", "Por favor complete todos los campos.");
    }

    connect(c, &Create::closedWithError, this, &MainWindow::exitApp);
}

void MainWindow::joinButtonClicked()
{
    QString nickname = ui->nickname->text();

    int indiceWeapon = ui->weapons->currentIndex();
    QString weapon = ui->weapons->currentText();

    QString code = ui->code->text();

    if (indiceWeapon != -1 && !nickname.isEmpty() && !code.isEmpty()) {
        bool wasClosed = false;
        namePlayer = nickname.toStdString();
        std::string weaponPlayer = weapon.toStdString();
        std::string codeGame = code.toStdString();
        std::shared_ptr<ActionClient> action = std::make_shared<JoinAction>(namePlayer,
                                                                    StringToTypeWeapon(weaponPlayer),
                                                                    std::stoi(codeGame));
        protocol.sendAction(std::move(action), wasClosed);
        player->setVolume(0);
        player->stop();
        hide();
        j->show();
        j->startReceiving();
    } else {
        QMessageBox::warning(this, "Campos vacíos", "Por favor complete todos los campos.");
    }
}

void MainWindow::sliderChanged(int value)
{
    qreal volume = value;
    player->setVolume(volume);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (returnCode == 0){
        close();
    } else {
        close();
        QApplication::exit(returnCode);
    }
}

void MainWindow::handleCreateClosed(int code)
{
    returnCode = code;
    if (code == 0){
        close();
    } else {
        close();
        QApplication::exit(code);
    }
}

void MainWindow::handleJoinClosed(int code)
{
    returnCode = code;
    if (code == 0){
        close();
    } else {
        close();
        QApplication::exit(code);
    }
}

std::string MainWindow::getNamePlayer(void){
    return namePlayer;
}

TypeMap_t MainWindow::getTypeMap(void){
    return typeMap;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete c;
    delete j;
    player->stop();
    delete player;
}







