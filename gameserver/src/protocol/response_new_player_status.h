//-*-c++-*-
#ifndef NOVIA_RESPONSE_NEW_PLAYER_STATUS_H
#define NOVIA_RESPONSE_NEW_PLAYER_STATUS_H

#include <string>
#include <item.h>

#include "out_message.h"


namespace novia {
  
  class ResponseNewPlayerStatus : public OutMessage {    
  public:
    enum class Status { NEW_PLAYER, CONNECTED, DISCONNECTED };

    ResponseNewPlayerStatus();

    virtual const Json::Value get_message() const override;
    
    Status status;
    const Character* player;

  };
}

#endif
