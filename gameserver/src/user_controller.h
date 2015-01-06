//-*-c++-*-
#ifndef NOVIA_USER_CONTROLLER
#define NOVIA_USER_CONTROLLER

#include <string>
#include "client_connection.h"

namespace novia {

  class UserController {
    
  public:
    bool authenticate(const std::string& username,
		      const std::string& password,
		      ClientConnection& message_owner) const;
  }; 
}


#endif
