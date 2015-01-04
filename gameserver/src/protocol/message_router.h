//-*-c++-*-
#ifndef NOVIA_MESSAGE_ROUTER_H
#define NOVIA_MESSAGE_ROUTER_H

#include <string>
#include <unordered_map>

#include "message.h"
#include "authentification_message.h"
#include "../user_controller.h"

#include <iostream>
namespace novia {

  namespace message_router {
    static Json::Reader reader;
    
    static Message* get_message(const std::string& msg_type);
    
    static Message* read_message(std::string payload) {
      Json::Value data;
      reader.parse(payload, data, false);
      
      std::string msg_type = data["msg_type"].asString();
      Message* msg = get_message(msg_type);
      msg->read(data);
      
      return msg;
    }

    static void invoke_now(Message* msg, ClientConnection& message_owner) {
      switch(msg->type()) {
      case AUTHENTICATE:
	  UserController::authenticate(*((AuthentificationMessage*) msg),
				       message_owner);
	  break;

      default:
	throw std::runtime_error("no route for message type");
      }
    }

    static void invoke_later(Message* msg, ClientConnection& cc_ref) {
      throw std::runtime_error("not implemented");
    }    

    static Message* get_message(const std::string& msg_type) {
      int type_val = message_type::from_name(msg_type);
      
      switch(type_val) {
      case AUTHENTICATE: return new AuthentificationMessage();
	
      }
      throw std::runtime_error("no implementation message found");
    }
  }
}

#endif
