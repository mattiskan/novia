//-*-c++-*-
#include "response_attack.h"
#include <item.h>
#include <character.h>
#include <door.h>

namespace novia {
  ResponseAttack::ResponseAttack(int damage, bool was_kill)
    : damage_(damage),
      kill_(was_kill)
  {
    
  }

  const Json::Value ResponseAttack::get_message() const {
    Json::Value message;
    
    message["msg_type"] = "attack";
    message["damage"] = damage_;
    message["killed"] = kill_;

    return message;
  }


}
