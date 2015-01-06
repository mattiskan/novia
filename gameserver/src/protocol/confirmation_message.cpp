//-*-c++-*-
#include "confirmation_message.h"

namespace novia {
  ConfirmationMessage::ConfirmationMessage(Status status)
    : status_(status) {
    
  }

  ConfirmationMessage::Status ConfirmationMessage::status() const {
    return status_;
  }
    
  const Json::Value ConfirmationMessage::get_message() const {
    Json::Value msg;
    msg["msg_type"] = "confirmation";

    
    msg["message"]["status"] = status_str[status_];
    return msg;
  }
}
