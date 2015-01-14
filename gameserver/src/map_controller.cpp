#include "map_controller.h"
#include <protocol/response_examine.h>
#include <protocol/response_new_player_status.h>
#include <protocol/response_info.h>
#include <iostream>

namespace novia {
  MapController::MapController() 
    : map_()
  {
    
  }

  std::unique_ptr<OutMessage> MapController::attack(CharacterPtr& attacker, CharacterPtr& victim) {
    return std::unique_ptr<OutMessage>();
  }

  std::unique_ptr<OutMessage> MapController::use(CharacterPtr& user, Item& item) {
    if (item.on_use) {
      item.on_use(user);
    } else {
      return std::unique_ptr<OutMessage>();
    }
    return std::unique_ptr<OutMessage>();
  }
  std::unique_ptr<OutMessage> MapController::use(CharacterPtr& user, Item& item, CharacterPtr& target) {
    if (!item.on_use_character) {
      return std::unique_ptr<OutMessage>();
    }
    return item.on_use_character(user, target);
  }
  std::unique_ptr<OutMessage> MapController::use(CharacterPtr& user, Item& item, Door& target) {
    if (!item.on_use_door) {
      return std::unique_ptr<OutMessage>();
    }
    return item.on_use_door(user, target);
  }

  std::unique_ptr<OutMessage> MapController::use(CharacterPtr& user, Item& item, Item& target) {
    if (!item.on_use_item) {
      return std::unique_ptr<OutMessage>();
    }
    return item.on_use_item(user, target);
  }

  std::unique_ptr<OutMessage> MapController::examine(const CharacterPtr& user, const Item& item) {
    ResponseExamine* response = new ResponseExamine();
    response->type = ResponseExamine::ExamineType::ITEM;
    response->item = &item;
    return std::unique_ptr<OutMessage>(response);
  }

  std::unique_ptr<OutMessage> MapController::examine(const CharacterPtr& user, const Door& door) {
    ResponseExamine* response = new ResponseExamine();
    response->type = ResponseExamine::ExamineType::DOOR;
    response->door = &door;
    return std::unique_ptr<OutMessage>(response);
  }

  std::unique_ptr<OutMessage> MapController::examine(const CharacterPtr& user, const CharacterPtr& character) {
    ResponseExamine* response = new ResponseExamine();
    response->type = ResponseExamine::ExamineType::CHARACTER;
    response->character = character.get();
    return std::unique_ptr<OutMessage>(response);
  }

  std::unique_ptr<OutMessage> MapController::take(CharacterPtr& user, Item& item) {
    return std::unique_ptr<OutMessage>();
  }

  Json::Value MapController::get_serialized() const {
    return map_.serialize();
  }

  bool MapController::player_exists(int user_id) const {
    return players_.count(user_id);
  }

  MapController::CharacterPtr MapController::player(int user_id) {
    return players_[user_id];
  }

  void MapController::add_new_player(const ClientConnection& conn, const std::string& name) {
    if (player_exists(conn.user_id()))
	throw std::invalid_argument("A player with that user_id is already connected");
    using namespace Json;
    Value character(objectValue);
    character["name"] = Value("player");
    character["playerName"] = name;
    CharacterPtr new_player = CharacterFactory::create_character(character, map_);
    players_[conn.user_id()] = new_player;
    map_.rooms()["Home"]->characters().push_back(new_player);
    new_player->set_current_room(map_.rooms()["Home"]);

    ResponseNewPlayerStatus status;
    status.player = players_[conn.user_id()].get();
    status.status = ResponseNewPlayerStatus::Status::NEW_PLAYER;
    conn.send(status);
  }

  std::unique_ptr<OutMessage> MapController::move(const CharacterPtr& traveler, Door& door) {
    std::shared_ptr<Room> current_room = door.entrance();
    std::shared_ptr<Room> target_room = door.exit();
    current_room->characters().remove(traveler);
    target_room->characters().push_back(traveler);
    traveler->set_current_room(target_room);
    ResponseInfo* message = new ResponseInfo();
    message->room = target_room.get();
    return std::unique_ptr<OutMessage>(message);
  }

  std::unique_ptr<OutMessage> MapController::info(const CharacterPtr& traveler) {
    
    return std::unique_ptr<OutMessage>();
  }

  /*  void MapController::send_msg_to_character(const CharacterPtr& character, const std::string message) {
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
