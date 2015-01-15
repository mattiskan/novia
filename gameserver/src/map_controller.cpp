#include "map_controller.h"
#include <protocol/response_examine.h>
#include <protocol/response_new_player_status.h>
#include <protocol/response_info.h>
#include <protocol/response_invalid_command.h>
#include <protocol/response_event.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <jsoncpp/json.h>
#include <algorithm>

namespace novia {
  MapController::MapController() 
    : map_()
  {
    load_game();
  }

  std::unique_ptr<OutMessage> MapController::attack(const CharacterPtr& attacker, const CharacterPtr& victim) {
    return std::unique_ptr<OutMessage>();
  }

  std::unique_ptr<OutMessage> MapController::use(const CharacterPtr& user, const ItemPtr& item) {
    if (!item->on_use) {
      std::stringstream error_message;
      error_message << "The item is not usable without a target";
      return std::unique_ptr<OutMessage>(new ResponseInvalidCommand(ResponseInvalidCommand::Type::NOT_USABLE, 
								    error_message.str()));
    }
    return item->on_use(user);
  }
  std::unique_ptr<OutMessage> MapController::use(const CharacterPtr& user, const ItemPtr& item, CharacterPtr& target) {
    if (!item->on_use_character) {
      std::stringstream error_message;
      error_message << "The item is not usable on character: '" << target->name() << "'";
      return std::unique_ptr<OutMessage>(new ResponseInvalidCommand(ResponseInvalidCommand::Type::NOT_USABLE, 
								    error_message.str()));
    }
    return item->on_use_character(user, target);
  }
  std::unique_ptr<OutMessage> MapController::use(const CharacterPtr& user, const ItemPtr& item, Door& target) {
    if (!item->on_use_door) {
      std::stringstream error_message;
      error_message << "The item is not usable on the door: '" << target.description() << "'";
      return std::unique_ptr<OutMessage>(new ResponseInvalidCommand(ResponseInvalidCommand::Type::NOT_USABLE, 
								    error_message.str()));
    }
    return item->on_use_door(user, target);
  }

  std::unique_ptr<OutMessage> MapController::use(const CharacterPtr& user, const ItemPtr& item, const ItemPtr& target) {
    if (!item->on_use_item) {
      std::stringstream error_message;
      error_message << item->name() <<" is not usable on the item: '" << target->name() << "'";
      return std::unique_ptr<OutMessage>(new ResponseInvalidCommand(ResponseInvalidCommand::Type::NOT_USABLE, 
								    error_message.str()));
    }
    return item->on_use_item(user, target);
  }

  std::unique_ptr<OutMessage> MapController::examine(const CharacterPtr& user, const ItemPtr& item) {
    ResponseExamine* response = new ResponseExamine();
    response->type = ResponseExamine::ExamineType::ITEM;
    response->item = item.get();
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

  std::unique_ptr<OutMessage> MapController::take(const CharacterPtr& user, const std::string& item_name) {
    OutMessage* msg;
    const RoomPtr& room_ptr = user->current_room();
    if (room_ptr->items().count(item_name)) {
      std::shared_ptr<Item> item_ptr = room_ptr->items().at(item_name);
      user->items().push_back(item_ptr);
      room_ptr->items().erase(room_ptr->items().find(item_name));
      ResponseEvent* response  = new ResponseEvent();
      response->type = ResponseEvent::Type::ITEM_GAINED;
      response->item = item_ptr.get();
      msg = response;
    } else {
      std::stringstream error_msg;
      error_msg << "There is no item with the name '" << item_name << "'";
      msg = new ResponseInvalidCommand(ResponseInvalidCommand::Type::UNKNOWN_TARGET, error_msg.str());
    }
    return std::unique_ptr<OutMessage>(msg);
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
    save_game();
    RoomPtr current_room = door.entrance();
    RoomPtr target_room = door.exit();
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

  void MapController::load_game() {
    using namespace Json;
    Value game_json;
    std::ifstream map_stream("maps/map.json", std::ifstream::in);
    if (!map_stream.good()) {
      map_stream.close();
      throw std::invalid_argument("Map file not found");
    }
    Reader json_reader;
    if (!json_reader.parse(map_stream, game_json)) {
      throw std::invalid_argument(json_reader.getFormatedErrorMessages());
    }

    map_stream.close();
    map_.init_from_json(game_json["map"]);
    for (const Value& client_json : game_json["clients"]) {
      players_[client_json["user_id"].asInt()] = 
	       *std::find_if(map_.characters().begin(), 
			     map_.characters().end(), [&](const CharacterPtr& char_ptr) {
	  return char_ptr->name() == client_json["name"].asString();
	});
    }
  }

  void MapController::save_game() {
    using namespace Json;
    Value game_json;
    for (const std::pair<int, CharacterPtr>& char_pair : players_) {
      Value client;
      client["user_id"] = char_pair.first;
      client["name"] = char_pair.second->name();
      game_json["clients"].append(client);
    }
    game_json["map"] = map_.serialize();
    StyledWriter json_writer;
    std::ofstream out("maps/map2.json");
    out << json_writer.write(game_json);
    out.close();
  }


}
