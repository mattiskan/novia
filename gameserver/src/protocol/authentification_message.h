//-*-c++-*-
#ifndef NOVIA_AUTHENTIFICATION_MESSAGE_H
#define NOVIA_AUTHENTIFICATION_MESSAGE_H

#include "message.h"

namespace novia {

  class AuthentificationMessage : public Message {
    std::string username_;
    std::string password_;
    
  public:

    const std::string& username() const;
    const std::string& password() const;

    
    // inherited from InMessage:
    virtual void read(const Json::Value& data) override;

    virtual Json::Value write() const override;
    
    virtual bool does_modification() const override;
  };
}

#endif
