#ifndef RESOURCE_CONTAINER_H
#define RESOURCE_CONTAINER_H

#include <set>
#include "ResourceHandlingError.h"

enum ResourceType { WOOD, STONE, FOOD, IRON, 
		    /*Must be last:*/ RESOURCE_COUNT };

class ResourceContainer{
 private:
  int capacity_;
  int resources_[RESOURCE_COUNT];

  void moveResourceTo(ResourceType, ResourceContainer& dest);

 public:
  ResourceContainer(int capacity, std::set<ResourceType> storedTypes);
  
  int getAmount(ResourceType) const;
  void add(int, ResourceType);
  int availableStorage() const;
  int totalStorage() const;
  bool canStore(ResourceType) const;

  void moveTo(ResourceContainer& dest);
};



#endif
