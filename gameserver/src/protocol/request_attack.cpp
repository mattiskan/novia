//-*-c++-*-
#include "request_attack.h"
#include "response_invalid_command.h"
#include <sstream>
#include <iostream>

namespace novia {

  const std::string& RequestAttack::target() const {
    return target_;
  }
    
    // inherited from InMessage:
  void RequestAttack::read(const Json::Value& data) {
    target_ = data["target"].asString();
  }
    

  void RequestAttack::instant_reply(const Controllers& c, ClientConnection& owner) const {

  }

  void RequestAttack::on_invoke(Controllers& c, ClientConnection& owner) const {
    const std::shared_ptr<Character>& char_ptr = c.map_controller.player(owner.user_id());
    std::shared_ptr<Character> char_target_ptr;
    for (const std::shared_ptr<Character>& room_char_ptr : char_ptr->current_room()->characters()) {
      if (room_char_ptr->name() == target()) {
	char_target_ptr = room_char_ptr;
	break;
      }
    }
    if (!char_target_ptr) {
      std::stringstream error_msg;
      error_msg << "There is no character in your room with the name: " << target();
      ResponseInvalidCommand response = ResponseInvalidCommand(ResponseInvalidCommand::Type::UNKNOWN_TARGET, error_msg.str());
      owner.send(response);
      return;
    }
    std::unique_ptr<OutMessage> msg = c.map_controller.attack(char_ptr, char_target_ptr);
    owner.send(*msg);
  }
}
