//-*-c++-*-
#include "map_object.h"

namespace novia {

  MapObject::MapObject(const Point& location, ObjectType type)
    : location_(location),
      type_(type)
  {

  }

  MapObject::ObjectType MapObject::type() const {
    return type_;
  }

  const Point& MapObject::location() const {
    return location_;
  }

  Json::Value MapObject::serialize() const {
    Json::Value serialized(Json::objectValue);
    serialized["type"] = Json::Value(type());
    serialized["location"] = location().serialize();
    
    return serialized;
  }

}
