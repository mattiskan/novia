//-*-c++-*-
#ifndef NOVIA_CONTROLLERS_H
#define NOVIA_CONTROLLERS_H

#include "client_connection.h"

namespace novia {

  /*
   * Simple reference holder
   */
  struct Controllers {
    ClientConnection& user;
    //MapController& mapController; 
  };
  
}

#endif
