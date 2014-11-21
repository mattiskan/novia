#include <iostream>
#include "server_instance.h"

int main() {
  ServerInstance server;
  std::cout << "Starting server..." << std::endl;
  server.start();
  return 0;
}
