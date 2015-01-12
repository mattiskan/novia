//-*-c++-*-
#ifndef NOVIA_CHARACTER_H
#define NOVIA_CHARACTER_H

#include <memory>
#include <vector>

#include "character_factory.h"
#include "item.h"
#include "room.h"

namespace novia {
  class Item;
  class Character;
  class Map;
  namespace CharacterFactory {
    std::shared_ptr<Character> create_character(const Json::Value&, Map&);
    std::shared_ptr<Character> create_character(const std::string&, Map&);
  }
  class Character {
  public:
    friend std::shared_ptr<Character> CharacterFactory::create_character(const Json::Value&, Map&);
    friend std::shared_ptr<Character> CharacterFactory::create_character(const std::string&, Map&);
    Character();
    int hp() const;
    virtual bool can_be_attacked(const Character& attacker) const;
    std::vector< std::shared_ptr<Item> >& items();
    std::string name() const;
    std::string description() const;
    int items_weight() const;
    int items_max_weight() const;
    std::shared_ptr<Room> current_room() const;
    void set_current_room(const std::shared_ptr<Room>& new_room);
  private:
    int hp_;
    std::string name_;
    std::vector< std::shared_ptr<Item> > items_;
    std::string description_;
    std::shared_ptr<Room> current_room_;
  };
}

#endif
