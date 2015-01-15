//-*-c++-*-
#ifndef NOVIA_AUTHENTIFICATION_MESSAGE_H
#define NOVIA_AUTHENTIFICATION_MESSAGE_H

#include "in_message.h"

namespace novia {

  class AuthentificationMessage : public InMessage {
    std::string username_;
    std::string password_;
    bool authed_;
  public:
    const std::string& username() const;
    const std::string& password() const;
    bool authenticated() const;
    
    // inherited from InMessage:
    virtual void read(const Json::Value& data) override;
    

    virtual void instant_reply(const Controllers& c,
			       ClientConnection& owner) const override;

    virtual void on_invoke(Controllers& c,
			   ClientConnection& owner) const override;
  };
}

#endif
