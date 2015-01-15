//-*-c++-*-
#include "response_move.h"



namespace novia {
  ResponseMove::ResponseMove() {

  }

  const Json::Value ResponseMove::get_message() const {
    using namespace Json;
    Value message(objectValue);
    message["msg_type"] = Value("move");
    message["entrance"] = Value(entrance->name());
    message["exit"] = Value(exit->name());
    message["character"] = Value(character->name());
    return message;
  }


}
