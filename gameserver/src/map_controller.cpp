#include "map_controller.h"

namespace novia {
  MapController::MapController() 
    : map_(32, 32)
  {
    
  }
  Json::Value MapController::get_serialized() const {
    return map_.serialize();
  }
}
