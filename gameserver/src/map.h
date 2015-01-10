//-*-c++-*-
#ifndef NOVIA_MAP_H
#define NOVIA_MAP_H
#include <vector>
#include <memory>

#include "room.h"
#include "character.h"
#include "serializable.h"

namespace novia {

  class Map : public Serializable {
  public:
    Map();
    virtual Json::Value serialize() const override;
    void load_map();
    std::vector<std::shared_ptr<Room>>& get_rooms();
    std::vector<std::shared_ptr<Character>>& get_characters();
    
  private:
    std::vector<std::shared_ptr<Room>> rooms_;
    std::vector<std::shared_ptr<Character>> characters_;
    void init_from_json(const Json::Value& map);
  };

}

#endif
