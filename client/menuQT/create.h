#ifndef CREATE_H
#define CREATE_H

#include <QDialog>
#include <QMediaPlayer>
#include "client/client_connection/client_protocol.h"
#include "client/actions/action_start_game.h"
#include "client/actions/action_client.h"
#include "hiloMensajes.h"
#include <memory>

namespace Ui {
class Create;
}

class Create : public QDialog
{
    Q_OBJECT

public:
    explicit Create(ClientProtocol& protocol, QWidget *parent = nullptr);
    void startReceiving();
    ~Create();

signals:
    void closedWithError(int exitCode);

private slots:
    void startButtonClicked();
    void closeEvent(QCloseEvent *event);
    void sliderChanged(int value);
    void handlerInfoGameReceived(TypeMap_t typeMap, int amountPlayers, 
                            std::vector<infoPlayerDTO_t>& infoPlayers);
    void handleClosed(int exitCode);
    std::string typeWeaponToString(TypeWeapon_t type);

private:
    ClientProtocol& protocol;
    Ui::Create *ui;
    QMediaPlayer *player;
    HiloMensajes* hiloMensajes;
};

#endif // CREATE_H


