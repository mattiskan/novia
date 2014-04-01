#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "ResourceContainer.h"

class WareHouse {
 protected:
  ResourceContainer resources_;
 public:
  WareHouse(ResourceContainer ref);
  int getResourceTotal() const;
};

#endif
