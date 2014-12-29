//-*-c++-*-
#include <iostream>
#include <cxxtest/TestSuite.h>
#include "../src/storage_unit.h"

using namespace novia;

class StorageUnitTest : public CxxTest::TestSuite
{
 public:
  void testStoreOneResource(){
    const int CAP = 20;
    
    StorageUnit resourceContainer(CAP, { WOOD });

    for(int i=1; i<= CAP; ++i){
      resourceContainer.add(1, WOOD);
      TS_ASSERT_EQUALS( resourceContainer.get(WOOD), i);//invariant
    }
  }

  void testStoreTwoResources(){
    const int CAP = 20;

    StorageUnit resourceContainer(CAP,  { WOOD, FOOD });


    for(int i=1; i<= CAP/2; ++i){
      resourceContainer.add(1, WOOD);
      resourceContainer.add(1, FOOD);
      TS_ASSERT_EQUALS( resourceContainer.get(WOOD), i);//invariant
      TS_ASSERT_EQUALS( resourceContainer.get(FOOD), i);//invariant
    }
  }

  void testCapacityOverload(){
    StorageUnit resourceContainer(20, { WOOD });

    TS_ASSERT_EQUALS(resourceContainer.add(30, WOOD), 10);

    TS_ASSERT_EQUALS(resourceContainer.get(WOOD), 20);
  }

  void testTotalStorage() {
    StorageUnit resourceContainer(30, { WOOD, STONE, FOOD, IRON } );

    resourceContainer.add(1, WOOD);
    resourceContainer.add(2, STONE);
    resourceContainer.add(4, FOOD);
    resourceContainer.add(8, IRON);

    TS_ASSERT_EQUALS( resourceContainer.totalStorage(), 15);
  }

  void testAvailableStorage() {
    StorageUnit resourceContainer(15, { WOOD, STONE, FOOD, IRON });

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
    StorageUnit resourceContainer(20, { WOOD });

    TS_ASSERT(resourceContainer.canStore(WOOD));

    TS_ASSERT(!resourceContainer.canStore(STONE));

    TS_ASSERT_THROWS(resourceContainer.add(1, STONE), ResourceHandlingError);
  }
  
  void testSpreadOutCapacity() {
    StorageUnit resourceContainer(30, { WOOD, FOOD, IRON });

    TS_ASSERT_EQUALS(resourceContainer.totalStorage(), 0);
    TS_ASSERT_EQUALS(resourceContainer.availableStorage(), 30);    

    TS_ASSERT_EQUALS(resourceContainer.add(10, WOOD), 0);
    TS_ASSERT_EQUALS(resourceContainer.totalStorage(), 10);
    TS_ASSERT_EQUALS(resourceContainer.availableStorage(), 20);

    TS_ASSERT_EQUALS(resourceContainer.add(10, FOOD), 0);
    TS_ASSERT_EQUALS(resourceContainer.totalStorage(), 20);
    TS_ASSERT_EQUALS(resourceContainer.availableStorage(), 10);

    TS_ASSERT_EQUALS(resourceContainer.add(10, IRON), 0);
    TS_ASSERT_EQUALS(resourceContainer.totalStorage(), 30);
    TS_ASSERT_EQUALS(resourceContainer.availableStorage(), 0);

    TS_ASSERT_EQUALS(resourceContainer.add(1, IRON), 1);
    //The last one shouldn't fit:
    TS_ASSERT_EQUALS(resourceContainer.totalStorage(), 30);
    
  }

  void testMoveResources() {
    StorageUnit a(30, { WOOD, FOOD, IRON });
    StorageUnit b(10, { WOOD, FOOD, IRON });

    a.add(5, WOOD);
    a.retrieveInto( b );

    TS_ASSERT_EQUALS(a.get(WOOD), 0);
    TS_ASSERT_EQUALS(b.get(WOOD), 5);

    a.add(10, FOOD);
    a.retrieveInto( b );

    TS_ASSERT_EQUALS(a.get(FOOD), 5);
    TS_ASSERT_EQUALS(b.get(FOOD), 5);
  }

  void testMoveWithUnstorableResource(){
    StorageUnit a(30, { WOOD, FOOD, IRON });

    StorageUnit b(30, { FOOD, IRON });
    
    a.add(10, WOOD);
    a.add(10, FOOD);
    a.add(10, IRON);

    a.retrieveInto(b);

    TS_ASSERT_EQUALS(a.totalStorage(), 10);
    TS_ASSERT_EQUALS(a.get(WOOD), 10);

    TS_ASSERT_EQUALS(b.totalStorage(), 20);
    TS_ASSERT_EQUALS(b.get(WOOD), 0);
  }

};

