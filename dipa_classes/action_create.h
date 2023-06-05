#ifndef ACTION_CREATE_H_
#define ACTION_CREATE_H_

#include "action_client.h"
#include <string>

typedef struct CreateDTO {
    std::string scenario;
} CreateDTO_t;

class Create : public ActionClient {
   private:
    std::string scenario;

   public:
    Create(std::string scenario);

    actionDTO_t* getDTO() const override;

    //virtual void run(Game& game) override;
};

#endif  //ACTION_CREATE_H_