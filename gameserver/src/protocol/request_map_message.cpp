//-*-c++-*-
#include "request_map_message.h"

namespace novia {

  void RequestMapMessage::read(const Json::Value& data) {
    
  }

  void RequestMapMessage::instant_reply(const Controllers& c,
					ClientConnection& owner) const {

    Json::Value serialized_map(c.map_controller.get_serialized());
    RequestMapResponse response(serialized_map);
    owner.send(&response);
  }
  
  void RequestMapMessage::on_invoke(Controllers& c,
				    ClientConnection& owner) const {

  }

  RequestMapResponse::RequestMapResponse(Json::Value& serialized_map)
    : serialized_map_(serialized_map) {

  }
  
  const Json::Value RequestMapResponse::get_message() const {
    return serialized_map_;
  }
}

