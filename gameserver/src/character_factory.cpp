//-*-c++-*-
#include "character_factory.h"
#include <algorithm>
#include <sstream>

namespace novia {
  namespace CharacterFactory {
    
    std::shared_ptr<Character> create_character(const Json::Value& character_data) {
      std::shared_ptr<Character> character(new Character());
      std::string character_name = character_data["name"].asString();
      std::transform(character_name.begin(), character_name.end(), character_name.begin(), ::tolower);
      if (character_name == "beggar") {
	character->name_ = "Beggar1";
      } else {
	std::stringstream msg;
	Json::StyledWriter json_writer;
	msg << "Unknown character: '" << character_name << "' json: '"<<json_writer.write(character_data) <<"'";
	throw std::runtime_error(msg.str());
      }
      return character;
    }
  }
}
