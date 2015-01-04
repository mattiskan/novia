//-*-c++-*-
#ifndef NOVIA_MESSAGE_TYPES_H
#define NOVIA_MESSAGE_TYPES_H

#include <string>
#include <unordered_map>
#include <stdexcept>

namespace novia {
  namespace message_type {

    enum MessageType {
      AUTHENTICATE = 1
    };
    
    static std::unordered_map<std::string, MessageType> from_name_ = {
      {"authenticate", AUTHENTICATE}
    };
  
    static MessageType from_name(const std::string& str_type) {
      return from_name_.at(str_type);
    }

    static std::string from_enum(MessageType enum_type) {
      switch(enum_type) {
      case AUTHENTICATE: return "authenticate";
      }

      throw std::domain_error("unknonw message type");
    }
  }
}
#endif
