#ifndef FARM_H
#define FARM_H

#include "../Config.h"
#include "WareHouse.h"
#include "Timer.h"


class Farm: public StorageUnit {
 private:
  Timer* timerPtr_;

 public:
  const ResourceType farmType_;

  Farm(ResourceType, Timer*);
  bool grow();

  virtual void retrieveInto(StorageUnit& dest) override;

 private:
  void startGrowth();
};

#endif
