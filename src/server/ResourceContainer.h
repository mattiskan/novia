#ifndef RESOURCE_CONTAINER_H
#define RESOURCE_CONTAINER_H

#include <set>
#include "ResourceHandlingError.h"


#define ALL_RESOURCES { WOOD, STONE, FOOD, IRON }
enum ResourceType { WOOD, STONE, FOOD, IRON, 
		    /*Must be last:*/ RESOURCE_COUNT };

class ResourceContainer{
 private:
  int capacity_;
  int resources_[RESOURCE_COUNT];

 public:
  ResourceContainer(int capacity, std::set<ResourceType> storedTypes);
  
  int getAmount(ResourceType) const;
  int add(int, ResourceType);
  int getCapacity() const;
  int availableStorage() const;
  int totalStorage() const;
  bool isFull() const;
  bool canStore(ResourceType) const;
  void moveTo(ResourceContainer& dest);

 private:
  void moveResourceTo(ResourceType, ResourceContainer& dest);

};



#endif
