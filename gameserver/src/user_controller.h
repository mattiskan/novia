//-*-c++-*-
#ifndef NOVIA_USER_CONTROLLER
#define NOVIA_USER_CONTROLLER

#include <string>
#include <memory>
#include "client_connection.h"

namespace novia {

  class UserController {
    
  public:
    bool authenticate(const std::string& username,
		      const std::string& password,
		      const std::shared_ptr<ClientConnection>& message_owner) const;
  }; 
}


#endif
