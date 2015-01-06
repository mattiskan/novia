//-*-c++-*-
#ifndef NOVIA_MAP_CONTROLLER_H
#define NOVIA_MAP_CONTROLLER_H

#include "map.h"

namespace novia {

  class MapController {
    Map map_;
  public:
    
    Json::Value get_serialized() const;
    
  };
  
}

#endif

