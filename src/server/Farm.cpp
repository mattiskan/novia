#include "Farm.h"

Farm::Farm(ResourceType type, Timer* timerPtr) :
  StorageUnit( 20, {type}) 
  , farmType_(type)
  , timerPtr_(timerPtr)
{
  startGrowth();
}

bool Farm::grow(){
  add(1, farmType_);

  return isFull()? NO_REQUEUE : REQUEUE;
}

void Farm::retrieveInto(StorageUnit& dest) {
  StorageUnit::retrieveInto(dest);
  if( !isFull())
    startGrowth();
}

void Farm::startGrowth(){
  timerPtr_->add(std::bind( &Farm::grow, this), 120);
}

