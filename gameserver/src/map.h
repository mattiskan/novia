//-*-c++-*-
#ifndef NOVIA_MAP_H
#define NOVIA_MAP_H
#include <vector>
#include <memory>

#include "item.h"
#include "room.h"
#include "character.h"
#include "serializable.h"

namespace novia {
  class Room;
  class Map : public Serializable {
  public:
    typedef std::shared_ptr<Character> CharacterPtr;
    typedef std::shared_ptr<Room> RoomPtr;
    typedef std::shared_ptr<Item> ItemPtr;

    Map();
    virtual Json::Value serialize() const override;
    std::map<std::string, RoomPtr>& rooms();
    const std::map<std::string, RoomPtr>& rooms() const;
    std::vector<CharacterPtr>& characters();
    const std::vector<CharacterPtr>& characters() const;
    std::vector<ItemPtr>& items();
    void init_from_json(const Json::Value& map);
  private:
    std::map<std::string, RoomPtr> rooms_;
    std::vector<CharacterPtr> characters_;
  };

}

#endif
