#include "messages.h"

#include <unordered_map>
#include <memory>
#include <sstream>

#include "authentification_message.h"
#include "request_move.h"
#include "request_examine.h"

namespace novia{
  namespace messages {

    InMessage* from_type(const std::string& messgage_type);
    
    Json::Reader reader;
    
    std::shared_ptr<InMessage> in_message(const std::string& payload) {
      Json::Value data;
      reader.parse(payload, data, false);
      
      std::string message_type(data["msg_type"].asString());
      std::shared_ptr<InMessage> msg(from_type(message_type));
      msg->read(data);
      
      return msg;
    }    
    
    enum MessageType {
      AUTHENTICATE = 1,
      EXAMINE,
      MOVE
    };

    std::unordered_map<std::string, MessageType> from_name_ = {
      {"authenticate", AUTHENTICATE},
      {"examine", EXAMINE},
      {"move", MOVE},

    };
    
    InMessage* from_type(const std::string& message_type) {
      MessageType type = from_name_.at(message_type);
      
      switch(type) {	
      case AUTHENTICATE: return new AuthentificationMessage;
      case EXAMINE: return new RequestExamine;
      case MOVE: return new RequestMove;
      }
      std::stringstream error_msg;
      error_msg << "unknown message type: " << message_type;
      throw std::domain_error(error_msg.str());
    }

  }
}
