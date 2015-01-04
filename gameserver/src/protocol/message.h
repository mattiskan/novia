//-*-c++-*-
#ifndef NOVIA_MESSAGE_H
#define NOVIA_MESSAGE_H

#include <jsoncpp/json.h>

namespace novia {
  
  class Message {

  public:
    /*
     * Used to copy contents of messages into fields.
     *
     * Throw std::domain_error if message is invalid.
     */
    virtual void read(const Json::Value& data) = 0;


    virtual Json::Value write() const = 0;
    
    virtual bool does_modification() const = 0;
  };
}

#endif
