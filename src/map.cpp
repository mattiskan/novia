#include "map.h"

namespace Novia {

  Json::Value Map::serialize() const {
    Json::Value serialized;
    serialized["map"] = Json::Value(Json::objectValue);

    return serialized;
  }


}
