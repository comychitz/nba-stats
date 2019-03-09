#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "PlayerDb.h"
#include <iostream>

using namespace nba;

TEST_CASE("player DB", "[basic]") {
  PlayerDb db;
  REQUIRE(db.init("../../data/players.txt"));

  Player player;
  REQUIRE(db.getPlayer("Stephen Curry", player));

  REQUIRE(player.firstname == "Stephen");
  REQUIRE(player.lastname == "Curry");
  REQUIRE(player.fullname == "Stephen Curry");
  REQUIRE(player.id == 201939);
}
