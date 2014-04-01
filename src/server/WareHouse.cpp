#include "WareHouse.h"

WareHouse::WareHouse(ResourceContainer resourceStorage)
  :resources_(resourceStorage)
{

}

int WareHouse::getResourceTotal() const {
  return resources_.totalStorage();
}
