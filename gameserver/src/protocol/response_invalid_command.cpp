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

    
    return response;
  }


}
