//-*-c++-*-
#include "door.h"
#include <stdexcept>
#include <algorithm>
namespace novia {
  const std::vector<std::string> Door::lock_type_strings {
    "unlocked",
      "small_key",
      "large_key"
  };
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
    serialized["description"] = Value(description());
    serialized["to"] = Value(exit()->name());
    serialized["lock"] = Value(to_lock_type_string(check_lock()));
    return serialized;
  }
  
  std::string Door::to_lock_type_string(LockType lt) {
    return lock_type_strings.at((std::size_t)lt);
  }
  Door::LockType Door::to_lock_type(const std::string& str) {
    return (LockType)std::distance(lock_type_strings.begin(), 
				   std::find(lock_type_strings.begin(), 
					     lock_type_strings.end(), str));
    /*if (str == "unlocked") {
      return LockType::UNLOCKED;
    } else if (str == "small_key") {
      return LockType::SMALL_KEY;
    } else if ( str == "large_key") {
      return LockType::LARGE_KEY;
      }
      throw std::out_of_range("Invalid enum for locked");*/
  }
}
