#ifndef MY_BUILDING_H
#define MY_BUILDING_H

#include "MapObject.h"
#include "Player.h"


enum BuildingType { plant, refinery, warehouse, house, factory };

class Building : public MapObject {
 private:
  Player owner_;
  BuildingType type_;
 public:
  Building(BuildingType);
};

#endif
