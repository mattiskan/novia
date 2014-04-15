#include "Farm.h"

Farm::Farm(ResourceType type, Timer* timerPtr) :
  WareHouse( ResourceContainer(FARM_STORAGE, {type}) ) 
  , product_(type)
  , timerPtr_(timerPtr)
{
  startGrowth();
}


bool Farm::grow(){
  resources_.add(1, product_);

  return (resources_.isFull()) ? NO_REQUEUE : REQUEUE;
}


void Farm::startGrowth(){
  timerPtr_->add(std::bind( &Farm::grow, this), 120);
}

