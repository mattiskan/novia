//-*-c++-*-
#include "character.h"

namespace novia {
  Character::Character() {

  }

  int Character::hp() const {
    return hp_;
  }

  bool Character::can_be_attacked(const Character& attacker) const {
    return false;
  }

  std::vector<std::shared_ptr<Item>>& Character::get_items() {
    return items_;
  }
}
