#ifndef JOIN_H
#define JOIN_H

#include <QDialog>
#include <QMediaPlayer>
#include "client/client_connection/client_protocol.h"
#include "hiloMensajes.h"

namespace Ui {
class Join;
}

class Join : public QDialog
{
    Q_OBJECT

public:
    explicit Join(ClientProtocol& protocol, QWidget *parent = nullptr);
    void startReceiving();
    ~Join();

signals:
    void closedWithError(int exitCode);

private slots:
    void closeEvent(QCloseEvent *event);
    void sliderChanged(int value);
    void handlerInfoGameReceived(TypeMap_t typeMap, int amountPlayers, 
                            std::vector<infoPlayerDTO_t>& infoPlayers);
    void handleClosed(int exitCode);
    std::string typeWeaponToString(TypeWeapon_t type);

private:
    ClientProtocol& protocol;
    Ui::Join *ui;
    QMediaPlayer *player3;
    HiloMensajes* hiloMensajes;
};

#endif // JOIN_H
