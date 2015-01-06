#include "map_controller.h"

namespace novia {
  Json::Value MapController::get_serialized() const {
    return map_.serialize();
  }
}
