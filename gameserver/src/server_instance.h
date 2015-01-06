//-*-c++-*-
#ifndef NOVIA_SERVER_INSTANCE_H
#define NOVIA_SERVER_INSTANCE_H

#include "connection_receiver.h"
#include "interval_sleeper.h"
#include "task_queue.h"


namespace novia {

  /**
   * Class used to start and control a server instance for a single game.
   */
  class ServerInstance {
    ConnectionReceiver connections_;
    IntervalSleeper sleep_;
    TaskQueue& task_queue_ref_;

  public:
    ServerInstance();

    void start();
    void stop();
  };

}

#endif
