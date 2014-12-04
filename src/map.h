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

    size_t object_count() const;
    virtual Json::Value serialize() const override;
  };

}

#endif
