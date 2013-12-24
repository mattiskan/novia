#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include "MapObject.h"
#define MAP_SIZE 1

typedef std::vector<MapObject*>::iterator iterator;


// Håller alla MapObjects inom en liten region
struct MapSquare {
  const int X, Y;
  std::vector<MapObject*> mapObjects;
  
  MapSquare(int x, int y) : X(x), Y(y) {}
};


class Map {
private:
  MapSquare* squares[MAP_SIZE][MAP_SIZE];

public:
  Map();
  iterator getMapObjects();
  std::vector<MapObject*> temporarySolution;
};

#endif
