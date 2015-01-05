//-*-c++-*-
#include "authentification_message.h"

#include <iostream>
#include <stdexcept>

namespace novia {

  const std::string& AuthentificationMessage::username() const {
    return username_;
  }

  const std::string& AuthentificationMessage::password() const {
    return password_;
  }
  
  void AuthentificationMessage::read(const Json::Value& data) {
    username_ = data["username"].asString();
    password_ = data["password"].asString();
  }

  const OutMessage* AuthentificationMessage::instant_reply(const Controllers& c) const {
    
    std::cout << "recieved login from "
	      << username_ << ":" << password_
	      << std::endl;
    
  }

  const OutMessage* AuthentificationMessage::invoke_on_server_thread(Controllers& c) const {
    
  }
}

