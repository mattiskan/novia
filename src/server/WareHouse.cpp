#include "WareHouse.h"

WareHouse::WareHouse()
  : resources_(WARE_HOUSE_STORAGE, ALL_RESOURCES)
{ }

WareHouse::WareHouse(ResourceContainer resources)
  : resources_(resources)
{ }


ResourceContainer WareHouse::getStorage() const {
  return resources_;
}

ResourceContainer WareHouse::addToStorage(ResourceContainer& newWares) {
  ResourceContainer leftOvers(newWares);
  leftOvers.moveTo(resources_);
  return leftOvers;
}
