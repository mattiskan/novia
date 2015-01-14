//-*-c++-*-
#ifndef NOVIA_MAP_CONTROLLER_H
#define NOVIA_MAP_CONTROLLER_H

#include <map>

#include "map.h"
#include "client_connection.h"
namespace novia {

  class MapController {
  public:
    typedef std::shared_ptr<Character> CharacterPtr;
    MapController();
    Json::Value get_serialized() const;

    std::unique_ptr<OutMessage> attack(CharacterPtr& attacker, CharacterPtr& victim);

    std::unique_ptr<OutMessage> use(CharacterPtr& user, Item& item);
    std::unique_ptr<OutMessage> use(CharacterPtr& user, Item& item, CharacterPtr& target);
    std::unique_ptr<OutMessage> use(CharacterPtr& user, Item& item, Door& target);
    std::unique_ptr<OutMessage> use(CharacterPtr& user, Item& item, Item& target);

    std::unique_ptr<OutMessage> examine(const CharacterPtr& user, const Item& item);
    std::unique_ptr<OutMessage> examine(const CharacterPtr& user, const Door& door);
    std::unique_ptr<OutMessage> examine(const CharacterPtr& user, const CharacterPtr& character);
 
    std::unique_ptr<OutMessage> take(CharacterPtr& user, Item& item);

    std::unique_ptr<OutMessage> move(const CharacterPtr& traveler, Door& door);

    std::unique_ptr<OutMessage> info(const CharacterPtr& traveler);
    
    void add_new_player(const ClientConnection& conn, const std::string& name);
    bool player_exists(int user_id) const;
    CharacterPtr player(int user_id);



  private:

    Map map_;
    std::map<int, std::shared_ptr<Character>> players_;

    /*    void send_msg_to_character(const Character& character, const std:: string message);
    
	  void send_msg_to_all(const std::string& message);*/
  };
  
}

#endif

