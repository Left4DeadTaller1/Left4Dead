#ifndef ACTION_CREATE_H_
#define ACTION_CREATE_H_

#include "action_client.h"
#include <string>

class CreateAction : public ActionClient {
   private:
    std::string namePlayer;
    TypeWeapon_t typeWeapon;
    TypeMap_t typeMap;

   public:
    CreateAction(std::string namePlayer, 
                TypeWeapon_t weaponPlayer, 
                TypeMap_t map);

    virtual std::vector<int8_t> serialize() const override;
};

#endif  //ACTION_CREATE_H_
