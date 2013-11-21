#include <vector>
#include "MapObject.h"
#define MAP_SIZE 1000


/*
 * Håller alla MapObjects inom en liten region
 */
struct MapSquare {
  const int X, Y;
  std::vector<MapObject> mapObjects;
  
  MapSquare(int x, int y) : X(x), Y(y) {}
};


class GameMap {

private:
  MapSquare squares[MAP_SIZE][MAP_SIZE];

public:
  
};



