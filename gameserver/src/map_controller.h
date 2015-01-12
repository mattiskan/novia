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

    std::unique_ptr<OutMessage> attack(Character& attacker, Character& victim);

    std::unique_ptr<OutMessage> use(Character& user, Item& item);
    std::unique_ptr<OutMessage> use(Character& user, Item& item, Character& target);
    std::unique_ptr<OutMessage> use(Character& user, Item& item, RoomPathEntrance& target);
    std::unique_ptr<OutMessage> use(Character& user, Item& item, Item& target);

    std::unique_ptr<OutMessage> examine(const Character& user, const Item& item);
    std::unique_ptr<OutMessage> examine(const Character& user, const RoomPathEntrance& door);
    std::unique_ptr<OutMessage> examine(const Character& user, const Character& character);
 
    std::unique_ptr<OutMessage> take(Character& user, Item& item);

    /*    void send_msg_to_character(const Character& character, const std:: string message);
    
	  void send_msg_to_all(const std::string& message);*/
  };
  
}

#endif

