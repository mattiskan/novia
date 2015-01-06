//-*-c++-*-
#include "user_controller.h"

#include <unordered_map>
#include <iostream>

std::unordered_map<std::string, int> valid_users = {
  { "mattis", 1337},
  { "axel", 4711},
  { "test", 123}
};

namespace novia {

  bool UserController::authenticate(const std::string& username,
				    const std::string& password,
				    ClientConnection& message_owner) const {
    
    if (valid_users.count(username) == 1) {
      std::cout << "authenticated user " << username << std::endl;
      return true;
    }

    return false;
  }
  
}
