//-*-c++-*-
#include "farm.h"

namespace novia {

  Farm::Farm(const Point& location)
    : MapObject(location){
    
  }

  Json::Value Farm::serialize() const {
    return Json::Value(Json::nullValue);
  };

}
