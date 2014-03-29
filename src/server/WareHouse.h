#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "ResourceContainer.h"

class WareHouse {
 private:
  ResourceContainer* resources;
 public:
  WareHouse();
  int getResourceTotal() const;
  void incrementResources(ResourceContainer);
};

#endif
