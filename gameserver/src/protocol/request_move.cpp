//-*-c++-*-
#include "request_move.h"
#include "response_invalid_command.h"
#include <sstream>
#include <iostream>

namespace novia {

  const std::string& RequestMove::door() const {
    return door_;
  }

    
    // inherited from InMessage:
  void RequestMove::read(const Json::Value& data) {
    door_ = data["destination"].asString();
    std::cout << "read move" << std::endl;
  }
    

  void RequestMove::instant_reply(const Controllers& c, ClientConnection& owner) const {
    std::cout << "instant move" << std::endl;
  }

  void RequestMove::on_invoke(Controllers& c, ClientConnection& owner) const {
    std::cout << "invoke move" << std::endl;
    const std::shared_ptr<Character>& char_ptr = c.map_controller.player(owner.user_id());
    std::map<std::string, Door> exits = char_ptr->current_room()->exits();
    if (exits.count(door())) {
	Door& door_entrance = exits[door()];
	std::unique_ptr<OutMessage> message = c.map_controller.move(char_ptr, door_entrance);
	owner.send(*message);
    } else {
      std::stringstream msg;
      msg << "There is no door with the name '" << door() << "'";
      owner.send(ResponseInvalidCommand(ResponseInvalidCommand::Type::UNKNOWN_TARGET, msg.str()));
    }
  }
}
