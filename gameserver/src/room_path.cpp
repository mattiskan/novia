//-*-c++-*-
#include "room_path.h"

namespace novia {
  RoomPath::RoomPath(Entrance room1, Entrance room2)
    : room1_(room1),
      room2_(room2)
  {
  }


  std::shared_ptr<Room> RoomPath::exit(const Room& entrance) {
    return (&entrance == room1_.entrance.get()) ? room2_.entrance : room1_.entrance;
  }


  RoomPath::Entrance RoomPath::entrance(const Room& entrance) {
    return (&entrance == room1_.entrance.get()) ? room1_ : room2_;
  }

  RoomPathEntrance RoomPath::get_room_path_entrance(const Room& entrance) {
    std::shared_ptr<Room> entr = (&entrance == room1_.entrance.get()) ? room1_.entrance : room2_.entrance;
    return RoomPathEntrance(*this, entr);
  }

  Json::Value RoomPath::serialize() const {
    using namespace Json;
    Value serialized(objectValue);

    return serialized;
  }
}
