//-*-c++-*-
#ifndef NOVIA_RESPONSE_MOVE_H
#define NOVIA_RESPONSE_MOVE_H

#include <string>
#include <character.h>
#include <room.h>

#include "out_message.h"


namespace novia {
  
  class ResponseMove : public OutMessage {    
  public:
    const Room* entrance;
    const Room* exit;
    const Character* character;

    ResponseMove();

    virtual const Json::Value get_message() const override;
    

  };
}

#endif
