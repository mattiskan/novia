//-*-c++-*-
#ifndef NOVIA_REQUEST_MOVE_H
#define NOVIA_REQUEST_MOVE_H

#include "in_message.h"

namespace novia {

  class RequestMove : public InMessage {
  public:
    const std::string& door() const;

    
    // inherited from InMessage:
    virtual void read(const Json::Value& data) override;
    

    virtual void instant_reply(const Controllers& c,
			       const std::shared_ptr<ClientConnection>& owner) const override;

    virtual void on_invoke(Controllers& c,
			   const std::shared_ptr<ClientConnection>& owner) const override;
  private:
    std::string door_;
  };
}

#endif
