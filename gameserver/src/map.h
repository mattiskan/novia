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
    Map();
    virtual Json::Value serialize() const override;
    void load_map();
    std::map<std::string, std::shared_ptr<Room>>& rooms();
    std::vector<std::shared_ptr<Character>>& characters();
    std::vector<std::shared_ptr<Item>>& items();
  private:
    std::map<std::string, std::shared_ptr<Room>> rooms_;
    std::vector<std::shared_ptr<Character>> characters_;
    void init_from_json(const Json::Value& map);
  };

}

#endif
