//-*-c++-*-
#include "item_factory.h"
#include <algorithm>
#include <exception>
#include <sstream>
namespace novia {
  namespace ItemFactory {
    std::shared_ptr<Item> create_item(const Json::Value& item_data) {
      std::shared_ptr<Item> item(new Item());
      std::string item_name = item_data["name"].asString();
      std::transform(item_name.begin(), item_name.end(), item_name.begin(), ::tolower);
      if (item_name == "sword") {
	item->name_ = "Sword";
	item->description_ = "Normal sword";
      } else if (item_name == "dagger") {
	item->name_ = "Dagger";
	item->description_ =  "Point the the pointy end in the right direction.";
      } else {
	std::stringstream msg;
	Json::StyledWriter json_writer;
	msg << "Unknown item: '" << item_name << "' json: '"<<json_writer.write(item_data) <<"'";
	throw std::runtime_error(msg.str());
	throw std::runtime_error(msg.str());
      }
      return item;
    }
  }
}
