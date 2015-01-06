//-*-c++-*-
#include "server_instance.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "controllers.h"

namespace novia {

  ServerInstance::ServerInstance()
    : sleep_(5000),
      task_queue_ref_(connections_.task_queue_ref()) {

    
  }

  void ServerInstance::start() {
    connections_.initiate();

    int i = 0;
    while(true) {

      std::stringstream out;
      out << "mayday mayday" << i++;
      
      connections_.broadcast(out.str());

      sleep_();
    }
    
  }


  void ServerInstance::stop() {
    connections_.terminate();
  }
}
