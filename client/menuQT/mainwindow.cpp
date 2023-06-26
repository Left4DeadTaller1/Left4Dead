#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "client/actions/action_create.h"
#include "client/actions/action_join.h"
#include "client/actions/action_client.h"

MainWindow::MainWindow(ClientProtocol& protocol, QWidget *parent)
    : protocol(protocol),
    QMainWindow(parent), 
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //rectangulo con transparencias
    ui->frame->setStyleSheet("background-color: transparent;");
    ui->frame->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");

    //imagen de fondo
    QPixmap pixmapFondo(IMAGEN_FONDO_QT);
    ui->fondo->setPixmap(pixmapFondo);
    ui->fondo->setScaledContents(true);

    //icono sonido
    QPixmap pixmapIconoSonido(ICONO_SONIDO_QT);
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
    ui->weapons->addItem("Opción 1");
    ui->weapons->addItem("Opción 2");
    ui->weapons->addItem("Opción 3");

    //opciones de mapas
    ui->mapas->addItem("Opción 1");
    ui->mapas->addItem("Opción 2");
    ui->mapas->addItem("Opción 3");
    ui->mapas->addItem("Opción 4");

    c = new Create(protocol, this);
    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::createButtonClicked);
    connect(c, &Create::closedWithError, this, &MainWindow::handleCreateClosed);

    j = new Join(protocol, this);
    connect(ui->joinButton, &QPushButton::clicked, this, &MainWindow::joinButtonClicked);
    connect(j, &Join::closedWithError, this, &MainWindow::handleJoinClosed);

    //barra de volumen
    QSlider *slider = new QSlider(Qt::Horizontal, this);
    ui->slider->setRange(0, 100);
    ui->slider->setValue(20);

    connect(ui->slider, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));

    player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile(SOUND_FONDO_QT));
    player->setVolume(20);

    slider->show();
    player->play();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete c;
    delete j;
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
        std::string namePlayer = nickname.toStdString();
        std::string weaponPlayer = weapon.toStdString();
        std::string map = mapa.toStdString();
        std::shared_ptr<ActionClient> action = std::make_shared<CreateAction>(namePlayer,
                                                                        weaponPlayer,
                                                                        map);
        protocol.sendAction(std::move(action), wasClosed);
        player->stop();
        hide();
        c->startReceiving();
    } else {
        //mensaje de que se deben rellanar los campos
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
        std::string namePlayer = nickname.toStdString();
        std::string weaponPlayer = weapon.toStdString();
        std::string codeGame = code.toStdString();
        std::shared_ptr<ActionClient> action = std::make_shared<JoinAction>(namePlayer,
                                                                    weaponPlayer,
                                                                    codeGame);
        protocol.sendAction(std::move(action), wasClosed);
        player->stop();
        hide();
        j->show();
        j->startReceiving();
    } else {
        //mensaje de que se deben rellanar los campos
    }
}

void MainWindow::sliderChanged(int value)
{
    qreal volume = value;
    player->setVolume(volume);
}

void MainWindow::handleCreateClosed(int code)
{
    if (code == 0){
        close();
    } else {
        QApplication::exit(code);
    }
}

void MainWindow::handleJoinClosed(int code)
{
    if (code == 0){
        close();
    } else {
        QApplication::exit(code);
    }
}

