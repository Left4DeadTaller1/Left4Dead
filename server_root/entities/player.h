#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>

#include "entity.h"
#include "weapon.h"

enum PlayerActionState {
    PLAYER_WALKING,    // 0
    PLAYER_RUNNING,    // 1
    PLAYER_IDLE,       // 2
    PLAYER_SHOOTING,   // 3
    PLAYER_RELOADING,  // 4
    PLAYER_ATTACKING,  // 5
    PLAYER_REVIVING,   // 6
    PLAYER_HURT,       // 7
    PLAYER_DYING,      // 8
    PLAYER_DEAD,       // 9
};

// TODO add this to action class

struct PlayerDTO : EntityDTO {
    int bullets;
    PlayerActionState actionState;
    std::string nickName;
};

class Player : public Entity {
   private:
    Weapon weapon;
    PlayerActionState actionState;
    std::string nickName;
    int knockDowns;
    std::shared_ptr<Player> revivingPlayer;

   public:
    Player(int xPosition, int yPosition, std::string idPlayer, WeaponType weapon, std::string nickName);

    void setMovementDirectionX(MovementDirectionX movementDirectionX);
    void setMovementDirectionY(MovementDirectionY movementDirectionY);

    void setActionState(PlayerActionState actionState);
    PlayerActionState getActionState();

    EntityType getType() override;
    std::shared_ptr<EntityDTO> getDto() override;
    bool isMoving() override;
    void idle() override;
    std::tuple<int, int> getDirectionsAmount();
    void takeDamage(int damage) override;
    void decreaseActionCounter() override;

    std::shared_ptr<Player> getClosestRevivablePlayer(std::vector<std::shared_ptr<Player>>& players);
    void setClosestRevivablePlayer(std::shared_ptr<Player> player);
    void setRevivalState();
    void revive();

    void decreaseATKCooldown();

    void reload();
    bool canAttack() override;
    Attack generateAttack();
    void startMoving() override;

    bool checkIfDead() override;
    void kill() override;
    bool isDead() override;
    bool isRemovable() override;
    ~Player();
};

#endif  // PLAYER_H_