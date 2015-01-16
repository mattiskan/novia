//-*-c++-*-
#include "response_event.h"
#include <stdexcept>


namespace novia {
  ResponseEvent::ResponseEvent() {

  }

  const Json::Value ResponseEvent::get_message() const {
    Json::Value message;
    message["msg_type"] = "event";
    
    switch(type) {
    case Type::ITEM_GAINED:
      message["type"] = "ITEM_GAINED";
      message["item"] = item->name();
      break;
    case Type::ITEM_DROPPED:
      message["type"] = "ITEM_DROPPED";
      message["item"] = item->name();
      break;
    case Type::DOOR_OPENED:
      message["type"] = "DOOR_OPENED";
      message["door"] = door->description();
      break;
    case Type::PLAYER_DIED:
      message["type"] = "PLAYER_DIED";
      message["player"] = character->name();
      break;
    case Type::PLAYER_ENTERED_ROOM:
      message["type"] = "PLAYER_ENTERED_ROOM";
      message["player"] = character->name();
      message["room"] = room->name();
      break;
    case Type::PLAYER_LEFT_ROOM:
      message["type"] = "PLAYER_LEFT_ROOM";
      message["player"] = character->name();
      message["room"] = room->name();
      break;
    }
    
    return message;
  }


}
