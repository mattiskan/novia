//-*-c++-*-
#include "response_examine.h"


namespace novia {
  ResponseExamine::ResponseExamine() {

  }

  const Json::Value ResponseExamine::get_message() const {
    using namespace Json;
    Value message(objectValue);
    message["msg_type"] = Value("response_examine");
    switch(type) {
    case ExamineType::TYPE_ITEM:
      message["type"] = "ITEM";
      message["item"] = Value(item->name());
      message["description"] = Value(item->description());
      break;
    case ExamineType::TYPE_CHARACTER:
      message["type"] = "CHARACTER";
      message["character"] = Value(character->name());
      message["description"] = Value(character->description());
      break;
    case ExamineType::TYPE_ROOM:
      message["type"] = "ROOM";
      message["room"] = Value(room->name());
      message["description"] = Value(room->description());
      break;
    case ExamineType::TYPE_DOOR:
      message["type"] = "DOOR";
      message["door"] = Value(door->entrance().entrance->name());
      message["description"] = Value(door->entrance().description);
      break;
    }
    return message;
  }


}
