#include <iostream>
#include <cxxtest/TestSuite.h>
#include "../src/server/ResourceContainer.h"

class ResourceContainerTest : public CxxTest::TestSuite
{
 public:

  void setUp(){
    
  }

  void testStoreOneResource(){
    const int CAP = 20;
    
    std::set<ResourceType> storedTypes = { WOOD };
    ResourceContainer resourceContainer(CAP,  storedTypes);

    for(int i=1; i<= CAP; ++i){
      resourceContainer.add(1, WOOD);
      TS_ASSERT_EQUALS( resourceContainer.getAmount(WOOD), i);//invariant
    }
  }

  void testStoreTwoResources(){
    const int CAP = 20;

    std::set<ResourceType> storedTypes = { WOOD, FOOD };
    ResourceContainer resourceContainer(CAP,  storedTypes);


    for(int i=1; i<= CAP/2; ++i){
      resourceContainer.add(1, WOOD);
      resourceContainer.add(1, FOOD);
      TS_ASSERT_EQUALS( resourceContainer.getAmount(WOOD), i);//invariant
      TS_ASSERT_EQUALS( resourceContainer.getAmount(FOOD), i);//invariant
    }
  }

  void testCapacityOverload(){
    std::set<ResourceType> storedTypes = { WOOD };
    ResourceContainer resourceContainer(20, storedTypes);

    TS_ASSERT_THROWS(resourceContainer.add(30, WOOD), ResourceHandlingError);
    
    resourceContainer.add(20, WOOD);

    TS_ASSERT_THROWS(resourceContainer.add(1, WOOD), ResourceHandlingError);
  }

  void testTotalStorage() {
    std::set<ResourceType> storedTypes = { WOOD, STONE, FOOD, IRON };
    ResourceContainer resourceContainer(30, storedTypes);

    resourceContainer.add(1, WOOD);
    resourceContainer.add(2, STONE);
    resourceContainer.add(4, FOOD);
    resourceContainer.add(8, IRON);

    TS_ASSERT_EQUALS( resourceContainer.totalStorage(), 15);
  }

  void testAvailableStorage() {
    std::set<ResourceType> storedTypes = { WOOD, STONE, FOOD, IRON };
    ResourceContainer resourceContainer(15, storedTypes);

    TS_ASSERT_EQUALS( resourceContainer.availableStorage(), 15);
    resourceContainer.add(1, WOOD);

    TS_ASSERT_EQUALS( resourceContainer.availableStorage(), 14);
    resourceContainer.add(2, STONE);

    TS_ASSERT_EQUALS( resourceContainer.availableStorage(), 12);
    resourceContainer.add(4, FOOD);

    TS_ASSERT_EQUALS( resourceContainer.availableStorage(), 8);
    resourceContainer.add(8, IRON);

    TS_ASSERT_EQUALS( resourceContainer.availableStorage(), 0);
  }

  void testUnsuportedStorageType(){
    std::set<ResourceType> storedTypes = { WOOD };
    ResourceContainer resourceContainer(20, storedTypes);

    TS_ASSERT(resourceContainer.canStore(WOOD));

    TS_ASSERT(!resourceContainer.canStore(STONE));

    TS_ASSERT_THROWS(resourceContainer.add(1, STONE), ResourceHandlingError);
  }
  
  void testSpreadOutCapacity() {
    std::set<ResourceType> storedTypes = { WOOD, FOOD, IRON };
    ResourceContainer resourceContainer(30, storedTypes);

    TS_ASSERT_EQUALS(resourceContainer.totalStorage(), 0);
    TS_ASSERT_EQUALS(resourceContainer.availableStorage(), 30);    

    resourceContainer.add(10, WOOD);
    TS_ASSERT_EQUALS(resourceContainer.totalStorage(), 10);
    TS_ASSERT_EQUALS(resourceContainer.availableStorage(), 20);

    resourceContainer.add(10, FOOD);
    TS_ASSERT_EQUALS(resourceContainer.totalStorage(), 20);
    TS_ASSERT_EQUALS(resourceContainer.availableStorage(), 10);

    resourceContainer.add(10, IRON);
    TS_ASSERT_EQUALS(resourceContainer.totalStorage(), 30);
    TS_ASSERT_EQUALS(resourceContainer.availableStorage(), 0);

    TS_ASSERT_THROWS(resourceContainer.add(1, IRON), ResourceHandlingError);
  }

  void testMoveResources() {
    std::set<ResourceType> storedTypes = { WOOD, FOOD, IRON };
    ResourceContainer a(30, storedTypes);
    ResourceContainer b(10, storedTypes);

    a.add(5, WOOD);
    a.moveTo( b );

    TS_ASSERT_EQUALS(a.getAmount(WOOD), 0);
    TS_ASSERT_EQUALS(b.getAmount(WOOD), 5);

    a.add(10, FOOD);
    a.moveTo( b );

    TS_ASSERT_EQUALS(a.getAmount(FOOD), 5);
    TS_ASSERT_EQUALS(b.getAmount(FOOD), 5);
  }

  void testMoveWithUnstorableResource(){
    std::set<ResourceType> storedTypesA = { WOOD, FOOD, IRON };
    ResourceContainer a(30, storedTypesA);

    std::set<ResourceType> storedTypesB = { FOOD, IRON };
    ResourceContainer b(30, storedTypesB);
    
    a.add(10, WOOD);
    a.add(10, FOOD);
    a.add(10, IRON);

    a.moveTo(b);

    TS_ASSERT_EQUALS(a.totalStorage(), 10);
    TS_ASSERT_EQUALS(a.getAmount(WOOD), 10);

    TS_ASSERT_EQUALS(b.totalStorage(), 20);
    TS_ASSERT_EQUALS(b.getAmount(WOOD), 0);
  }

  void tearDown(){

  }
};

