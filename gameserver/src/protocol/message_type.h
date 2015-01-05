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
    
    MessageType from_name(const std::string& str_type);
    std::string from_enum(MessageType enum_type);  
  }
}
#endif
