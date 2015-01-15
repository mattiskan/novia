//-*-c++-*-
#include "item_factory.h"
#include <algorithm>
#include <exception>
#include <sstream>
#include <protocol/response_invalid_command.h>
namespace novia {
  namespace ItemFactory {
    typedef std::shared_ptr<Character> CharacterPtr;
    typedef std::shared_ptr<Item> ItemPtr;
    typedef std::shared_ptr<Room> RoomPtr;
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
	item->name_ = "sword";
	item->description_ = "Normal sword";

      } else if (item_name == "dagger") {
	item->name_ = "dagger";
	item->description_ =  "Point the the pointy end in the right direction.";

      } else if (item_name == "small_bag") {
	item->name_ = "small_bag";
	item->description_ =  "Can contain a small amount of items.";
	item->weight_ = 100;
      } else if (item_name == "small_key") {
	item->name_ = "small_key";
	item->description_ = "Can open some doors and are then destroyed in the process.";
	item->weight_ = 0;
	item->on_use_door = [=](const CharacterPtr& user, Door& door) {
	  OutMessage* out_msg;
	  if (door.check_lock() == Door::LockType::SMALL_KEY) {
	    door.unlock();
	    user->items().erase(std::find(user->items().begin(), user->items().end(), item));
	  } else if (door.check_lock() == Door::LockType::UNLOCKED) {
	    std::string msg = "The door is already unlocked.";
	    out_msg = new ResponseInvalidCommand(ResponseInvalidCommand::Type::NOT_USABLE, msg);
	  } else {
	    std::string msg = "This key can't unlock the door.";
	    out_msg = new ResponseInvalidCommand(ResponseInvalidCommand::Type::NOT_USABLE, msg);	    
	  }
	    return std::unique_ptr<OutMessage>(out_msg);
	};
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
