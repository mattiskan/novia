//-*-c++-*-
#ifndef NOVIA_REQUEST_EXAMINE_H
#define NOVIA_REQUEST_EXAMINE_H

#include "in_message.h"

namespace novia {

  class RequestExamine : public InMessage {
  public:
    const std::string& type() const;
    const std::string& target() const;
    
    // inherited from InMessage:
    virtual void read(const Json::Value& data) override;
    

    virtual void instant_reply(const Controllers& c,
			       ClientConnection& owner) const override;

    virtual void on_invoke(Controllers& c,
			   ClientConnection& owner) const override;
  private:
    std::string type_;
    std::string target_;
  };
}

#endif
