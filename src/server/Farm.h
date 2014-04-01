#ifndef FARM_H
#define FARM_H

#include "WareHouse.h"


class Farm: public WareHouse {
 private:
  ResourceType product_;

 public:
  Farm(ResourceType);
  void grow();
};

#endif
