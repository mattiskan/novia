//-*-c++-*-
#include "response_invalid_command.h"

namespace novia {

  ResponseInvalidCommand::ResponseInvalidCommand(Type error_type, const std::string& error_message)
    : error_message_(error_message),
      error_type_(error_type)
  {}

  const std::string& ResponseInvalidCommand::error_message() const {
    return error_message_;
  }

  ResponseInvalidCommand::Type ResponseInvalidCommand::error_type() const {
    return error_type_;
  }

  const Json::Value ResponseInvalidCommand::get_message() const {
    using namespace Json;
    Value response(objectValue);
    response["msg_type"] = Value("invalid_command");
    Value type_val;
    switch(error_type_) {
    case Type::UNKNOWN_TARGET:
      type_val = Value("unknown_target");
      break;
    case Type::TOO_FEW_ARGUMENTS:
      type_val = Value("too_few_arguments");
      break;
    case Type::INVALID_COMMAND:
      type_val = Value("invalid_command");
      break;
    case Type::NOT_USABLE:
      type_val = Value("not_usable");
      break;

    }
    response["type"] = type_val;
    response["message"] = error_message_;
    
    return response;
  }


}
