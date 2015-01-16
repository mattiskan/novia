//-*-c++-*-
#ifndef NOVIA_CHARACTER_H
#define NOVIA_CHARACTER_H

#include <memory>
#include <vector>

#include "character_factory.h"
#include "item.h"
#include "room.h"
#include "serializable.h"
#include "client_connection.h"

namespace novia {
  class Item;
  class Character;
  class Map;
  class MapController;
  namespace CharacterFactory {
    std::shared_ptr<Character> create_character(const Json::Value&, Map&);
    std::shared_ptr<Character> create_character(const std::string&, Map&);
  }
  class Character : Serializable {
  public:
    typedef std::shared_ptr<Character> CharacterPtr;
    typedef std::function<void(int damage, CharacterPtr& victim, CharacterPtr& attacker)> OnHitFn;
    typedef std::function<int(CharacterPtr& victim, CharacterPtr& attacker)> OnAttackFn;
    typedef std::function<void(MapController&)> OnUpdateFn; 

    friend class Map;
    friend CharacterPtr CharacterFactory::create_character(const Json::Value&, Map&);
    friend CharacterPtr CharacterFactory::create_character(const std::string&, Map&);
    Character();
    int hp() const;
    bool is_dead() const;
    int damage() const;
    std::string name() const;
    std::string description() const;
    int items_weight() const;
    int items_max_weight() const;
    std::shared_ptr<Room> current_room() const;

    std::vector< std::shared_ptr<Item> >& items();
    const std::vector< std::shared_ptr<Item> >& items() const;

    virtual bool can_be_attacked(const Character& attacker) const;
    virtual void attack(const Character& attacker);

    OnUpdateFn update;
    
    void set_current_room(const std::shared_ptr<Room>& new_room);
    Json::Value serialize() const;
    const std::string& type() const;
    const std::weak_ptr<ClientConnection>& connection() const;
    std::weak_ptr<ClientConnection>& connection();
  private:
    std::weak_ptr<ClientConnection> conn_;
    int hp_;
    std::string name_;
    std::vector< std::shared_ptr<Item> > items_;
    std::string description_;
    std::shared_ptr<Room> current_room_;
    std::string type_;
  };
}

#endif
