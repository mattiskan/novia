//-*-c++-*-
#ifndef NOVIA_MAP_CONTROLLER_H
#define NOVIA_MAP_CONTROLLER_H

#include <map>

#include "map.h"
#include "client_connection.h"

namespace novia {
  class ConnectionReceiver;

  
  class MapController {
  public:
    typedef std::shared_ptr<Character> CharacterPtr;
    typedef std::shared_ptr<Item> ItemPtr;
    typedef std::shared_ptr<Room> RoomPtr;

    MapController();
    Json::Value get_serialized() const;

    std::unique_ptr<OutMessage> attack(const CharacterPtr& attacker, const CharacterPtr& victim);

    std::unique_ptr<OutMessage> use(const CharacterPtr& user, const ItemPtr& item);
    std::unique_ptr<OutMessage> use(const CharacterPtr& user, const ItemPtr& item, CharacterPtr& target);
    std::unique_ptr<OutMessage> use(const CharacterPtr& user, const ItemPtr& item, Door& target);
    std::unique_ptr<OutMessage> use(const CharacterPtr& user, const ItemPtr& item, const ItemPtr& target);

    std::unique_ptr<OutMessage> examine(const CharacterPtr& user, const ItemPtr& item);
    std::unique_ptr<OutMessage> examine(const CharacterPtr& user, const Door& door);
    std::unique_ptr<OutMessage> examine(const CharacterPtr& user, const CharacterPtr& character);
 
    std::unique_ptr<OutMessage> take(const CharacterPtr& user, const std::string& item_name);

    std::unique_ptr<OutMessage> move(const CharacterPtr& traveler, Door& door);
    std::unique_ptr<OutMessage> teleport(const CharacterPtr& traveler, const RoomPtr& target);

    std::unique_ptr<OutMessage> info(const CharacterPtr& traveler);
    
    void add_new_player(const std::shared_ptr<ClientConnection>& conn, const std::string& name);
    bool player_exists(int user_id) const;
    CharacterPtr player(int user_id);

    void load_game();
    void save_game();
    void broadcast(std::unique_ptr<OutMessage> msg);
    void broadcast(std::unique_ptr<OutMessage> msg, const CharacterPtr& sender);
    void broadcast(std::unique_ptr<OutMessage> msg, const std::list<CharacterPtr>& exclude);
    void broadcast(std::unique_ptr<OutMessage> msg, const RoomPtr& room);
    void add_player_connection(const std::shared_ptr<ClientConnection>& conn);
    void kill_dead_players(ConnectionReceiver& cc);

    void update();
  private:

    Map map_;
    std::map<int, std::weak_ptr<ClientConnection>> player_cons_;
    std::map<int, CharacterPtr> players_;

    /*    void send_msg_to_character(const Character& character, const std:: string message);
    
	  void send_msg_to_all(const std::string& message);*/
  };
  
}

#endif

