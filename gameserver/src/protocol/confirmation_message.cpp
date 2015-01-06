//-*-c++-*-
#include "confirmation_message.h"

namespace novia {
  ConfirmationMessage::ConfirmationMessage()
    : status_(NOT_SET) {
    
  }

  ConfirmationMessage::Status ConfirmationMessage::status() const {
    return status_;
  }

  void ConfirmationMessage::set_status(ConfirmationMessage::Status status) {
    status_ = status;
  }
    
  const Json::Value ConfirmationMessage::get_message() const {
    if (status_ == NOT_SET)
      throw new std::runtime_error("status of ConfirmationMessage wasn't set");
    
    Json::Value msg;
    msg["msg_type"] = "confirmation";
    msg["status"] = status_str[status_];
    return msg;
  }
}
