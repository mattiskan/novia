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
    connections_.set_message_handler( [=](const std::shared_ptr<InMessage>& msg, ClientConnection& owner) {
	this->message_handler(msg, owner);
      });
    connections_.initiate();

    int i = 0;
    while(true) {
      write_mutex.lock();
      std::stringstream out;
      out << "mayday mayday" << i++;
      
      connections_.broadcast(out.str());
      write_mutex.unlock();
      sleep_();
    }
    
  }

  void ServerInstance::message_handler(const std::shared_ptr<InMessage>& msg, ClientConnection& owner) {
    write_mutex.lock();
    msg->instant_reply(controllers_, owner);
    std::cout << "message retrieved!" << std::endl;
    write_mutex.unlock();
  }


  void ServerInstance::stop() {
    connections_.terminate();
  }
}
