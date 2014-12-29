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
    StorageUnit resourceContainer2(CAP, { WOOD });

    for(int i=1; i<= CAP; ++i){
      resourceContainer.add(1, WOOD);
      TS_ASSERT_EQUALS( resourceContainer.get(WOOD), i);//invariant
      resourceContainer2.add(1, WOOD);
      TS_ASSERT_EQUALS( resourceContainer2.get(WOOD), i);//invariant

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

    TS_ASSERT_THROWS(resourceContainer.add(30, WOOD), ResourceHandlingError);

    TS_ASSERT_EQUALS(resourceContainer.get(WOOD), 0);
  }

  void testTotalStorage() {
    StorageUnit resourceContainer(30, { WOOD, STONE, FOOD, IRON } );

    resourceContainer.add(1, WOOD);
    resourceContainer.add(2, STONE);
    resourceContainer.add(4, FOOD);
    resourceContainer.add(8, IRON);

    TS_ASSERT_EQUALS( resourceContainer.total_storage(), 15);
  }

  void testAvailableStorage() {
    StorageUnit resourceContainer(15, { WOOD, STONE, FOOD, IRON });

    TS_ASSERT_EQUALS( resourceContainer.available_storage(), 15);
    resourceContainer.add(1, WOOD);

    TS_ASSERT_EQUALS( resourceContainer.available_storage(), 14);
    resourceContainer.add(2, STONE);

    TS_ASSERT_EQUALS( resourceContainer.available_storage(), 12);
    resourceContainer.add(4, FOOD);

    TS_ASSERT_EQUALS( resourceContainer.available_storage(), 8);
    resourceContainer.add(8, IRON);

    TS_ASSERT_EQUALS( resourceContainer.available_storage(), 0);
  }

  void testUnsuportedStorageType(){
    StorageUnit resourceContainer(20, { WOOD });

    TS_ASSERT(resourceContainer.can_store(WOOD));

    TS_ASSERT(!resourceContainer.can_store(STONE));

    TS_ASSERT_THROWS(resourceContainer.add(1, STONE), ResourceHandlingError);
  }
  
  void testSpreadOutCapacity() {
    StorageUnit resourceContainer(30, { WOOD, FOOD, IRON });

    TS_ASSERT_EQUALS(resourceContainer.total_storage(), 0);
    TS_ASSERT_EQUALS(resourceContainer.available_storage(), 30);    

    resourceContainer.add(10, WOOD);
    TS_ASSERT_EQUALS(resourceContainer.total_storage(), 10);
    TS_ASSERT_EQUALS(resourceContainer.available_storage(), 20);

    resourceContainer.add(10, FOOD);
    TS_ASSERT_EQUALS(resourceContainer.total_storage(), 20);
    TS_ASSERT_EQUALS(resourceContainer.available_storage(), 10);

    resourceContainer.add(10, IRON);
    TS_ASSERT_EQUALS(resourceContainer.total_storage(), 30);
    TS_ASSERT_EQUALS(resourceContainer.available_storage(), 0);

    TS_ASSERT_THROWS(resourceContainer.add(1, IRON), ResourceHandlingError);

    TS_ASSERT_EQUALS(resourceContainer.total_storage(), 30);


    //The last one shouldn't fit:
    TS_ASSERT_EQUALS(resourceContainer.total_storage(), 30);

    resourceContainer.add(-10, IRON);
    TS_ASSERT_EQUALS(resourceContainer.total_storage(), 20);
    TS_ASSERT_EQUALS(resourceContainer.available_storage(), 10);
    
  }

   void testTakeResources() {
    StorageUnit a(30, { WOOD, FOOD, IRON });
    StorageUnit b(10, { WOOD, FOOD, IRON });

    TS_ASSERT_THROWS(a.take(10, WOOD, b), ResourceHandlingError);
    TS_ASSERT_EQUALS(a.get(WOOD), 0);
    TS_ASSERT_EQUALS(b.get(WOOD), 0);

    a.add(10, WOOD);
    b.take(10, WOOD, a);

    TS_ASSERT_EQUALS(a.get(WOOD), 0);
    TS_ASSERT_EQUALS(b.get(WOOD), 10);


    a.add(20, FOOD);
    TS_ASSERT_THROWS(b.take(20, FOOD, a), ResourceHandlingError);

    TS_ASSERT_EQUALS(a.get(FOOD), 20);
    TS_ASSERT_EQUALS(b.get(FOOD), 0);
   }

   //  void testMoveWithUnstorableResource(){
   //  StorageUnit a(30, { WOOD, FOOD, IRON });

   //  StorageUnit b(30, { FOOD, IRON });
    
   //  a.add(10, WOOD);
   //  a.add(10, FOOD);
   //  a.add(10, IRON);

   //  a.retrieveInto(b);

   //  TS_ASSERT_EQUALS(a.total_storage(), 10);
   //  TS_ASSERT_EQUALS(a.get(WOOD), 10);

   //  TS_ASSERT_EQUALS(b.total_storage(), 20);
   //  TS_ASSERT_EQUALS(b.get(WOOD), 0);
   //  }

};


