//-*-c++-*-
#include "storage_unit.h"

namespace novia {
  const int StorageUnit::UNAVAILABLE_RESOURCE = -1;

  StorageUnit::StorageUnit(int capacity)
    : capacity_(capacity),
      total_storage_(0),
      resources_((int)ResourceType::RESOURCE_COUNT, 0)
  {
  }

  StorageUnit::StorageUnit(int capacity, const std::set<ResourceType>& stored_types)
    : capacity_(capacity),
      total_storage_(0),
      resources_(ResourceType::RESOURCE_COUNT, UNAVAILABLE_RESOURCE) //mark all as unsupported
  {
    for(auto resource : stored_types)
      resources_[resource] = 0;
  }

  StorageUnit::StorageUnit(int capacity, ResourceType type)
    : StorageUnit(capacity, std::set<ResourceType> {type})
  {

  }


  StorageUnit::StorageUnit(const StorageUnit& other) 
    : capacity_(other.capacity_),
      total_storage_(other.total_storage_),
      resources_(other.resources_)
  {
    
  }
  StorageUnit::StorageUnit(StorageUnit&& other)
    : capacity_(other.capacity_),
      total_storage_(other.total_storage_),
      resources_(std::move(other.resources_))
  {
    capacity_ = 0;
    total_storage_ = 0;
  }
  StorageUnit::~StorageUnit() {

  }
  StorageUnit& StorageUnit::operator=(const StorageUnit& other) {
    if (this == &other) return *this;
    capacity_ = other.capacity_;
    total_storage_ = other.total_storage_;
    resources_ = other.resources_;
    return *this;
  }
  StorageUnit& StorageUnit::operator=(StorageUnit&& other) {
    if (this == &other) return *this;
    capacity_ = other.capacity_;
    total_storage_ = other.total_storage_;
    resources_ = std::move(other.resources_);
    other.capacity_ = 0;
    other.total_storage_ = 0;
    return *this;
  }



  int StorageUnit::get(ResourceType type) const {
    if(!can_store(type))
      throw ResourceHandlingError("Cannot store that resource type.");
    return std::max(0, resources_[type]);
  }

  void StorageUnit::add(int amount, ResourceType type){
    if(!can_store(type))
      throw ResourceHandlingError("Cannot store that resource type.");
    int new_total_storage = total_storage_ + amount;
    if (new_total_storage > capacity() || new_total_storage < 0)
      throw ResourceHandlingError("The capacity is excided or less than zero.");
    total_storage_ = new_total_storage;
    resources_[type] += amount;
  }

  void StorageUnit::take(int amount, ResourceType type, StorageUnit& other){
    if (!can_store(type) || !other.can_store(type))
      throw ResourceHandlingError("One of the containers can't handle the resource type.");
    if (available_storage() < amount)
      throw ResourceHandlingError("Not enough avaiable capacity.");
    if (other.get(type) < amount)
      throw ResourceHandlingError("Not enough resources in container.");
    add(amount, type);
    other.add(-amount, type);
  }


  int StorageUnit::capacity() const {
    return capacity_;
  }

  int StorageUnit::available_storage() const {
    return capacity_ - total_storage();
  }

  int StorageUnit::total_storage() const {
    return total_storage_;
  }

  bool StorageUnit::is_full() const {
    return available_storage() == 0;
  }

  bool StorageUnit::can_store(ResourceType type) const {
    return resources_[type] != UNAVAILABLE_RESOURCE;
  }

}
