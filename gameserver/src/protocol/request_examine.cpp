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

  int RequestExamine::target_int() const {
    return target_int_;
  }

    
    // inherited from InMessage:
  void RequestExamine::read(const Json::Value& data) {
    type_ = data["type"].asString();
    if (type() == "backpack") {
      if (!data["target"].isNull()) {
	target_int_ = data["target"].asInt();
      }
    } else {
      target_ = data["target"].asString();
    } 
  }
    

  void RequestExamine::instant_reply(const Controllers& c, const std::shared_ptr<ClientConnection>& owner) const {

  }

  void RequestExamine::on_invoke(Controllers& c, const std::shared_ptr<ClientConnection>& owner) const {
    const std::shared_ptr<Character>& char_ptr = c.map_controller.player(owner->user_id());
    const std::shared_ptr<Room>& room_ptr = char_ptr->current_room();
    if (type() == "room") {
      ResponseInfo response;
      response.room = room_ptr.get();
      owner->send(response);

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
	owner->send(ResponseInvalidCommand(ResponseInvalidCommand::Type::UNKNOWN_TARGET, msg.str()));
	return;
      }
      owner->send(response);

    } else if (type() == "item") {
      ResponseExamine response;
      response.type = ResponseExamine::ExamineType::ITEM;
      if (!room_ptr->items().count(target())) {
	std::stringstream msg;
	msg << "There is no item with the name '" << target() << "'";
	owner->send(ResponseInvalidCommand(ResponseInvalidCommand::Type::UNKNOWN_TARGET, msg.str()));
	return;
      }
      response.item = room_ptr->items()[target()].get();
      owner->send(response);

    } else if (type() == "backpack") {
      ResponseExamine response;
      response.type = ResponseExamine::ExamineType::ITEM;
      const std::shared_ptr<Character>& char_ptr = c.map_controller.player(owner->user_id());
      if (!target_int_<0 || (std::size_t)target_int_ >= char_ptr->items().size()) {
	response.type = ResponseExamine::ExamineType::BACKPACK;
	response.character = char_ptr.get();
      } else {
	response.item = char_ptr->items()[target_int_].get();
      }
      owner->send(response);

    } else if (type() == "exit") {
      ResponseExamine response;
      response.type = ResponseExamine::ExamineType::DOOR;
      
      if (!room_ptr->exits().count(target())) {
	std::stringstream msg;
	msg << "There is no exit with the name '" << target() << "'";
	owner->send(ResponseInvalidCommand(ResponseInvalidCommand::Type::UNKNOWN_TARGET, msg.str()));
	return;
      }
      response.door = &(room_ptr->exits()[target()]);

      owner->send(response);
      
    } else {
	std::stringstream msg;
	msg << "You can't examine: '"<<type()<<"'";
	owner->send(ResponseInvalidCommand(ResponseInvalidCommand::Type::INVALID_COMMAND, msg.str()));
	return;

    }
  }

}
