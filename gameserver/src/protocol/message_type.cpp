#include "message_type.h"

namespace novia{
  namespace message_type {

    /* See message_type.h for enum MessageType */
    
    std::unordered_map<std::string, MessageType> from_name_ = {
      {"authenticate", AUTHENTICATE}
    };

    MessageType from_name(const std::string& str_type) {
      return from_name_.at(str_type);
    }

    std::string from_enum(MessageType enum_type) {
      switch(enum_type) {
      case AUTHENTICATE: return "authenticate";
      }
  
      throw std::domain_error("unknonw message type");
    }

  }
}
