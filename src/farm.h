//-*-c++-*-
#ifndef NOVIA_FARM_H
#define NOVIA_FARM_H

#include "map_object.h"
#include "serializeable.h"
#include "point.h"

namespace Novia {

  class Farm : public MapObject, public Serializeable {
    const Point location_;

  public:
    Farm(const Point& location);

    virtual Json::Value serialize() const override;

  };

}

#endif
