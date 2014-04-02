#ifndef FARM_H
#define FARM_H

#include "../Config.h"
#include "WareHouse.h"
#include "Timer.h"


class Farm: public WareHouse {
 private:
  ResourceType product_;
  Timer* timerPtr_;

 public:
  Farm(ResourceType, Timer*);
  bool grow();

 private:
  void startGrowth();
};

#endif
