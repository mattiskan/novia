//-*-c++-*-
#include "storage_unit.h"

namespace novia {
  StorageUnit::StorageUnit(int capacity, std::set<ResourceType> storedTypes)
    :capacity_(capacity)
  {
    std::fill_n(resources_, RESOURCE_COUNT, -1);//mark all as unsupported

    for(auto resource=storedTypes.begin(); resource!= storedTypes.end(); ++resource){
      resources_[*resource] = 0;
    }
  }


  int StorageUnit::get(ResourceType type) const {
    return std::max(0, resources_[type]);
  }

  int StorageUnit::add(int amount, ResourceType type){
    if(resources_[type] == -1)
      throw ResourceHandlingError("Cannot store that resource type.");

    int movedAmount = std::min(amount, availableStorage());
    resources_[type] += movedAmount;
  
    return amount - movedAmount; //the amount that didn't fit
  }

  int StorageUnit::getCapacity() const {
    return capacity_;
  }

  int StorageUnit::availableStorage() const {
    return capacity_ - totalStorage();
  }

  int StorageUnit::totalStorage() const {
    int tot = 0;
    for(int i=0; i<RESOURCE_COUNT; ++i){
      tot+=std::max(0, resources_[i]);
    }

    return tot;
  }

  bool StorageUnit::isFull() const {
    return availableStorage() == 0;
  }

  bool StorageUnit::canStore(ResourceType type) const {
    return resources_[type] != -1;
  }



  void StorageUnit::retrieveInto(StorageUnit& dest) {  
    for(int i=0; i<RESOURCE_COUNT; ++i){

      if(dest.isFull())
	return;

      ResourceType resource = static_cast<ResourceType>(i);
      if(!dest.canStore(resource) || get(resource) == 0)
	continue;
    
      moveResourceTo( resource, dest);
    }
  }

  void StorageUnit::moveResourceTo(ResourceType type, StorageUnit& dest) {
    int leftOver = dest.add(resources_[type], type);
    resources_[type] = leftOver;
  }
  
}
