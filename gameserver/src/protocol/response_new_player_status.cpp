//-*-c++-*-
#include "response_new_player_status.h"
#include <sstream>

namespace novia {
  ResponseNewPlayerStatus::ResponseNewPlayerStatus() {

  }

  const Json::Value ResponseNewPlayerStatus::get_message() const {
    using namespace Json;
    Value message(objectValue);
    message["msg_type"] = Value("response_new_player_status");
    message["player"] = Value(player->name());
      
    switch(status) {
    case Status::CONNECTED:
      message["status"] = Value("CONNECTED");
      break;
    case Status::DISCONNECTED:
      message["status"] = Value("DISCONNECTED");
      break;
    case Status::NEW_PLAYER:
      message["status"] = Value("NEW_PLAYER");
      break;
    default:
      std::stringstream error_msg;
      error_msg << "Unknown status: '" << (int)status << "'";
      throw std::invalid_argument(error_msg.str());
    }
    return message;
  }


}
