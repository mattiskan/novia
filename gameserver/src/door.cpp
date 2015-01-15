//-*-c++-*-
#include "door.h"
#include <stdexcept>
namespace novia {
  std::shared_ptr<Room> Door::entrance() const {
    return entrance_;
  }
  
  std::shared_ptr<Room> Door::exit() const {
    return exit_;
  }

  const std::string& Door::description() const {
    return description_;
  }

  Door::LockType Door::check_lock() const {
    return lock_type_;
  }

  void Door::unlock() {
    lock_type_ = LockType::UNLOCKED;
  }
  
  Json::Value Door::serialize() const {
    using namespace Json;
    Value serialized(objectValue);

    return serialized;
  }

  Door::LockType Door::to_lock_type(const std::string& str) {
    if (str == "unlocked") {
      return LockType::UNLOCKED;
    } else if (str == "small_key") {
      return LockType::SMALL_KEY;
    } else if ( str == "large_key") {
      return LockType::LARGE_KEY;
    }
    throw std::out_of_range("Invalid enum for locked");
  }
}
