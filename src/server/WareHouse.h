#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "ResourceContainer.h"
#include "../Config.h"

class WareHouse {
 protected:
  ResourceContainer resources_;
 public:
  WareHouse();
  WareHouse(ResourceContainer resources_);

  ResourceContainer getStorage() const;
  ResourceContainer addToStorage(ResourceContainer&);
};

#endif
