//-*-c++-*-

#ifndef NOVIA_ROOM_PATH_H
#define NOVIA_ROOM_PATH_H

#include <memory>

#include "room.h"
#include "serializable.h"

namespace novia {
  class Room;
  class Map;
  class Door : Serializable {
    friend class Map;
  public:
    std::shared_ptr<Room> entrance() const;

    std::shared_ptr<Room> exit() const;

    std::string description();
    
    Json::Value serialize() const;
  private:
    std::shared_ptr<Room> entrance_;
    std::shared_ptr<Room> exit_;
    std::string description_;
  };


}
#endif
