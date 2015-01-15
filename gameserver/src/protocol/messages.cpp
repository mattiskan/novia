#include "messages.h"

#include <unordered_map>
#include <memory>
#include <sstream>

#include "authentification_message.h"
#include "request_move.h"
#include "request_examine.h"
#include "request_take.h"
#include "request_use.h"

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
      MOVE,
      TAKE,
      USE
    };

    std::unordered_map<std::string, MessageType> from_name_ = {
      {"authenticate", AUTHENTICATE},
      {"examine", EXAMINE},
      {"move", MOVE},
      {"take", TAKE},
      {"use", USE}
    };
    
    InMessage* from_type(const std::string& message_type) {
      if (!from_name_.count(message_type)) {
	std::stringstream error_msg;
	error_msg << "unknown message type: '" << message_type <<"'";
	throw std::domain_error(error_msg.str());
      }
      MessageType type = from_name_.at(message_type);
      
      switch(type) {	
      case AUTHENTICATE: return new AuthentificationMessage;
      case EXAMINE: return new RequestExamine;
      case MOVE: return new RequestMove;
      case TAKE: return new RequestTake;
      case USE: return new RequestUse;
      }
      std::stringstream error_msg;
      error_msg << "unknown message type enum: '" << message_type<<"'";
      throw std::domain_error(error_msg.str());
    }

  }
}
