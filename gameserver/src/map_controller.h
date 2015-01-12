//-*-c++-*-
#ifndef NOVIA_MAP_CONTROLLER_H
#define NOVIA_MAP_CONTROLLER_H

#include "map.h"

namespace novia {

  class MapController {
    Map map_;
  public:
    
    MapController();
    Json::Value get_serialized() const;

    void attack(const Character& attacker, const Character& victim);

    void use(const Character& user, const Item& item);
    void use(const Character& user, const Item& item, const Character& target);
    void use(const Character& user, const Item& item, const RoomPath& target);
    void use(const Character& user, const Item& item, const Item& target);

    void examine(const Character& user, const Item& item);
    void examine(const Character& user, const RoomPath& door);
    void examine(const Character& user, const Character& character);
 
    void take(const Character& user, const Item& item);

    void send_msg_to_character(const Character& character, const std:: string message);
    
    void send_msg_to_all(const std::string& message);
  };
  
}

#endif

