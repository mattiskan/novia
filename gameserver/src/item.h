//-*-c++-*-

#ifndef NOVIA_ITEM_H
#define NOVIA_ITEM_H

#include "serializable.h"
#include "character.h"
#include "room_path.h"

class Character;

namespace novia {
  struct RoomPathEntrance;
  class Item : Serializable {
  public:
  
    Item();
    virtual void on_hit(int damage, const Character& victim, const Character& attacker);
    virtual void on_attack(int damage, const Character& victim, const Character& attacker);
    virtual void on_use(const Character& user, const Character& target);
    virtual void on_use(const Character& user, const Item& target);
    virtual void on_use(const Character& user, const RoomPathEntrance& target);
    std::string name() const;
    std::string description() const;
    Json::Value serialize() const;

  private:

    std::string name_;
    std::string description_;
  };
}
#endif
