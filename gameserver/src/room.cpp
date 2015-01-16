//-*-c++-*-
#include "room.h"

namespace novia {
  Room::Room() {
  
  }

  Json::Value Room::serialize() const {
    using namespace Json;
    Value serialized;
    for (const std::pair<std::string, std::shared_ptr<Item>>& item_pair : items()) {
      serialized["items"].append(item_pair.second->serialize());      
    }
    
    for (const std::pair<std::string, Door>& door_pair : exits()) {
      serialized["exits"].append(door_pair.second.serialize());
    }
    serialized["description"] = description();
    serialized["name"] = name();
    return serialized;
  }

  std::list<std::shared_ptr<Character>>& Room::characters() {
    return characters_;
  }

  const std::list<std::shared_ptr<Character>>& Room::characters() const {
    return characters_;
  }

  std::map<std::string, Door>& Room::exits() {
    return exits_;
  }

  const std::map<std::string, Door>& Room::exits() const {
    return exits_;
  }

  std::map<std::string, std::shared_ptr<Item>>& Room::items() {
    return items_;
  }

  const std::map<std::string, std::shared_ptr<Item>>& Room::items() const {
    return items_;
  }



  std::shared_ptr<Room> Room::from_json(const Json::Value& json, Map& map) {
    std::shared_ptr<Room> new_room(new Room());
    

    return new_room;
  }

  std::string Room::name() const {
    return name_;
  }

  std::string Room::description() const {
    return description_;
  }
  
}
