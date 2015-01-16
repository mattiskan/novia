//-*-c++-*-
#ifndef NOVIA_SERVER_INSTANCE_H
#define NOVIA_SERVER_INSTANCE_H

#include <memory>
#include <mutex>

#include "connection_receiver.h"
#include "interval_sleeper.h"
#include "task_queue.h"
#include "timer.h"


namespace novia {

  /**
   * Class used to start and control a server instance for a single game.
   */
  class ServerInstance {
  public:
    ServerInstance();

    void start();
    void stop();
  private:
    std::mutex write_mutex;
    ConnectionReceiver connections_;
    IntervalSleeper sleep_;
    Controllers controllers_;
    TaskQueue task_queue_;
    Timer timer_;
    
    void message_handler(const std::shared_ptr<InMessage>& msg, const std::shared_ptr<ClientConnection>& owner);
    void process_tasks();
  };

}

#endif
