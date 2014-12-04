#include "map.h"

namespace Novia {

  void Map::add(const MapObject& obj) {
    objects.push_back(obj);
  }

  size_t Map::object_count() const {
    return objects.size();
  }

  Json::Value Map::serialize() const {
    Json::Value serialized;
    serialized["map"] = Json::Value(Json::objectValue);

    return serialized;
  }


}
