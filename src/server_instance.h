#ifndef NOVIA_SERVER_INSTANCE_H
#define NOVIA_SERVER_INSTANCE_H

#include "connection_reciever.h"
#include "interval_sleeper.h"

namespace Novia {

  /**
   * Class used to start and control a server instance for a single game.
   */
  class ServerInstance {
    ConnectionReceiver connections_;
    IntervalSleeper sleep_;

  public:
    ServerInstance();

    void start();
    void stop();
  };

}

#endif
