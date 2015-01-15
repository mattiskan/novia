//-*-c++-*-
#include "response_examine.h"


namespace novia {
  ResponseExamine::ResponseExamine() {

  }

  const Json::Value ResponseExamine::get_message() const {
    using namespace Json;
    Value message(objectValue);
    message["msg_type"] = Value("examine");
    switch(type) {
    case ExamineType::ITEM:
      message["type"] = "ITEM";
      message["item"] = Value(item->name());
      message["description"] = Value(item->description());
      break;
    case ExamineType::CHARACTER:
      message["type"] = "CHARACTER";
      message["character"] = Value(character->name());
      message["description"] = Value(character->description());
      break;
    case ExamineType::ROOM:
      message["type"] = "ROOM";
      message["room"] = Value(room->name());
      message["description"] = Value(room->description());
      break;
    case ExamineType::DOOR:
      message["type"] = "DOOR";
      message["door"] = Value(door->entrance()->name());
      message["description"] = Value(door->description());
      break;
    case ExamineType::BACKPACK:
      message["type"] = "BACKPACK";
      message["items"] = Value(arrayValue);
      for (const std::shared_ptr<Item>& item : character->items()) {
	message["items"].append(Value(item->name()));
      }
      
      break;
    }
    return message;
  }


}
