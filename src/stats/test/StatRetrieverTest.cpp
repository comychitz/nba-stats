#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "StatRetriever.h"
#include <iostream>

using namespace nba;

TEST_CASE("retriever test", "[basic]") {
  StatRetriever retriever;
  std::map<std::string, std::string> params { {"PlayerID", "2544"},
                                              {"PerMode", "Totals"} };
  params["PlayerID"] = "2544";
  params["PerMode"] = "Totals";

  std::string response;
  REQUIRE(retriever.get("playerprofilev2", params, response));
  REQUIRE(!response.empty());
}
