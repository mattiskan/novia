#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include "MapObject.h"
#define MAP_SIZE 1

typedef std::vector<MapObject*>::iterator iterator;


// Håller alla MapObjects inom en liten region
struct MapSquare {
  const int x_, y_;
  std::vector<MapObject*> mapObjects;
  
  MapSquare(int x, int y) : x_(x), y_(y) {}
};


class MapModel {
  friend class MapController;
private:
  MapSquare* squares[MAP_SIZE][MAP_SIZE];

public:
  MapModel();
  std::vector<MapObject*> temporarySolution;
};

#endif
