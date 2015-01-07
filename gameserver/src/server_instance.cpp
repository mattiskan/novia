//-*-c++-*-
#include "server_instance.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "controllers.h"

namespace novia {

  ServerInstance::ServerInstance()
    : sleep_(5000) {

    
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

  void ServerInstance::message_handler(const std::shared_ptr<InMessage>& msg) {
    std::cout << "message retrieved!" << std::endl;
  }


  void ServerInstance::stop() {
    connections_.terminate();
  }
}
