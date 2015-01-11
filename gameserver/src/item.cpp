//-*-c++-*-
#include "item.h"

namespace novia {
  Item::Item() {

  }

  std::string Item::name() const {
    return name_;
  }

  std::string Item::description() const {
    return description_;
  }

  Json::Value Item::serialize() const {
    using namespace Json;
    Value serialized(objectValue);

    return serialized;
  }

}
