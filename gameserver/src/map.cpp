#include "map.h"
#include <stdexcept>

namespace novia {

  Map::Map(std::size_t width, std::size_t height)
    : width_(width),
      height_(height),
      terrain(height, std::vector<MapSquare>(width, MapSquare(MapSquare::GRASS)));
  {

  }

  std::size_t width() const {
    return width_;
  }

  std::size_t height() const {
    return height_;
  }

  void Map::add(const std::shared_ptr<MapObject>& obj) {
    objects.push_back(obj);
  }

  size_t Map::object_count() const {
    return objects.size();
  }

  Json::Value Map::serialize() const {
    using namespace Json;
    Value serialized(objectValue);
    Value map_objects_serialized(serialized["mapObjects"] = Value(arrayValue));
    for (const std::shared_ptr<MapObject>& mapObject : objects) {
      map_objects_serialized.append(mapObject->serialize());
    }

    return serialized;
  }


}
