#include <iostream>
#include <cxxtest/TestSuite.h>
#include "../src/server/GameInstance.h"

class GameInstanceTest : public CxxTest::TestSuite
{

 public:

  void setUp(){
    
  }

  void testCreateGameInstance(){
    GameInstance gameInstance;
  }

  void tearDown(){

  }
};
