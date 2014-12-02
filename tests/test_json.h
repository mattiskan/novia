// -*-c++-*-
#include <cxxtest/TestSuite.h>
#include <string>
#include <iostream>
#include <jsoncpp/json.h>

class TestJSON : public CxxTest::TestSuite
{
 public:
  void test_read() {
    const bool keep_comments = true;

    Json::Value root;
    Json::Reader reader;

    std::string json =
      "{ \"key\": \"found\" }";    
    
    bool successful = reader.parse(json, root, keep_comments);
    TS_ASSERT(successful);

    TS_ASSERT_EQUALS(root.get("key", "not_found").asString(), "found");
    TS_ASSERT_EQUALS(root.get("unpresent_key", "default").asString(), "default"); 
  }

  void test_write() {
    Json::Value root;

    root["key"] = "value";

    root["letters"]["a"] = 1;
    root["letters"]["b"] = 2;
    root["letters"]["c"] = 3;
    
    /*root["array"] = Json::Value(Json::arrayValue);
    root["array"][0] = "first";
    root["array"][1] = "seccond";
    root["array"][2] = "third";*/
    std::cout << root << std::endl;
  }

};
