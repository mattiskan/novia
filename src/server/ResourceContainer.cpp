#include "ResourceContainer.h"


ResourceContainer::ResourceContainer(int capacity, std::set<ResourceType> storedTypes)
  :capacity_(capacity)
{
  std::fill_n(resources_, RESOURCE_COUNT, -1);//mark all as unstored
  for(auto resource=storedTypes.begin(); resource!= storedTypes.end(); ++resource){
    resources_[*resource] = 0;
  }
}


int ResourceContainer::getAmount(ResourceType type) const {
  return std::max(0, resources_[type]);
}

void ResourceContainer::add(int amount, ResourceType type){
  if(resources_[type] == -1)
    throw ResourceHandlingError("Cannot store that resource type.");

  if(availableStorage() < amount)
    throw ResourceHandlingError("Not enough storage space left");

  resources_[type] += amount;
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

bool ResourceContainer::canStore(ResourceType type) const {
  return resources_[type] != -1;
}


void ResourceContainer::moveTo(ResourceContainer& dest) {  
  for(int i=0; i<RESOURCE_COUNT; ++i){
    ResourceType resource = static_cast<ResourceType>(i);
    if(dest.availableStorage() == 0)
      return;
    if(!dest.canStore(resource))
      continue;
    if(getAmount(resource) <= 0)
      continue;
    
    moveResourceTo( resource, dest);
  }
}

void ResourceContainer::moveResourceTo(ResourceType type, ResourceContainer& dest) {
  int movedAmount = std::min(dest.availableStorage(), getAmount(type));

  resources_[type] -= movedAmount;
  dest.resources_[type] += movedAmount;
}
