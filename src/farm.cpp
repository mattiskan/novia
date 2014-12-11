//-*-c++-*-
#include "farm.h"

namespace Novia {

  Farm::Farm(const Point& location)
    : MapObject(location){
    
  }

  Json::Value Farm::serialize() const {
    return Json::Value(Json::nullValue);
  };

}
