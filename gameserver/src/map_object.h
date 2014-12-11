//-*-c++-*-
#ifndef NOVIA_MAP_OBJECT_H
#define NOVIA_MAP_OBJECT_H
#include "point.h"

namespace novia {

  class MapObject {
  protected:
    const Point location_;

    MapObject(const Point& location);
  };

}

#endif
