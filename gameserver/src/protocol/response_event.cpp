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
      message["type"] = "item_gained";
      message["item"] = item->name();
      break;
    case Type::ITEM_DROPPED:
      message["type"] = "item_dropped";
      message["item"] = item->name();
      break;
    default:
      throw std::out_of_range("Unimplemented response event.");
    }
    return message;
  }


}
