#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include <catch2/catch.hpp>
#include "StatRetriever.h"
#include "StatProcessorJson.h"
#include "PlayerDb.h"
#include "Util.h"
#include <iostream>
#include <sstream>

using namespace nba;

class StatProcessorTest : public StatProcessor {
  public:
    StatProcessorTest() { }

    virtual ~StatProcessorTest() {}

    void process(const std::string &stats, std::vector<StatMap> &) {
      REQUIRE(!stats.empty());
    }
};

TEST_CASE("retriever test", "[basic]") {
  StatProcessorTest processor;
  StatRetriever retriever(processor);

  std::map<std::string, std::string> params;
  params["PlayerID"] = "2544";
  params["PerMode"] = "Totals";

  std::vector<StatMap> stats;
  REQUIRE(retriever.get("playerprofilev2", params, stats));
}

TEST_CASE("json proccesor", "[basic]") {
  StatProcessorJson processor;
  StatRetriever retriever(processor);

  std::vector<StatMap> stats;
  std::map<std::string, std::string> params;
  params["PlayerID"] = "2544";
  params["PerMode"] = "Totals";

  REQUIRE(retriever.get("playerprofilev2", params, stats));
}

TEST_CASE("player retriever", "[basic]") {
  StatProcessorJson processor;
  StatRetriever retriever(processor);

  PlayerDb db;
  db.init("../../data/players.txt");

  Player player;
  REQUIRE(db.getPlayer("Stephen Curry", player));

  std::map<std::string, std::string> params;
  params["PlayerID"] = Util::toStr(player.id);
  params["PerMode"] = "Totals";

  std::vector<StatMap> stats;
  REQUIRE(retriever.get("playerprofilev2", params, stats));
}
