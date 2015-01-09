//-*-c++-*-
#ifndef NOVIA_CHARACTER_H
#define NOVIA_CHARACTER_H

#include <memory>
#include <vector>

#include "item.h"

namespace novia {
  class Item;

  class Character {
  public:
    Character();
    int hp() const;
    virtual bool can_be_attacked(const Character& attacker) const;
    std::vector< std::shared_ptr<Item> >& get_items();
  private:
    int hp_;
    std::vector< std::shared_ptr<Item> > items_;
  };
}

#endif
