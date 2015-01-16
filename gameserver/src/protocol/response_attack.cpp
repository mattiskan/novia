//-*-c++-*-
#include "response_attack.h"
#include <item.h>
#include <character.h>
#include <door.h>

namespace novia {
  ResponseAttack::ResponseAttack(int damage, bool was_kill, Character* attacker, Character* victim)
    : damage_(damage),
      kill_(was_kill),
      attacker_(attacker),
      victim_(victim)
  {
    
  }

  const Json::Value ResponseAttack::get_message() const {
    Json::Value message;
    
    message["msg_type"] = "attack";
    message["damage"] = damage_;
    message["killed"] = kill_;
    message["attacker"] = attacker_->name();
    message["victim"] = victim_->name();
    

    return message;
  }


}
