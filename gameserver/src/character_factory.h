//-*-c++-*-
#ifndef NOVIA_CHARACTER_FACTORY_H
#define NOVIA_CHARACTER_FACTORY_H

#include <memory>
#include <jsoncpp/json.h>

#include "item.h"
#include "map.h"

namespace novia {
  class Character;
  class Map;
  namespace CharacterFactory {
    std::shared_ptr<Character> create_character(const std::string& character_name, Map& map);
    std::shared_ptr<Character> create_character(const Json::Value& character_data, Map& map);
  };
}

#endif
