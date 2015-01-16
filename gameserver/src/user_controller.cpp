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
				    const std::shared_ptr<ClientConnection>& message_owner) const {
    
    if (valid_users.count(username) == 1) {
      message_owner->authenticate(valid_users[username]);
      return true;
    }
    
    return false;
  }
  
}
