//-*-c++-*-

#ifndef NOVIA_ROOM_H
#define NOVIA_ROOM_H

#include <map>
#include <vector>
#include <list>
#include "serializable.h"
#include "character.h"
#include "door.h"
#include "item.h"

namespace novia {
  class Character;
  class Door;
  class Map;
  class Item;

  class Room : Serializable {  
  public:

    friend class Map;

    Room();
    std::list<std::shared_ptr<Character>>& characters();
    const std::list<std::shared_ptr<Character>>& characters() const;
    std::map<std::string, Door>& exits();
    const std::map<std::string, Door>& exits() const;
    std::map<std::string, std::shared_ptr<Item>>& items();
    const std::map<std::string, std::shared_ptr<Item>>& items() const;
    static std::shared_ptr<Room> from_json(const Json::Value& json, Map& map);
    std::string name() const;
    std::string description() const;
    Json::Value serialize() const;

  private:
    std::list<std::shared_ptr<Character>> characters_;
    std::map<std::string, Door> exits_;
    std::map<std::string, std::shared_ptr<Item>> items_;
    std::string name_;
    std::string description_;
  };
}


#endif
