//-*-c++-*-
#include "character.h"

namespace novia {
  Character::Character()
    : update([](MapController& mapcontroller){})
  {

  }

  int Character::hp() const {
    return hp_;
  }

  bool Character::can_be_attacked(const Character& attacker) const {
    return true;
  }

  const std::vector<std::shared_ptr<Item>>& Character::items() const {
    return items_;
  }

  std::vector<std::shared_ptr<Item>>& Character::items() {
    return items_;
  }
  
  std::string Character::name() const {
    return name_;
  }
  std::string Character::description() const {
    return description_;
  }
  
  const std::string& Character::type() const {
    return type_;
  }

  int Character::items_weight() const {
    int total_weight=0;
    for (const std::shared_ptr<Item>& item_ptr : items_) {
      total_weight += item_ptr->weight();
    }
    return total_weight;
  }

  int Character::items_max_weight() const {
    int total_max_weight = 0;
    for (const std::shared_ptr<Item>& item_ptr : items_) {
      total_max_weight += item_ptr->store_weight();
    }
    return total_max_weight;
  }
  
  void Character::set_current_room(const std::shared_ptr<Room>& new_room) {
    current_room_ = new_room;
  }

  std::shared_ptr<Room> Character::current_room() const {
    return current_room_;
  }

  Json::Value Character::serialize() const {
    using namespace Json;
    Value serialized(objectValue);
    serialized["current_room"] = current_room()->name();
    serialized["name"] = name();
    serialized["type"] = type();
    serialized["hp"] = hp();
    Value& items_json = serialized["items"] = arrayValue;
    for (const std::shared_ptr<Item>& item : items()) {
      items_json.append(item->serialize());
    }

    return serialized;
  }

  void Character::attack(const Character& attacker) {
    hp_ -= std::max(0, attacker.damage());
  }

  bool Character::is_dead() const {
    return hp_ <= 0;
  }

 int Character::damage() const {
    int dmg = 1;
    for(const auto& item_ptr : items()){
      if(item_ptr->name() == "sword") // because fuck logic
        dmg *= 2;
    }
    return dmg;
  }

  const std::weak_ptr<ClientConnection>& Character::connection() const {
    return conn_;
  }

  std::weak_ptr<ClientConnection>& Character::connection() {
    return conn_;
  }

}
