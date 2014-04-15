#include "Map.h"


Map::Map() {

}

void Map::add(AbstractMapObject& newObj){
  mapObjects_.push_back( newObj );
}




