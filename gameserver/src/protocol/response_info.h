//-*-c++-*-
#ifndef NOVIA_RESPONSE_INFO_H
#define NOVIA_RESPONSE_INFO_H

#include <string>
#include <item.h>

#include "out_message.h"


namespace novia {
  
  class ResponseInfo : public OutMessage {    
  public:
    const Room* room;

    ResponseInfo();

    virtual const Json::Value get_message() const override;
    

  };
}

#endif
