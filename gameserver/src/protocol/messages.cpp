#include "messages.h"

#include <unordered_map>
#include "authentification_message.h"

namespace novia{
  namespace messages {

    InMessage* from_type(std::string messgage_type);
    
    Json::Reader reader;
    
    InMessage* in_message(std::string payload) {
      Json::Value data;
      reader.parse(payload, data, false);
      
      std::string message_type = data["msg_type"].asString();
      InMessage* msg = from_type(message_type);
      msg->read(data);
      
      return msg;
    }    
    
    enum MessageType {
      AUTHENTICATE = 1
    };

    std::unordered_map<std::string, MessageType> from_name_ = {
      {"authenticate", AUTHENTICATE}
    };
    
    InMessage* from_type(std::string message_type) {
      MessageType type = from_name_.at(message_type);
      
      switch(type) {	
      case AUTHENTICATE: return new AuthentificationMessage();
      }
  
      throw std::domain_error("unknown message type");
    }

  }
}
