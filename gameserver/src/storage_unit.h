//-*-c++-*-
#ifndef STORAGE_UNIT_H
#define STORAGE_UNIT_H

#include <set>
#include <limits>
#include "resource_handling_error.h"

namespace novia {
#define ALL_RESOURCES { WOOD, STONE, FOOD, IRON }
  enum ResourceType { WOOD, STONE, FOOD, IRON, 
		      /*Must be last:*/ RESOURCE_COUNT };

  class StorageUnit{
  private:
    int capacity_;
    int resources_[RESOURCE_COUNT];

  public:
    StorageUnit(int capacity, std::set<ResourceType> storedTypes);
  
    int get(ResourceType) const;
    int add(int, ResourceType);
    int getCapacity() const;
    int availableStorage() const;
    int totalStorage() const;
    bool isFull() const;
    bool canStore(ResourceType) const;
    virtual void retrieveInto(StorageUnit& dest);
  private:
    void moveResourceTo(ResourceType, StorageUnit& dest);

  };
}

#endif
