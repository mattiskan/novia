//-*-c++-*-
#include "request_take.h"
#include "response_invalid_command.h"
#include <sstream>
#include <iostream>

namespace novia {

  const std::string& RequestTake::target() const {
    return target_;
  }

    
    // inherited from InMessage:
  void RequestTake::read(const Json::Value& data) {
    target_ = data["item"].asString();
  }
    

  void RequestTake::instant_reply(const Controllers& c, ClientConnection& owner) const {

  }

  void RequestTake::on_invoke(Controllers& c, ClientConnection& owner) const {
    const std::shared_ptr<Character>& char_ptr = c.map_controller.player(owner.user_id());
    std::unique_ptr<OutMessage> msg = c.map_controller.take(char_ptr, target());
    owner.send(*msg);
  }
}
