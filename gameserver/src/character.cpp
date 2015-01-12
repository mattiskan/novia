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
  
  std::string Character::name() const {
    return name_;
  }

  bool Character::has_connection() const {
    return client_connection.expired();
  }
  std::weak_ptr<ClientConnection>& client_connection() const {
    return client_connection_;
  }


}
