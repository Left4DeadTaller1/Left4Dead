#include "client.h"

Client::Client(const char* hostname, const char* servname) : socket(hostname, servname),
                                                             isConnected(true) {}

void Client::processUserInput() {
    // event instancia

    while (isConnected) {
        // identificar que tipo de evento es (moverse derecha o ize, etc)

        bool was_closed = false;
        try {
            while (!was_closed) {
                // swith(tipo de evento):
                //  case moverse para arriba:
                //  send moverse para arriba
            }
        }

        catch (const LibError& e) {
            // supongo que esto no hace falta realmente porque si hubo un liberror
            // el while se interrumpio pero bueno no esta de mas
            was_closed = true;
        }
    }
}

Client::run() {
    // methods to connect to menu
    // una vez ya en partida llamas a processUserInput() y lanzas a receiver;
}