//-*-c++-*-
#include "request_use.h"
#include "response_info.h"
#include "response_invalid_command.h"
#include <sstream>

namespace novia {

  const std::string& RequestUse::type() const {
    return type_;
  }

  const std::string& RequestUse::target() const {
    return target_;
  }

  int RequestUse::target_int() const {
    return target_int_;
  }

  int RequestUse::item() const {
    return item_;
  }
    
    // inherited from InMessage:
  void RequestUse::read(const Json::Value& data) {
    item_ = data["item"].asInt();
    if ( data["type"].isNull()) {
      type_ = "self";
    } else {
      type_ = data["type"].asString();
      if (type_ != "backpack") {
	target_ = data["target"].asString();;
      } else {
	target_int_ = data["target"].asInt();
      }
      
    }

  }
    

  void RequestUse::instant_reply(const Controllers& c, ClientConnection& owner) const {

  }

  void RequestUse::on_invoke(Controllers& c, ClientConnection& owner) const {
    const std::shared_ptr<Character>& char_ptr = c.map_controller.player(owner.user_id());
    const std::shared_ptr<Room>& room_ptr = char_ptr->current_room();
    if (item()<0 || (unsigned int)item() >= char_ptr->items().size()) {
	std::stringstream msg;
	msg << "You don't have an item with id: '" << item() << "'";
	owner.send(ResponseInvalidCommand(ResponseInvalidCommand::Type::UNKNOWN_TARGET, msg.str()));
	return;
    }
    std::shared_ptr<Item> item_ptr = char_ptr->items()[item()];
    

    if (type() == "character") {
      std::shared_ptr<Character> character_ptr;
      for (const std::shared_ptr<Character>& character : room_ptr->characters()) {
	if (character->name() == target()) {
	  character_ptr = character;
	  break;
	}
      }
      if (!character_ptr) {
	std::stringstream msg;
	msg << "There is no character with the name '" << target() << "'";
	owner.send(ResponseInvalidCommand(ResponseInvalidCommand::Type::UNKNOWN_TARGET, msg.str()));
	return;
      }
      std::unique_ptr<OutMessage> response = c.map_controller.use(char_ptr, item_ptr, character_ptr);
      owner.send(*response);

    } else if (type() == "item") {
      if (!room_ptr->items().count(target())) {
	std::stringstream msg;
	msg << "There is no item in the room with the name '" << target() << "'";
	owner.send(ResponseInvalidCommand(ResponseInvalidCommand::Type::UNKNOWN_TARGET, msg.str()));
	return;
      }
      std::shared_ptr<Item> item_target_ptr = room_ptr->items()[target()];
      std::unique_ptr<OutMessage> response = c.map_controller.use(char_ptr, item_ptr, item_target_ptr);
      owner.send(*response);

    } else if (type() == "backpack") {
      if (!target_int_<0 || (std::size_t)target_int_ >= char_ptr->items().size()) {
	std::stringstream msg;
	msg << "There is no item in you backpack with the id '" << target_int() << "'";
	owner.send(ResponseInvalidCommand(ResponseInvalidCommand::Type::UNKNOWN_TARGET, msg.str()));
	return;
      }
      std::shared_ptr<Item> item_target_ptr = char_ptr->items()[target_int()];
      std::unique_ptr<OutMessage> response = c.map_controller.use(char_ptr, item_ptr, item_target_ptr);
      owner.send(*response);

    } else if (type() == "door") {
      if (!room_ptr->exits().count(target())) {
	std::stringstream msg;
	msg << "There is no exit with the name: '" << target() << "'";
	owner.send(ResponseInvalidCommand(ResponseInvalidCommand::Type::UNKNOWN_TARGET, msg.str()));
	return;
      }
      Door& door = room_ptr->exits()[target()];
      std::unique_ptr<OutMessage> response = c.map_controller.use(char_ptr, item_ptr, door);
      owner.send(*response);
      
    } else {
	std::stringstream msg;
	msg << "You can't examine: '"<<type()<<"'";
	owner.send(ResponseInvalidCommand(ResponseInvalidCommand::Type::INVALID_COMMAND, msg.str()));
	return;

    }
  }

}
