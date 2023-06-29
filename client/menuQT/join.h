#ifndef JOIN_H
#define JOIN_H

#include <QDialog>
#include <QMediaPlayer>
#include "client/client_connection/client_protocol.h"
#include "hiloMensajes.h"
#include <QStandardItemModel>
#include <atomic>

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
    void emitTypeMap(const QString& typeMap);

private slots:
    void closeEvent(QCloseEvent *event);
    void sliderChanged(int value);
    void handlerInfoGameReceived(const QString& messageInfoGame);
    void handleClosed(int exitCode);
    void handlerTypeMap(const QString& typeMap);
    std::string typeWeaponToString(TypeWeapon_t type);
    std::string getImageMap(QString& map);
    std::string getImageSoldier(QString& weapon);

private:
    ClientProtocol& protocol;
    Ui::Join *ui;
    QMediaPlayer *player3;
    HiloMensajes* hiloMensajes;
    QStandardItemModel model;
    int exitCode;
    std::atomic<bool> isConnected;
};

#endif // JOIN_H
