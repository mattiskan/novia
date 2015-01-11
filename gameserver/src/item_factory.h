//-*-c++-*-
#ifndef NOVIA_ITEM_FACTORY_H
#define NOVIA_ITEM_FACTORY_H

#include <map>
#include <memory>
#include <jsoncpp/json.h>

#include "item.h"

namespace novia {
  class Item;
  namespace ItemFactory {
    std::shared_ptr<Item> create_item(const Json::Value& item_data);
  };
}

#endif
