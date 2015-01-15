//-*-c++-*-
#include "response_info.h"
#include <item.h>
#include <character.h>
#include <door.h>

namespace novia {
  ResponseInfo::ResponseInfo() {

  }

  const Json::Value ResponseInfo::get_message() const {
    using namespace Json;
    Value message(objectValue);
    message["msg_type"] = Value("info");
    message["description"] = Value(room->description());
    Value& characters = message["characters"] = Value(arrayValue);
    for (const std::shared_ptr<Character>& character : room->characters()) {
      characters.append(Value(character->name()));
    }

    Value& exits = message["exits"] = Value(arrayValue);
    for (const std::pair<const std::string, Door>& exit : room->exits()) {
      exits.append(Value(exit.first));
    }

    Value& items = message["items"] = Value(arrayValue);
    for (const std::pair<const std::string, std::shared_ptr<Item>>& item : room->items()) {
      items.append(Value(item.first));
    }

    return message;
  }


}
