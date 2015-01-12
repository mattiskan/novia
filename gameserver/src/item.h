//-*-c++-*-

#ifndef NOVIA_ITEM_H
#define NOVIA_ITEM_H

#include <functional>

#include "item_factory.h"
#include "serializable.h"
#include "character.h"
#include "room_path.h"
#include "item.h"
#include <protocol/out_message.h>

class Character;

namespace novia {
  struct RoomPathEntrance;
  namespace ItemFactory {
    std::shared_ptr<Item> create_item(const Json::Value&);
  }
  class Item : Serializable {
  public:
    friend std::shared_ptr<Item> ItemFactory::create_item(const Json::Value&);

    typedef std::function<void(int damage, Character& victim, Character& attacker)> OnHitFn;
    typedef std::function<int(Character& victim, Character& attacker)> OnAttackFn;
    
    //Use functions
    typedef std::function<std::unique_ptr<OutMessage>(Character& user, Character& target)> OnUseCharacterFn;
    typedef std::function<std::unique_ptr<OutMessage>(Character& user)> OnUseFn;
    typedef std::function<std::unique_ptr<OutMessage>(Character& user, Item& target)> OnUseItemFn;
    typedef std::function<std::unique_ptr<OutMessage>(Character& user, RoomPathEntrance& door_path)> OnUseDoor;
    
    Item();
    OnHitFn on_hit;
    OnAttackFn on_attack;

    OnUseCharacterFn on_use_character;
    OnUseItemFn on_use_item;
    OnUseFn on_use;
    OnUseDoor on_use_door;

    std::string name() const;
    std::string description() const;
    //Uses this amount of weight
    int weight() const;
    //Can store this amount of weight
    int store_weight() const;
    Json::Value serialize() const;
  private:

    std::string name_;
    std::string description_;
    int weight_;
    int store_weight_;
  };
}
#endif
