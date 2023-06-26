#ifndef ACTION_JOIN_H_
#define ACTION_JOIN_H_

#include "action_client.h"
#include <memory>
#include <string>

class JoinAction : public ActionClient {
   private:
    std::string namePlayer;
    int8_t code;
    TypeWeapon_t typeWeapon;

   public:
    JoinAction(std::string namePlayer, 
                std::string weaponPlayer, 
                std::string code);

    virtual std::vector<int8_t> serialize() const override;

    virtual bool isExit(void) const override;
};

#endif  // ACTION_JOIN_H_

