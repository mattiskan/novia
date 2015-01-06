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
  
  Json::Value Cart::serialize() const {
    return Json::Value(Json::nullValue);
  };

}
