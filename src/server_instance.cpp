#include "server_instance.h"
#include <stdexcept>
#include <iostream>
#include "connection_reciever.h"
#include "interval_sleeper.h"

void ServerInstance::start() {
  IntervalSleeper sleep(3000);
  ConnectionReceiver cr;

  cr.initiate();

  while(true) {
    cr.broadcast("mayday, mayday");
    sleep();
  }
  
}

