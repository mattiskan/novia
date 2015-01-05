//-*-c++-*-
#ifndef NOVIA_CONTROLLERS_H
#define NOVIA_CONTROLLERS_H

#include "user_controller.h"
#include "task_queue.h"

namespace novia {

  /*
   * Simple reference holder
   */
  struct Controllers {
    UserController user_controller;
    TaskQueue task_queue;
    //MapController map_controller;

    
  };
  
}

#endif
