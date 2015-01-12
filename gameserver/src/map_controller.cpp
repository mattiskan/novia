#include "map_controller.h"
#include <protocol/response_examine.h>
namespace novia {
  MapController::MapController() 
    : map_()
  {
    
  }

  std::unique_ptr<OutMessage> MapController::attack(Character& attacker, Character& victim) {
    return std::unique_ptr<OutMessage>();
  }

  std::unique_ptr<OutMessage> MapController::use(Character& user, Item& item) {
    if (item.on_use) {
      item.on_use(user);
    } else {
      return std::unique_ptr<OutMessage>();
    }
    return std::unique_ptr<OutMessage>();
  }
  std::unique_ptr<OutMessage> MapController::use(Character& user, Item& item, Character& target) {
    if (!item.on_use_character) {
      return std::unique_ptr<OutMessage>();
    }
    return item.on_use_character(user, target);
  }
  std::unique_ptr<OutMessage> MapController::use(Character& user, Item& item, RoomPathEntrance& target) {
    if (!item.on_use_door) {
      return std::unique_ptr<OutMessage>();
    }
    return item.on_use_door(user, target);
  }

  std::unique_ptr<OutMessage> MapController::use(Character& user, Item& item, Item& target) {
    if (!item.on_use_item) {
      return std::unique_ptr<OutMessage>();
    }
    return item.on_use_item(user, target);
  }

  std::unique_ptr<OutMessage> MapController::examine(const Character& user, const Item& item) {
    ResponseExamine* response = new ResponseExamine();
    response->type = ResponseExamine::ExamineType::ITEM;
    response->item = &item;
    return std::unique_ptr<OutMessage>(response);
  }

  std::unique_ptr<OutMessage> MapController::examine(const Character& user, const RoomPathEntrance& door) {
    ResponseExamine* response = new ResponseExamine();
    response->type = ResponseExamine::ExamineType::DOOR;
    response->door = &door;
    return std::unique_ptr<OutMessage>(response);
  }

  std::unique_ptr<OutMessage> MapController::examine(const Character& user, const Character& character) {
    ResponseExamine* response = new ResponseExamine();
    response->type = ResponseExamine::ExamineType::CHARACTER;
    response->character = &character;
    return std::unique_ptr<OutMessage>(response);
  }

  std::unique_ptr<OutMessage> MapController::take(Character& user, Item& item) {
    return std::unique_ptr<OutMessage>();
  }

  Json::Value MapController::get_serialized() const {
    return map_.serialize();
  }


  /*  void MapController::send_msg_to_character(const Character& character, const std::string message) {
      if (!character.has_connection()) {
	throw std::exception("No connection!");
      }
      TextMessageOut json;
      json.set_message(message);
      character.client_connection()->send(json);
  }
    
  void MapController::send_msg_to_all(const std::string& message) {
    for (const std::shared_ptr<Character>& character_ptr : map.characters()) {
      if (!character_ptr->has_connection()) {
	continue;
      }
      send_msg_to_character(*character_ptr, message);
    }
    }*/

}
