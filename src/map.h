//-*-c++-*-
#ifndef NOVIA_MAP_H
#define NOVIA_MAP_H
#include <vector>

#include "serializeable.h"
#include "map_object.h"

namespace Novia {

  class Map : public Serializeable {
    std::vector<MapObject> objects;

  public:
    void add(const MapObject& obj);
    virtual void deserialize(const Json::Value& data) override;

    size_t object_count() const;
    virtual Json::Value serialize() const override;
  };

}

#endif
