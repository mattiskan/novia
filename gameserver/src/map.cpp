#include "map.h"
#include <stdexcept>
#include <fstream>
#include <jsoncpp/json.h>


namespace novia {

  Map::Map() {
    load_map();
  }

  Json::Value Map::serialize() const {
    using namespace Json;
    Value serialized(objectValue);
    return serialized;
  }
  void Map::load_map() {
    using namespace Json;
    Value map_json;
    std::ifstream map_stream("maps/map.json", std::ifstream::in);
    if (!map_stream.good()) {
      map_stream.close();
      throw std::invalid_argument("Map file not found");
    }
    Reader json_reader;
    if (!json_reader.parse(map_stream, map_json)) {
      throw std::invalid_argument(json_reader.getFormatedErrorMessages());
    }

    map_stream.close();
    init_from_json(map_json);
  }

  void Map::init_from_json(const Json::Value& map) {
    using namespace Json;
    get_rooms().clear();
    get_characters().clear();
    for (const std::string& : roommap["rooms"].memberNames()) {
      
    }
    
  }

  std::vector<std::shared_ptr<Room>>& Map::get_rooms() {
    return rooms_;
  }

  std::vector<std::shared_ptr<Character>>& Map::get_characters() {
    return characters_;
  }


}
