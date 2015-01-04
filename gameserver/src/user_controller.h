//-*-c++-*-
#ifndef NOVIA_USER_CONTROLLER
#define NOVIA_USER_CONTROLLER

#include "client_connection.h"
#include "protocol/authentification_message.h"

namespace novia {
  class UserController {
    

    
  public:

    static void authenticate(const AuthentificationMessage& auth,
			     ClientConnection& message_owner);
    
  }; 
}


#endif
