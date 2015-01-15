#include "map.h"
#include <stdexcept>
#include <fstream>
#include <jsoncpp/json.h>
#include <algorithm>


namespace novia {

  Map::Map() {
    
  }


  void Map::init_from_json(const Json::Value& map) {
    using namespace Json;
    rooms().clear();
    characters().clear();
    //items().clear();

    /*for (const std::string& item_id : map["items"].getMemberNames()) {
      items_.push_back(ItemFactory::create_item(map["items"][item_id]));
      }*/

    
    for (const Value& room_json : map["rooms"]) {
      RoomPtr room(new Room());
      room->description_ = room_json["description"].asString();
      room->name_ = room_json["name"].asString();
      for (const Value& item_json : room_json["items"]) {
	ItemPtr item = ItemFactory::create_item(item_json);
	room->items_[item->name()] = item;
      }

      rooms_[room->name()] = room;
    }
    

    for (const Value& room_json : map["rooms"]) {
      RoomPtr room(rooms()[room_json["name"].asString()]);
      const Value& exits = room_json["exits"];
      for (const Json::Value& exit : exits) {
	Door d;
	d.description_ = exit["description"].asString();
	d.entrance_ = room;
	d.name_ = exit["name"].asString();
	d.exit_ = rooms()[exit["to"].asString()];
	Door::LockType locked = Door::to_lock_type(exit.get("lock", Value("unlocked")).asString());
	d.lock_type_ = locked;
	

	room->exits()[d.name()] = d;
      }
    }
    for (const Value& character_json : map["characters"]) {
      characters_.push_back(CharacterFactory::create_character(character_json, *this));
    }

  }

  std::map<std::string, Map::RoomPtr>& Map::rooms() {
    return rooms_;
  }

  const std::map<std::string, Map::RoomPtr>& Map::rooms() const {
    return rooms_;
  }


  std::vector<Map::CharacterPtr>& Map::characters() {
    return characters_;
  }

  const std::vector<Map::CharacterPtr>& Map::characters() const {
    return characters_;
  }


  Json::Value Map::serialize() const {
    Json::Value serialized;
    for (const std::pair<std::string, RoomPtr>& room_ptr : rooms()) {
      serialized["rooms"].append(room_ptr.second->serialize());
    }

    for (const CharacterPtr& char_ptr : characters()) {
      serialized["characters"].append(char_ptr->serialize());
    }
    
    return serialized;
  }

}
