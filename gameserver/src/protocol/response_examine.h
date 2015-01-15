//-*-c++-*-
#ifndef NOVIA_RESPONSE_EXAMINE_H
#define NOVIA_RESPONSE_EXAMINE_H

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
      DOOR,
      BACKPACK
    };
    
    ExamineType type;
    const Item* item;
    const Character* character;
    const Room* room;
    const Door* door;

    ResponseExamine();

    virtual const Json::Value get_message() const override;
    

  };
}

#endif
