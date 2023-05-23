#include "create.h"

Create::Create(std::string scenario) : scenario(scenario) {}

//creo que desp voy a necesitar mandar el id del player
int Create::send(ClientProtocol& protocol, bool& wasClosed) {
    protocol.create(scenario, wasClosed);
    return -1;
}

/*void Client::execute_commands(){
    bool was_closed = false;
    std::string command;

    if (std::cin >> command) {
        if (command == "create"){
            std::string scenario;
            std::cin >> scenario;
            protocol.create(scenario, was_closed);
            int code = protocol.receive_notification_create(was_closed);
            std::cout << "Created match: " << code << "\n";
        }
        if (command == "join"){
            int code;
            std::cin >> code;
            protocol.join(code, was_closed);
            bool exito = protocol.receive_notification_join(was_closed);
            if (exito){
                std::cout << "Joined to match: " << code << "\n";
            } else {
                std::cout << "Match does not exist: 1\n";
            }
        }
    } else {
        return;
    }

    while (std::cin >> command) {
        if (was_closed) {
            break;
        }else if (command == "broadcast"){
            std::string x;
            std::cin >> x;
            protocol.broadcast(x, was_closed);
        }else if (command == "read"){
            int n;
            std::cin >> n;
            for (int i = 0; i < n; i++){
                std::string msg = protocol.read(was_closed);
                if (was_closed){
                    break;
                }
                std::cout << "Broadcasted: " << msg << '\n';
            }
        }else if (command == "leave"){
            break;
        }else {
            continue;
        }
    }
}*/