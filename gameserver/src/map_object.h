//-*-c++-*-
#ifndef NOVIA_MAP_OBJECT_H
#define NOVIA_MAP_OBJECT_H
#include "point.h"
#include "serializable.h"

namespace novia {

  class MapObject : public Serializable {
  public:
    enum ObjectType { FARM, CART};

    virtual Json::Value serialize() const override;
    ObjectType type() const;
    const Point& location() const;
  protected:
    const Point location_;
    const ObjectType type_;

    MapObject(const Point& location, ObjectType type);
  };

}

#endif
