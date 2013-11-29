#ifndef BUILDING_H
#define BUILDING_H

#include "MapObject.h"
#include "Player.h"

enum BuildingType { plant, refinery, warehouse, house, facility };

class Building : public MapObject {
 private:
  Player owner;
  BuildingType type;
  int a;
};

#endif
