#include "ResourceContainer.h"

ResourceContainer::ResourceContainer(int capacity, std::set<ResourceType> storedTypes)
  :capacity_(capacity)
{
  std::fill_n(resources_, RESOURCE_COUNT, -1);//mark all as unsupported

  for(auto resource=storedTypes.begin(); resource!= storedTypes.end(); ++resource){
    resources_[*resource] = 0;
  }
}


int ResourceContainer::getAmount(ResourceType type) const {
  return std::max(0, resources_[type]);
}

int ResourceContainer::add(int amount, ResourceType type){
  if(resources_[type] == -1)
    throw ResourceHandlingError("Cannot store that resource type.");

  int movedAmount = std::min(amount, availableStorage());
  resources_[type] += movedAmount;
  
  return amount - movedAmount; //the amount that didn't fit
}

int ResourceContainer::availableStorage() const {
  return capacity_ - totalStorage();
}

int ResourceContainer::totalStorage() const {
  int tot = 0;
  for(int i=0; i<RESOURCE_COUNT; ++i){
    tot+=std::max(0, resources_[i]);
  }

  return tot;
}

bool ResourceContainer::isFull() const {
  return availableStorage() == 0;
}

bool ResourceContainer::canStore(ResourceType type) const {
  return resources_[type] != -1;
}


void ResourceContainer::moveTo(ResourceContainer& dest) {  
  for(int i=0; i<RESOURCE_COUNT; ++i){

    if(dest.isFull())
      return;

    ResourceType resource = static_cast<ResourceType>(i);
    if(!dest.canStore(resource) || getAmount(resource) == 0)
      continue;
    
    moveResourceTo( resource, dest);
  }
}

void ResourceContainer::moveResourceTo(ResourceType type, ResourceContainer& dest) {
  int leftOver = dest.add(resources_[type], type);
  resources_[type] = leftOver;
}
