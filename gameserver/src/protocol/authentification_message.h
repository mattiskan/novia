//-*-c++-*-
#ifndef NOVIA_AUTHENTIFICATION_MESSAGE_H
#define NOVIA_AUTHENTIFICATION_MESSAGE_H

#include "in_message.h"

namespace novia {

  class AuthentificationMessage : public InMessage {
    std::string username_;
    std::string password_;
    
  public:
    const std::string& username() const;
    const std::string& password() const;

    
    // inherited from InMessage:
    virtual void read(const Json::Value& data) override;
    

    virtual const OutMessage* instant_reply(const Controllers& c) const override;

    virtual const OutMessage* invoke_on_server_thread(Controllers& c) const override;
  };
}

#endif
