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
    enum class LockType { UNLOCKED, SMALL_KEY, LARGE_KEY };
    static LockType to_lock_type(const std::string& str);
    std::shared_ptr<Room> entrance() const;

    std::shared_ptr<Room> exit() const;

    const std::string& description() const;
    
    Json::Value serialize() const;
    
    LockType check_lock() const;
    
    void unlock();
  private:
    std::shared_ptr<Room> entrance_;
    std::shared_ptr<Room> exit_;
    std::string description_;
    LockType lock_type_;
  };


}
#endif
