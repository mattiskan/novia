//-*-c++-*-
#include "item.h"

namespace novia {
  Item::Item() {

  }

  std::string Item::name() const {
    return name_;
  }

  std::string Item::description() const {
    return description_;
  }

  Json::Value Item::serialize() const {
    using namespace Json;
    Value serialized(objectValue);

    return serialized;
  }

  void Item::on_hit(int damage, const Character& victim, const Character& attacker) {

  }
  void Item::on_attack(int damage, const Character& victim, const Character& attacker) {

  }
  void Item::on_use(const Character& user, const Character& target) {

  }
  void Item::on_use(const Character& user, const Item& target) {

  }
  void Item::on_use(const Character& user, const RoomPathEntrance& target) {

  }
}
