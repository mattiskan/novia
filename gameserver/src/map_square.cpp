//-*-c++-*-
#include "map_square.h"

namespace novia {

  MapSquare::MapSquare(TerrainType terrain_type)
      : terrain_type_(terrain_type)
  {
  }

  MapSquare::TerrainType MapSquare::terrain_type() const {
    return terrain_type_;
  }

  Json::Value MapSquare::serialize() const {
    using namespace Json;
    Value serialized(objectValue);
    serialized["terrainType"] = Value((int)terrain_type());
    return serialized;
  }
}
