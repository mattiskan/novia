//-*-c++-*-
#include "request_examine.h"
#include "response_examine.h"
#include "response_info.h"
#include "response_invalid_command.h"
#include <sstream>

namespace novia {

  const std::string& RequestExamine::type() const {
    return type_;
  }

  const std::string& RequestExamine::target() const {
    return target_;
  }

    
    // inherited from InMessage:
  void RequestExamine::read(const Json::Value& data) {
    type_ = data["type"].asString();
    if (type() == "room") {
      target_ = data["target"].asString();
    }
  }
    

  void RequestExamine::instant_reply(const Controllers& c, ClientConnection& owner) const {

  }

  void RequestExamine::on_invoke(Controllers& c, ClientConnection& owner) const {
    const std::shared_ptr<Character>& char_ptr = c.map_controller.player(owner.user_id());
    const std::shared_ptr<Room>& room_ptr = char_ptr->current_room();
    if (type() == "room") {
      ResponseInfo response;
      response.room = room_ptr.get();
      owner.send(response);
    } else if (type() == "character") {
      ResponseExamine response;
      response.type = ResponseExamine::ExamineType::CHARACTER;
      for (const std::shared_ptr<Character>& character : room_ptr->characters()) {
	if (character->name() == target()) {
	  response.character = character.get();
	  break;
	}
      }
      if (response.character == nullptr) {
	std::stringstream msg;
	msg << "There is no character with the name '" << target() << "'";
	owner.send(ResponseInvalidCommand(ResponseInvalidCommand::Type::UNKNOWN_TARGET, msg.str()));
	return;
      }
      owner.send(response);
    } else if (type() == "item") {
      ResponseExamine response;
      response.type = ResponseExamine::ExamineType::ITEM;
      if (!room_ptr->items().count(target())) {
	std::stringstream msg;
	msg << "There is no item with the name '" << target() << "'";
	owner.send(ResponseInvalidCommand(ResponseInvalidCommand::Type::UNKNOWN_TARGET, msg.str()));
	return;
      }
      response.item = room_ptr->items()[target()].get();
      owner.send(response);
    }
  }

}
