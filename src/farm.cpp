//-*-c++-*-
#include "farm.h"

namespace Novia {

  Farm::Farm(const Point& location)
    : location_(location){
    
  }

  Json::Value Farm::serialize() const {
    return Json::Value(Json::nullValue);
  };

}
