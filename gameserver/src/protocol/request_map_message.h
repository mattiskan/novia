//-*-c++-*-
#ifndef NOVIA_REQUEST_MAP_MESSAGE_H
#define NOVIA_REQUEST_MAP_MESSAGE_H

#include "in_message.h"

namespace novia {

  class RequestMapResponse;
  
  class RequestMapMessage : public InMessage {    
  public:

    // inherited from InMessage:
    void read(const Json::Value& data) override;

    void instant_reply(const Controllers& c,
		       const std::shared_ptr<ClientConnection>& owner) const override;

    void on_invoke(Controllers& c, const std::shared_ptr<ClientConnection>& owner) const override;
  };

  class RequestMapResponse : public OutMessage {
    const Json::Value serialized_map_;

  public:
    RequestMapResponse(Json::Value& serialized_map);
    
    virtual const Json::Value get_message() const override;
  };
}

#endif
