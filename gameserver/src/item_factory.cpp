//-*-c++-*-
#include "item_factory.h"
#include <algorithm>
#include <exception>
#include <sstream>
namespace novia {
  namespace ItemFactory {
    std::shared_ptr<Item> create_item(const std::string& name) {
      using namespace Json;
      Value item(objectValue);
      item["name"] = Value(name);
      return create_item(item);
    }
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

      } else if (item_name == "small bag") {
	item->name_ = "Small Bag";
	item->description_ =  "Can contain a small amount of items.";
	item->weight_ = 100;
	
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
