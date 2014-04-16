#include <iostream>
#include <cxxtest/TestSuite.h>
#include "../src/server/Farm.h"
#include "../src/server/Timer.h"

class MockTimer: public Timer {
 public:
  bool hasQueuedEvents() {
    return !queuedEvents_.empty();
  }
};

class FarmTest : public CxxTest::TestSuite
{
 public:

  void testGrowth(){
    Timer t;
    Farm subject(WOOD, &t);
      
    for(int i=0; i<(120*20 +1); ++i)
      t.tick();

    TS_ASSERT(subject.isFull());
  }

  void testStopGrowthOnFull() {
    MockTimer t;
    Farm subject(WOOD, &t);

    TS_ASSERT( t.hasQueuedEvents() );

    for(int i=0; i<(120*20 +1); ++i)
      t.tick();

    TS_ASSERT( !t.hasQueuedEvents() );
  }

  void testRequeueAfterFull(){
    Timer t;
    Farm subject(WOOD, &t);
    
    subject.add(19, WOOD);

    for(int i=0; i<120; ++i)
      t.tick();
    TS_ASSERT( subject.isFull() );

    StorageUnit dump(20, {WOOD} );
    subject.retrieveInto( dump ); //should requeue in timer

    TS_ASSERT( !subject.isFull() );

    for(int i=0; i<120; ++i)
      t.tick();

    TS_ASSERT_EQUALS(subject.get(WOOD), 1);
  }

};

