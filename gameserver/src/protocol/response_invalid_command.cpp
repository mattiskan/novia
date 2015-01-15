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
    Json::Value response;
    
    switch(error_type_) {
    case Type::UNKNOWN_TARGET:
      response["type"] = "unknown_target";
      break;
    case Type::TOO_FEW_ARGUMENTS:
      response["type"] = "too_few_arguments";
      break;
    case Type::INVALID_COMMAND:
      response["type"] = "invalid_command";
      break;
    case Type::NOT_USABLE:
      response["type"] = "not_usable";
      break;
    case Type::UNAUTHORIZED:
      response["type"] = "unauthorized";
      break;
    case Type::NOT_ATTACKABLE:
      response["type"] = "not_attackable";
      break;
    }

    response["msg_type"] = "invalid_command";
    response["message"] = error_message_;
    
    return response;
  }


}
