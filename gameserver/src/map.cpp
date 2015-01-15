#include "map.h"
#include <stdexcept>
#include <fstream>
#include <jsoncpp/json.h>


namespace novia {

  Map::Map() {
    load_map();
  }

  Json::Value Map::serialize() const {
    using namespace Json;
    Value serialized(objectValue);
    return serialized;
  }
  void Map::load_map() {
    using namespace Json;
    Value map_json;
    std::ifstream map_stream("maps/map.json", std::ifstream::in);
    if (!map_stream.good()) {
      map_stream.close();
      throw std::invalid_argument("Map file not found");
    }
    Reader json_reader;
    if (!json_reader.parse(map_stream, map_json)) {
      throw std::invalid_argument(json_reader.getFormatedErrorMessages());
    }

    map_stream.close();
    init_from_json(map_json);
  }

  void Map::init_from_json(const Json::Value& map) {
    using namespace Json;
    rooms().clear();
    characters().clear();
    items().clear();

    for (const std::string& item_id : map["items"].getMemberNames()) {
      items_.push_back(ItemFactory::create_item(map["items"][item_id]));
    }

    for (const std::string& character_name : map["characters"].getMemberNames()) {
      characters_.push_back(CharacterFactory::create_character(map["characters"][character_name], *this));
    }
    
    for (const std::string& room_name : map["rooms"].getMemberNames()) {
      const Value& room_json = map["rooms"][room_name];
      std::shared_ptr<Room> room(new Room());
      room->description_ = room_json["description"].asString();
      for (const Value& item_id_json : room_json["items"]) {
	std::shared_ptr<Item>& item = items().at(item_id_json.asInt());
	room->items_[item->name()] = item;
      }
      rooms_[room_name] = room;
    }
    

    for (const std::string& room_name : map["rooms"].getMemberNames()) {
      std::shared_ptr<Room> room(rooms()[room_name]);
      const Value& exits = map["rooms"][room_name]["exits"];
      for (const std::string& exit_name : exits.getMemberNames()) {
	Value exit = exits[exit_name];
	Door d;
	d.description_ = exit["description"].asString();
	d.entrance_ = room;
	d.exit_ = rooms()[exit["to"].asString()];
	Door::LockType locked = Door::to_lock_type(exit.get("lock", Value("unlocked")).asString());
	d.lock_type_ = locked;
	

	room->exits()[exit_name] = d;
      }
    }


    /*for (const Value& path : map["paths"]) {
      const Value& exit1 = path["exit1"];
      const Value& exit2 = path["exit2"];
      RoomPath::Entrance entrance1(rooms_.at(exit1["to"].asString()), exit1["description"].asString());
      RoomPath::Entrance entrance2(rooms_.at(exit2["to"].asString()), exit2["description"].asString());
      std::shared_ptr<RoomPath> new_path(new RoomPath(entrance1, entrance2));
      entrance1.entrance->exits_[exit1["to"].asString()] = new_path;
      entrance2.entrance->exits_[exit2["to"].asString()] = new_path;
      }*/


    
  }

  std::map<std::string, std::shared_ptr<Room>>& Map::rooms() {
    return rooms_;
  }

  std::vector<std::shared_ptr<Character>>& Map::characters() {
    return characters_;
  }

  std::vector<std::shared_ptr<Item>>& Map::items() {
    return items_;
  }


}
