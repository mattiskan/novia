#ifndef NOVIA_MAP_H
#define NOVIA_MAP_H

#include "serializeable.h"

namespace Novia {

  class Map : public Serializeable {
  public:
    virtual Json::Value serialize() const override;

  };

}

#endif
