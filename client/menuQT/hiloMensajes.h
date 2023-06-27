#ifndef CLIENT_HILO_MENSAJES_H
#define CLIENT_HILO_MENSAJES_H

#include "client_protocol.h"
#include "action_client.h"
#include "liberror.h"
#include "socket.h"
#include "thread.h"
#include <atomic>
#include <QObject>

class HiloMensajes : public QObject, public Thread
{
    Q_OBJECT

private:
    ClientProtocol& protocol;
    std::string typeWeaponToString(TypeWeapon_t type);
    std::string typeMapToString(TypeMap_t typeMap);
    const QString encodeInfoGame(TypeMap_t typeMap, int amountPlayers, 
                            std::vector<infoPlayerDTO_t>& infoPlayers);

public:
    HiloMensajes(ClientProtocol& protocol);
    virtual void run() override;

signals:
    void infoGameReceived(const QString& messageInfoGame);
    void closedWithoutError(int exitCode);

};

#endif  // CLIENT_HILO_MENSAJES_H


