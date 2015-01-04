//-*-c++-*-
#include "user_controller.h"

namespace novia {

  void UserController::authenticate(const AuthentificationMessage& auth,
			     ClientConnection& message_owner) {
    
      bool successful =
	message_owner.authenticate(auth.username(), auth.password());


      if (successful){
	message_owner.send("welcome:");
	message_owner.send(auth.username().c_str());
      }
    }

  
}
