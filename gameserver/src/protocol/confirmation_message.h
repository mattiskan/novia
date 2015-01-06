//-*-c++-*-
#ifndef NOVIA_CONFIRMATION_MESSAGE_H
#define NOVIA_CONFIRMATION_MESSAGE_H

#include "out_message.h"
#include <string>


namespace novia {
  
  class ConfirmationMessage : public OutMessage {    
  public:
    enum Status {
      ACCEPTED = 0,
      REJECTED,
      INVALID_REQUEST,
      DENIED
    };
    
    ConfirmationMessage(Status status);

    Status status() const;
    
    virtual const Json::Value get_message() const override;

  private:
    const Status status_;
    
    const std::string status_str[4] = {
      "accepted",
      "rejected",
      "invalid_request",
      "denied"
    };

  };
}

#endif
