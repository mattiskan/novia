//-*-c++-*-
#include "character_factory.h"
#include <algorithm>
#include <sstream>

namespace novia {
  namespace CharacterFactory {
    std::shared_ptr<Character> create_character(const std::string& character_name, Map& map) {
      using namespace Json;
      Value json(objectValue);
      json["name"] = Value(character_name);
      return create_character(json, map);
    }
    std::shared_ptr<Character> create_character(const Json::Value& character_data, Map& map) {
      std::shared_ptr<Character> character(new Character());
      std::string character_name = character_data["name"].asString();
      std::transform(character_name.begin(), character_name.end(), character_name.begin(), ::tolower);



      if (character_name == "player") {
	using namespace Json;
	character->name_ = character_data["playerName"].asString();
	std::vector<std::string> starting_items = {
	  "dagger",
	  "small_bag"
	};
	for (auto& item_name : starting_items) {
	  std::shared_ptr<Item> item = ItemFactory::create_item(item_name);
	  character->items().push_back(item);
	}
      } else if (character_name == "beggar") {
	character->name_ = "Beggar1";

      } else {
	std::stringstream msg;
	Json::StyledWriter json_writer;
	msg << "Unknown character: '" << character_name << "' json: '"<<json_writer.write(character_data) <<"'";
	throw std::runtime_error(msg.str());
      }

      for (const Json::Value& item_json : character_data["items"]) {
	std::shared_ptr<Item> item = ItemFactory::create_item(item_json);
	character->items().push_back(item);
      }

      return character;
    }
  }
}
