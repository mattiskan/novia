//-*-c++-*-
#ifndef NOVIA_REQUEST_USE_H
#define NOVIA_REQUEST_USE_H

#include "in_message.h"

namespace novia {

  class RequestUse : public InMessage {
  public:
    const std::string& type() const;
    const std::string& target() const;
    int item() const;

    int target_int() const;
    
    // inherited from InMessage:
    virtual void read(const Json::Value& data) override;
    

    virtual void instant_reply(const Controllers& c,
			       ClientConnection& owner) const override;

    virtual void on_invoke(Controllers& c,
			   ClientConnection& owner) const override;
  private:
    int item_;
    std::string type_;
    std::string target_;
    int target_int_;
  };
}

#endif
