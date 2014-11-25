#include <iostream>
#include "server_instance.h"


int main() {
  ServerInstance server;
  std::cout << "Starting server on port 9002..." << std::endl;
  server.start();
  return 0;
}
