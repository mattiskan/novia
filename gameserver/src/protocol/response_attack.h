//-*-c++-*-
#ifndef NOVIA_RESPONSE_ATTACK_H
#define NOVIA_RESPONSE_ATTACK_H

#include <string>
#include <item.h>

#include "out_message.h"


namespace novia {
  
  class ResponseAttack : public OutMessage {
    int damage_;
    bool kill_;
    Character* attacker_;
    Character* victim_;
  public:

    ResponseAttack(int damage, 
		   bool was_kill,
		   Character* attacker, 
		   Character* victim 
		   );

    virtual const Json::Value get_message() const override;
    

  };
}

#endif
