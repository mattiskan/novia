//-*-c++-*-
#ifndef NOVIA_SERVER_INSTANCE_H
#define NOVIA_SERVER_INSTANCE_H

#include <memory>
#include "connection_receiver.h"
#include "interval_sleeper.h"
#include "task_queue.h"


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
    ConnectionReceiver connections_;
    IntervalSleeper sleep_;
    Controllers controllers_;
    TaskQueue task_queue_;
    void message_handler(const std::shared_ptr<InMessage>& msg);
  };

}

#endif
