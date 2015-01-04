//-*-c++-*-
#include "authentification_message.h"

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

  Json::Value AuthentificationMessage::write() const {
    throw std::runtime_error("not implemented");
  }
  
  bool AuthentificationMessage::does_modification() const {
    return false;
  }
  
}
