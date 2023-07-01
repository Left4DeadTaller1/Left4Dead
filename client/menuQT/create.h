#ifndef CREATE_H
#define CREATE_H

#include <QDialog>
#include <QMediaPlayer>
#include "client/client_connection/client_protocol.h"
#include "client/actions/action_start_game.h"
#include "client/actions/action_client.h"
#include "hiloMensajes.h"
#include <memory>
#include <atomic>
#include <QStandardItemModel>

namespace Ui {
class Create;
}

class Create : public QDialog
{
    Q_OBJECT

public:
    Create(ClientProtocol& protocol, 
            std::map<QString, QPixmap>& textureIconSoldiers,
            std::map<QString, QPixmap>& textureMaps,
            QWidget *parent = nullptr);
    void startReceiving();
    ~Create();

signals:
    void closedWithError(int exitCode);
    void emitTypeMap(const QString& typeMap);

private slots:
    void startButtonClicked();
    void closeEvent(QCloseEvent *event);
    void sliderChanged(int value);
    void handlerInfoGameReceived(const QString& messageInfoGame);
    void handleClosed(int exitCode);
    void handlerTypeMap(const QString& typeMap);
    std::string typeWeaponToString(TypeWeapon_t type);
    QPixmap getTextureIconSoldier(QString typeSoldier);
    QPixmap getTextureMap(QString typeMap);

private:
    ClientProtocol& protocol;
    Ui::Create *ui;
    QMediaPlayer *player;
    HiloMensajes* hiloMensajes;
    QStandardItemModel model;
    int exitCode;
    std::atomic<bool> isConnected;
    std::map<QString, QPixmap>& textureIconSoldiers;
    std::map<QString, QPixmap>& textureMaps;
};

#endif // CREATE_H


