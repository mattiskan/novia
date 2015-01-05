//-*-c++-*-
#ifndef NOVIA_MAP_CONTROLLER
#define NOVIA_MAP_CONTROLLER

#include "client_connection.h"

namespace novia {
  class MapController {
        
  public:

    static void authenticate(const AuthentificationMessage& auth,
			     ClientConnection& message_owner);
    
  }; 
}


#endif
