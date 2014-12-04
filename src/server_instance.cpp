//-*-c++-*-
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "server_instance.h"

namespace novia {

  ServerInstance::ServerInstance()
    : sleep_(5000) {
  
  }

  void ServerInstance::start() {
    connections_.initiate();

    int i = 0;
    while(true) {
      std::stringstream ss;
      ss << "mayday mayday " << i++;

      connections_.broadcast(ss.str());
      sleep_();
    }
  
  }


  void ServerInstance::stop() {
    connections_.terminate();
  }
}
