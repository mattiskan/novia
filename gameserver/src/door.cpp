//-*-c++-*-
#include "door.h"

namespace novia {
  std::shared_ptr<Room> Door::entrance() const {
    return entrance_;
  }
  
  std::shared_ptr<Room> Door::exit() const {
    return exit_;
  }

  std::string Door::description() {
    return description_;
  }


  
  Json::Value Door::serialize() const {
    using namespace Json;
    Value serialized(objectValue);

    return serialized;
  }
}
