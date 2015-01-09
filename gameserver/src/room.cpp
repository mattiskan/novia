//-*-c++-*-
#include "room.h"

namespace novia {
  Room::Room() {
  
  }

  Json::Value Room::serialize() const {
    using namespace Json;
    Value serialized(objectValue);
    return serialized;
  }

  std::vector<std::shared_ptr<Character>>& Room::get_characters() {
    return characters_;
  }

  std::map<std::string, RoomPathEntrance> Room::get_exits() {
    std::map<std::string, RoomPathEntrance> exits;
    for (auto& name_entrance : exits_) {
      exits.insert(exits.begin(), std::pair<std::string, RoomPathEntrance>(name_entrance.first, name_entrance.second->get_room_path_entrance(*this)));
    }
    return exits;
  }
}
