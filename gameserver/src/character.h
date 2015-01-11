//-*-c++-*-
#ifndef NOVIA_CHARACTER_H
#define NOVIA_CHARACTER_H

#include <memory>
#include <vector>

#include "character_factory.h"
#include "item.h"

namespace novia {
  class Item;
  class Character;
  namespace CharacterFactory {
    std::shared_ptr<Character> create_character(const Json::Value&);
  }
  class Character {
  public:
    friend std::shared_ptr<Character> CharacterFactory::create_character(const Json::Value&);
    Character();
    int hp() const;
    virtual bool can_be_attacked(const Character& attacker) const;
    std::vector< std::shared_ptr<Item> >& get_items();
    std::string name() const;
  private:
    int hp_;
    std::string name_;
    std::vector< std::shared_ptr<Item> > items_;
  };
}

#endif
