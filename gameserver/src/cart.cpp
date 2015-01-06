//-*-c++-*-
#include "cart.h"

namespace novia {

  Cart::Cart(const Point& location)
    : MapObject(location, MapObject::CART),
      storage_(5)
  {
    
  }

  StorageUnit& Cart::storage() {
    return storage_;
  }

  const StorageUnit& Cart::storage() const {
    return storage_;
  }
  
  Json::Value Cart::serialize() const {
    using namespace Json;
    Value serialized(MapObject::serialize());
    serialized["storage"] = storage().serialize();
    return serialized;
  };

}
