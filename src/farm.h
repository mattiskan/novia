//-*-c++-*-
#ifndef NOVIA_FARM_H
#define NOVIA_FARM_H

#include "map_object.h"
#include "serializeable.h"

namespace novia {

  class Farm : public MapObject, public Serializeable {

  public:
    Farm(const Point& location);

    virtual Json::Value serialize() const override;

  };

}

#endif
