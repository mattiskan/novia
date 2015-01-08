#include "messages.h"

#include <unordered_map>
#include <memory>
#include <sstream>

#include "authentification_message.h"
#include "request_map_message.h"


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
      REQUEST_MAP
    };

    std::unordered_map<std::string, MessageType> from_name_ = {
      {"authenticate", AUTHENTICATE},
      {"request_map", REQUEST_MAP}
    };
    
    InMessage* from_type(const std::string& message_type) {
      MessageType type = from_name_.at(message_type);
      
      switch(type) {	
      case AUTHENTICATE: return new AuthentificationMessage;
      case REQUEST_MAP: return new RequestMapMessage;
      }
      std::stringstream error_msg;
      error_msg << "unknown message type: " << message_type;
      throw std::domain_error(error_msg.str());
    }

  }
}
