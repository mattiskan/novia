//-*-c++-*-
#include "room_path.h"

namespace novia {
  RoomPath::RoomPath(Entrance room1, Entrance room2)
    : room1_(room1),
      room2_(room2)
  {
  }


  std::shared_ptr<Room> RoomPath::get_exit(const Room& entrance) {
    return (&entrance == room1_.entrance.get()) ? room2_.entrance : room1_.entrance;
  }


  RoomPath::Entrance RoomPath::get_entrance(const Room& entrance) {
    return (&entrance == room1_.entrance.get()) ? room1_ : room2_;
  }

  RoomPathEntrance RoomPath::get_room_path_entrance(const Room& entrance) {
    std::shared_ptr<Room> entr = (&entrance == room1_.entrance.get()) ? room1_.entrance : room2_.entrance;
    return RoomPathEntrance(*this, entr);
  }
}
