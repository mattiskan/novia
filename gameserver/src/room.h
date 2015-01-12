//-*-c++-*-

#ifndef NOVIA_ROOM_H
#define NOVIA_ROOM_H

#include <map>
#include <vector>
#include "serializable.h"
#include "character.h"
#include "room_path.h"
#include "item.h"

namespace novia {
  class Character;
  class RoomPathEntrance;
  class RoomPath;
  class Map;
  class Item;

  class Room : Serializable {  
  public:

    friend class Map;

    Room();
    std::vector<std::shared_ptr<Character>>& get_characters();
    std::map<std::string, RoomPathEntrance> get_exits();
    std::map<std::string, std::shared_ptr<Item>>& items();
    static std::shared_ptr<Room> from_json(const Json::Value& json, Map& map);
    std::string name() const;
    std::string description() const;
  private:
    std::vector<std::shared_ptr<Character>> characters_;
    std::map<std::string, std::shared_ptr<RoomPath>> exits_;
    std::map<std::string, std::shared_ptr<Item>> items_;
    Json::Value serialize() const;
    std::string name_;
    std::string description_;
  };
}


#endif
