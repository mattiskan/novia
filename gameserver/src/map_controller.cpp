#include "map_controller.h"

namespace novia {
  MapController::MapController() 
    : map_()
  {
    
  }

  void MapController::attack(const Character& attacker, const Character& victim) {
    
  }

  void MapController::use(const Character& user, const Item& item) {
    if (item.on_use) {
      item.on_use(user);
    }
  }
  void MapController::use(const Character& user, const Item& item, const Character& target) {
    if (item.on_use_character) {
      item.on_use_character(user, target);
    }
  }
  void MapController::use(const Character& user, const Item& item, const RoomPathEntrance& target) {
    if (item.on_use_door) {
      item.on_use_character(user, target);
    }
  }
  void MapController::use(const Character& user, const Item& item, const Item& target) {
    if (item.on_use_item) {
      item.on_use_item(user, target);
    }
  }

  void MapController::examine(const Character& user, const Item& item) {
    
  }

  void MapController::examine(const Character& user, const RoomPath& door) {

  }

  void MapController::examine(const Character& user, const Character& character) {

  }

  void MapController::take(const Character& user, const Item& item) {

  }

  Json::Value MapController::get_serialized() const {
    return map_.serialize();
  }


  void MapController::send_msg_to_character(const Character& character, const std:: string message) {

  }
    
  void MapController::send_msg_to_all(const std::string& message) {
    for (const std::shared_ptr<Character>& character_ptr : map.characters()) {
      if (!character_ptr->has_connection()) {
	continue;
      }
      std::shared_ptr<ClientConnection>& c_conn_ptr = character_ptr->client_connection();
    }
  }

}
