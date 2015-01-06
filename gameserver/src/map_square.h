// -*-c++-*-
#ifndef NOVIA_MAP_SQUARE_H
#define NOVIA_MAP_SQUARE_H

#include "serializable.h"

namespace novia {

  class MapSquare : public Serializable  {
  public:
    enum class TerrainType { GRASS, FOREST, MOUNTAIN };
    MapSquare(TerrainType terrain_type);
    TerrainType terrain_type() const;
    virtual Json::Value serialize() const override;
  private:
    const TerrainType terrain_type_;
  };
}

#endif
