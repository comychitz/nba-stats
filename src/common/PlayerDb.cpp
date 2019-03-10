#include "PlayerDb.h"
#include "Util.h"
#include <fstream>
#include <iostream>

namespace nba {

PlayerDb::PlayerDb() {
  players_.reserve(4500);
}

PlayerDb::~PlayerDb() { 
}

bool PlayerDb::init(const std::string &srcPath) {
  std::ifstream f(srcPath.c_str());
  if (!f.good()) {
    std::cout << "ERROR: Unable to open: " << srcPath << std::endl;
    return false;
  }
  std::string line;
  unsigned count = 0;
  while (std::getline(f, line)) {
    parsePlayer_(line, count++);
  }
  return true;
}

bool PlayerDb::getPlayer(const std::string &name, Player &player) const {
  auto playerIter = nameToPlayerId_.find(name);
  if (playerIter != nameToPlayerId_.end()) {
    player = players_.at(playerIter->second);
    return true;
  }
  return false;
}

void PlayerDb::parsePlayer_(const std::string &line, unsigned count) {
  std::vector<std::string> tokens = Util::tokenize(line, ",");
    if (tokens.size() < 4) {
    std::cout << "WARNING: Unexpected number of tokens: " << line << std::endl;
    return;
  }
  Player player;
  player.id = Util::strToULong(tokens.at(0));
  player.lastname = tokens.at(1);
  player.firstname = tokens.at(2);
  player.fullname = tokens.at(3);
  players_.push_back(player);

  nameToPlayerId_[player.fullname] = count;

  // the rest of the tokens are (optional) nick names
  for (size_t i = 4; i < tokens.size(); i++) {
    nameToPlayerId_[tokens.at(i)] = count;
  }
}

}
