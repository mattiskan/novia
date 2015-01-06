#include "map.h"
#include <stdexcept>

namespace novia {

  void Map::add(const std::shared_ptr<MapObject>& obj) {
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
