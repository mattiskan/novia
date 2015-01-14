//-*-c++-*-
#include "server_instance.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "controllers.h"

namespace novia {

  ServerInstance::ServerInstance()
    : sleep_(500) {

    
  }

  void ServerInstance::start() {
    connections_.set_message_handler( [=](const std::shared_ptr<InMessage>& msg, 
					  const std::shared_ptr<ClientConnection>& owner) {
	this->message_handler(msg, owner);
      });
    connections_.initiate();

    //int i = 0;
    while(true) {
      write_mutex.lock(); //Make sure only this thread uses the data model.
      process_tasks();
      /*std::stringstream out;
      out << "mayday mayday" << i++;
      
      connections_.broadcast(out.str());*/
      write_mutex.unlock(); 
      sleep_();
    }
    
  }

  void ServerInstance::process_tasks() {
    while (!task_queue_.empty()) {
      task_queue_.front()();
      task_queue_.pop();
    }
  }

  void ServerInstance::message_handler(const std::shared_ptr<InMessage>& msg, const std::shared_ptr<ClientConnection> & owner) {
    write_mutex.lock();
    msg->instant_reply(controllers_, *owner);
    std::cout << "message retrieved!" << std::endl;
    task_queue_.push([=]() {
	msg->on_invoke(this->controllers_, *owner);
      });
    write_mutex.unlock();
  }


  void ServerInstance::stop() {
    connections_.terminate();
  }
}
