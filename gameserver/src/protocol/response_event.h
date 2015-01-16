//-*-c++-*-
#ifndef NOVIA_RESPONSE_MOVE_H
#define NOVIA_RESPONSE_MOVE_H

#include <string>
#include <character.h>
#include <room.h>
#include <item.h>

#include "out_message.h"


namespace novia {
  
  class ResponseEvent : public OutMessage {    
  public:
    enum class Type { ITEM_GAINED, ITEM_DROPPED, DOOR_OPENED, PLAYER_DIED, PLAYER_ENTERED_ROOM, PLAYER_LEFT_ROOM };
    const Character* character;
    const Item* item;
    const Door* door;
    const Room* room;
    Type type;
    ResponseEvent();

    virtual const Json::Value get_message() const override;
    

  };
}

#endif
