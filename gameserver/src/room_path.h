//-*-c++-*-

#ifndef NOVIA_ROOM_PATH_H
#define NOVIA_ROOM_PATH_H

#include <memory>

#include "room.h"
#include "serializable.h"

namespace novia {
  class Room;
  class RoomPathEntrance;

  class RoomPath : Serializable {
  public:
    struct Entrance {
      Entrance(const std::shared_ptr<Room>& entrance, const std::string& description)
	: entrance(entrance),
	  description(description)
      {}
      const std::shared_ptr<Room> entrance;
      const std::string description;
    };
    
    
    RoomPath(Entrance room1, Entrance room2);
    Entrance get_entrance(const Room& entrance);
    std::shared_ptr<Room> get_exit(const Room& entrance);
    RoomPathEntrance get_room_path_entrance(const Room& entrance);
    Json::Value serialize() const override;
  private:
    Entrance room1_;
    Entrance room2_;
  };
  
  struct RoomPathEntrance {
    RoomPathEntrance(RoomPath& room_path, const std::shared_ptr<Room>& entrance)
      : entrance(entrance),
	room_path(room_path)
    {};
  private:
    std::shared_ptr<Room> entrance;
    RoomPath& room_path;
    RoomPath::Entrance get_entrance() { return room_path.get_entrance(*entrance); };
    std::shared_ptr<Room> get_exit() { return room_path.get_exit(*entrance); };
  };

}
#endif
