#ifndef ACTION_JOIN_H_
#define ACTION_JOIN_H_

#include "action_client.h"
#include <memory>

typedef struct JoinDTO {
    int code;
} JoinDTO_t;

class Join : public ActionClient {
   private:
    int code;

   public:
    Join(int code);

    virtual actionDTO_t* getDTO() const override;

    //virtual void run(Game& game) override;
};

#endif  // ACTION_JOIN_H_