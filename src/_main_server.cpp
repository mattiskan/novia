#include <iostream>
#include <signal.h>
#include "server_instance.h"

using namespace Novia;

ServerInstance* server;

void on_signal(int s){
  std::cout<<std::endl<<"Stopping server..."<<std::endl;
  
  server->stop();
  exit(0);
}

void catch_signals() {
  struct sigaction sigIntHandler;
   
  sigIntHandler.sa_handler = on_signal;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);
}

int main() {
  catch_signals();
  
  server = new ServerInstance;
  
  std::cout << "Starting server on port 9002..." << std::endl;
  server->start();
  return 0;
}
