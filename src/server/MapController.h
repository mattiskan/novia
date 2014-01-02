#ifndef MAP_CONTROLLER_H
#define MAP_CONTROLLER_H

#include "MapModel.h"

class MapController {
 private:
  MapModel model_;
  
 public:
 MapController(MapModel& model):
  model_(model){
    
  }

  void addToMap(MapObject* newObj){
    model_.squares[0][0]->mapObjects.push_back(newObj);
  }
};


#endif
