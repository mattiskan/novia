#include "map_controller.h"

namespace novia {
  MapController::MapController() 
    : map_()
  {
    
  }
  Json::Value MapController::get_serialized() const {
    return map_.serialize();
  }
}
