//-*-c++-*-
#ifndef NOVIA_SERIALIZEABLE_H
#define NOVIA_SERIALIZEABLE_H

#include <jsoncpp/json.h>

namespace novia {

  class Serializeable {
  public:

    virtual Json::Value serialize() const = 0;
    
  };
}

#endif
