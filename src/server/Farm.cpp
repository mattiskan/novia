#include "Farm.h"

Farm::Farm(ResourceType type) :
  WareHouse( ResourceContainer(30, {type}) ) 
  , product_(type)
{
  
}



void Farm::grow(){
  resources_.add(1, product_);
}

