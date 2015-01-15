//-*-c++-*-

#ifndef NOVIA_ITEM_H
#define NOVIA_ITEM_H

#include <functional>

#include "item_factory.h"
#include "serializable.h"
#include "character.h"
#include "door.h"
#include "item.h"
#include <protocol/out_message.h>

class Character;

namespace novia {
  class Door;
  namespace ItemFactory {
    std::shared_ptr<Item> create_item(const Json::Value&);
  }
  class Item : Serializable {
    typedef std::shared_ptr<Character> CharacterPtr;
    typedef std::shared_ptr<Item> ItemPtr;
  public:
    friend std::shared_ptr<Item> ItemFactory::create_item(const Json::Value&);

    
    //Use functions
    typedef std::function<std::unique_ptr<OutMessage>(const CharacterPtr& user, CharacterPtr& target)> OnUseCharacterFn;
    typedef std::function<std::unique_ptr<OutMessage>(const CharacterPtr& user)> OnUseFn;
    typedef std::function<std::unique_ptr<OutMessage>(const CharacterPtr& user, const ItemPtr& target)> OnUseItemFn;
    typedef std::function<std::unique_ptr<OutMessage>(const CharacterPtr& user, Door& door_path)> OnUseDoor;
    
    Item();

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
