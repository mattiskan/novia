//-*-c++-*-
#ifndef NOVIA_OUT_EXAMINE_H
#define NOVIA_OUT_EXAMINE_H

#include <string>
#include <item.h>

#include "out_message.h"


namespace novia {
  
  class ResponseExamine : public OutMessage {    
  public:
    enum class ExamineType {
      ITEM,
      CHARACTER,
      ROOM,
      DOOR
    };
    
    ExamineType type;
    const Item* item;
    const Character* character;
    const Room* room;
    const RoomPathEntrance* door;

    ResponseExamine();

    virtual const Json::Value get_message() const override;
    

  };
}

#endif
