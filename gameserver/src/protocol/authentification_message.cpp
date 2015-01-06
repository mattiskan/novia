//-*-c++-*-
#include "authentification_message.h"
#include "confirmation_message.h"

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

  void AuthentificationMessage::instant_reply(const Controllers& c,
					      ClientConnection& owner) const {

    bool successful =
      c.user_controller.authenticate(username(), password(), owner);

    ConfirmationMessage response;
    if(successful)
      response.set_status(ConfirmationMessage::ACCEPTED);
    else
      response.set_status(ConfirmationMessage::REJECTED);

    owner.send(response.get_message());
  }

  void AuthentificationMessage::on_invoke(Controllers& c, ClientConnection& owner) const {
    // maybe broadcast new user to other players?
  }
}

