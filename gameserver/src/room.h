//-*-c++-*-

#ifndef NOVIA_ROOM_H
#define NOVIA_ROOM_H

#include <map>
#include <vector>
#include "serializable.h"
#include "character.h"
#include "room_path.h"

namespace novia {
  class Character;
  class RoomPathEntrance;
  class RoomPath;

  class Room : Serializable {
  
  public:
    Room();
    std::vector<std::shared_ptr<Character>>& get_characters();
    std::map<std::string, RoomPathEntrance> get_exits();
  private:
    std::vector<std::shared_ptr<Character>> characters_;
    std::map<std::string, std::shared_ptr<RoomPath>> exits_;
    Json::Value serialize() const;
  };
}


#endif
