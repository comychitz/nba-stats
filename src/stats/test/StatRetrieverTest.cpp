#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "StatRetriever.h"
#include <iostream>

using namespace nba;

class StatProcessorTest : public StatProcessor {
  public:
    StatProcessorTest() { }

    virtual ~StatProcessorTest() {}

    void process(const std::string &stats) {
      std::cout << stats << std::endl;
    }
};


TEST_CASE("retriever test", "[basic]") {
  StatProcessorTest processor;
  StatRetriever retriever;

  std::map<std::string, std::string> params;
  params["PlayerID"] = "2544";
  params["PerMode"] = "Totals";

  REQUIRE(retriever.get("playerprofilev2", params, processor));
}
