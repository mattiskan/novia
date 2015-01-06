//-*-c++-*-
#ifndef NOVIA_FARM_H
#define NOVIA_FARM_H

#include "map_object.h"
#include "serializable.h"

namespace novia {

  class Farm : public MapObject {

  public:
    Farm(const Point& location);

    virtual Json::Value serialize() const override;

  };

}

#endif
