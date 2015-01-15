//-*-c++-*-
#include "response_event.h"
#include <stdexcept>


namespace novia {
  ResponseEvent::ResponseEvent() {

  }

  const Json::Value ResponseEvent::get_message() const {
    using namespace Json;
    Value message(objectValue);
    message["msg_type"] = Value("event");
    switch(type) {
    case Type::ITEM_GAINED:
      message["type"] = "ITEM_GAINED";
      message["item"] = item->name();
      break;
    case Type::ITEM_DROPPED:
      message["type"] = "ITEM_DROPPED";
      message["item"] = item->name();
      break;
    case Type::DOOR_OPENED:
      message["type"] = "DOOR_OPENED";
      message["door"] = door->description();
      break;
      //default:
      //throw std::out_of_range("Unimplemented response event.");
    }
    return message;
  }


}
