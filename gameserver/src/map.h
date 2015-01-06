//-*-c++-*-
#ifndef NOVIA_MAP_H
#define NOVIA_MAP_H
#include <vector>
#include <memory>

#include "serializable.h"
#include "map_object.h"
#include "map_square.h"

namespace novia {

  class Map : public Serializable {
    std::vector<std::shared_ptr<MapObject>> objects;
    std::vector<std::vector<MapSquare>> terrain;
    std::size_t width_;
    std::size_t height_;
  public:
    Map(std::size_t width, std::size_t height);
    void add(const std::shared_ptr<MapObject>& obj);
    std::size_t width() const;
    std::size_t height() const;
    size_t object_count() const;
    virtual Json::Value serialize() const override;
  };

}

#endif
