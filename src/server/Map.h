#ifndef MAP_MODEL_H
#define MAP_MODEL_H

#include <vector>
#include "AbstractMapObject.h"

class Map {
 private:
  std::vector<AbstractMapObject> mapObjects_;


 public:
  Map();

  void add(AbstractMapObject&);

};


#endif
