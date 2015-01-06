//-*-c++-*-
#ifndef NOVIA_MAP_H
#define NOVIA_MAP_H
#include <vector>
#include <memory>

#include "serializable.h"
#include "map_object.h"

namespace novia {

  class Map : public Serializable {
    std::vector<std::shared_ptr<MapObject>> objects;

  public:
    void add(const std::shared_ptr<MapObject>& obj);

    size_t object_count() const;
    virtual Json::Value serialize() const override;
  };

}

#endif
