//-*-c++-*-
#include "server_instance.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "controllers.h"
#include "protocol/response_invalid_command.h"


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

      controllers_.map_controller.kill_dead_players(connections_);

            
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
    std::cout << "message_handler" << std::endl;
    
    write_mutex.lock();
    if(owner->authenticated() || !msg->requires_authentication()) {

      msg->instant_reply(controllers_, *owner);
      std::cout << "message retrieved!" << std::endl;
      task_queue_.push([=]() {
	  msg->on_invoke(this->controllers_, *owner);
	});
    } else {
      auto error = ResponseInvalidCommand::Type::UNAUTHORIZED;
      owner->send(ResponseInvalidCommand(error, "That command requires login."));
    }
      
    write_mutex.unlock();
  }


  void ServerInstance::stop() {
    connections_.terminate();
  }
}
