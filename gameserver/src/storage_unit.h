//-*-c++-*-
#ifndef STORAGE_UNIT_H
#define STORAGE_UNIT_H

#include <set>
#include <limits>
#include <vector>

#include "resource_handling_error.h"
#include "serializable.h"

namespace novia {
#define ALL_RESOURCES { WOOD, STONE, FOOD, IRON }
  enum ResourceType { WOOD=0, STONE, FOOD, IRON, 
		      /*Must be last:*/ RESOURCE_COUNT };

  class StorageUnit : public Serializable {
  private:
    int capacity_;
    int total_storage_;
    std::vector<int> resources_;
    static const int UNAVAILABLE_RESOURCE;
  public:
    StorageUnit(int capacity, const std::set<ResourceType>& storedTypes);
    StorageUnit(int capacity, ResourceType type);
    StorageUnit(int capacity);
    StorageUnit(const StorageUnit& other);
    StorageUnit(StorageUnit&& other);
    ~StorageUnit();
    StorageUnit& operator=(const StorageUnit& other);
    StorageUnit& operator=(StorageUnit&& other);

    int get(ResourceType type) const;
    void add(int amount, ResourceType type);
    void take(int amount, ResourceType type, StorageUnit& other);
    int capacity() const;
    int available_storage() const;
    int total_storage() const;
    bool is_full() const;
    bool can_store(ResourceType type) const;

    virtual Json::Value serialize() const;
  private:
  };
}

#endif
