#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#endif
#include "TeamDb.h"
#include "StatMap.h"
#include "PlayerDb.h"

using namespace nba;

TEST_CASE("player DB", "[basic]") {
  PlayerDb db;
  REQUIRE(db.init("../../data/players.txt"));

  Player player;
  REQUIRE(db.getPlayer("Stephen Curry", player));

  CHECK(player.firstname == "Stephen");
  CHECK(player.lastname == "Curry");
  CHECK(player.fullname == "Stephen Curry");
  CHECK(player.id == 201939);
}

TEST_CASE("resolve nick name", "[basic]") {
  PlayerDb db;
  REQUIRE(db.init("../../data/players.txt"));

  Player player;
  CHECK(db.getPlayer("Steph Curry", player));
  CHECK(player.fullname == "Stephen Curry");

  CHECK(db.getPlayer("MJ", player));
  CHECK(player.fullname == "Michael Jordan");

  CHECK(db.getPlayer("The King", player));
  CHECK(player.fullname == "LeBron James");
}

TEST_CASE("team DB", "[basic]") {
  TeamDb db;
  REQUIRE(db.init("../../data/teams.txt"));

  Team team;
  REQUIRE(db.getTeam("Warriors", team));

  CHECK(team.id == 1610612744);
  CHECK(team.abbr == "GSW");
  CHECK(team.name == "Warriors");
  CHECK(team.fullname == "Golden State Warriors");
  CHECK(team.yearfounded == 1946);
  CHECK(team.city == "Golden State");
  CHECK(team.state == "California");
}

TEST_CASE("resolve team name", "[basic]") {
  TeamDb db;
  REQUIRE(db.init("../../data/teams.txt"));

  Team team;
  REQUIRE(db.getTeam("GSW", team));
  CHECK(team.id == 1610612744);

  REQUIRE(db.getTeam("Golden State", team));
  CHECK(team.id == 1610612744);

  REQUIRE(db.getTeam("Golden State Warriors", team));
  CHECK(team.id == 1610612744);
}

TEST_CASE("stat map test", "[basic]") {
  StatMap map;

  map.add("LEAGUE_ID", "00");
  map.add("PTS", "17.5");

  std::string leagueid;
  CHECK(map.get("LEAGUE_ID", leagueid));
  CHECK(leagueid == "00");
  float pts = 0.0;
  CHECK(map.get("PTS", pts));
  CHECK(pts == 17.5);
}
