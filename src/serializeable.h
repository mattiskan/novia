#ifndef NOVIA_SERIALIZEABLE_H
#define NOVIA_SERIALIZEABLE_H

#include <jsoncpp/json.h>

namespace Novia {

  class Serializeable {
  public:
    virtual Json::Value serialize() const = 0;

  };
}

#endif
