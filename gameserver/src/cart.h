//-*-c++-*-
#ifndef NOVIA_CART_H
#define NOVIA_CART_H

#include <memory>
#include "map_object.h"
#include "storage_unit.h"
#include "serializable.h"

namespace novia {

  class Cart : public MapObject {

  public:
    Cart(const Point& location);

    virtual Json::Value serialize() const override;
    StorageUnit& storage();
    const StorageUnit& storage() const;
  private:
    std::weak_ptr<MapObject> targetObject;
    StorageUnit storage_;
  };
}

#endif
