//-*-c++-*-

#ifndef NOVIA_ITEM_H
#define NOVIA_ITEM_H

#include <functional>

#include "item_factory.h"
#include "serializable.h"
#include "character.h"
#include "room_path.h"
#include "item.h"

class Character;

namespace novia {
  struct RoomPathEntrance;
  namespace ItemFactory {
    std::shared_ptr<Item> create_item(const Json::Value&);
  }
  class Item : Serializable {
  public:
    friend std::shared_ptr<Item> ItemFactory::create_item(const Json::Value&);

    typedef std::function<void(int damage, const Character& victim, const Character& attacker)> OnHitFn;
    typedef std::function<int(const Character& victim, const Character& attacker)> OnAttackFn;
    typedef std::function<void(int damage, const Character& victim, const Character& attacker)> OnUseCharacterFn;
    typedef std::function<void(int damage, const Character& victim, const Character& attacker)> OnUseItemFn;
    typedef std::function<void(int damage, const Character& victim, const Character& attacker)> OnUseDoor;
    
    Item();
    OnHitFn on_hit;
    OnAttackFn on_attack;
    OnUseCharacterFn on_use_character;
    OnUseItemFn on_use_item;
    OnUseDoor on_use_door;

    std::string name() const;
    std::string description() const;
    Json::Value serialize() const;

  private:

    std::string name_;
    std::string description_;
  };
}
#endif
