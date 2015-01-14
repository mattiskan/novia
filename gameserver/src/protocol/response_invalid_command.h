//-*-c++-*-
#ifndef NOVIA_RESPONSE_INVALID_COMMAND_H
#define NOVIA_RESPONSE_INVALID_COMMAND_H

#include <string>
#include <item.h>

#include "out_message.h"


namespace novia {
  
  class ResponseInvalidCommand : public OutMessage {    
  public:
    enum class Type { UNKNOWN_TARGET, TOO_FEW_ARGUMENTS };
    ResponseInvalidCommand(Type error_type, const std::string& error_msg);
    const std::string& error_message() const;
    Type error_type() const;
    virtual const Json::Value get_message() const override;
  private:
    std::string error_message_;
    Type error_type_;

  };
}

#endif
