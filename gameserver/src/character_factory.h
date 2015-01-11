//-*-c++-*-
#ifndef NOVIA_CHARACTER_FACTORY_H
#define NOVIA_CHARACTER_FACTORY_H

#include <map>
#include <memory>
#include <jsoncpp/json.h>

#include "item.h"

namespace novia {
  class Character;
  namespace CharacterFactory {
    std::shared_ptr<Character> create_character(const Json::Value& character_data);
  };
}

#endif
